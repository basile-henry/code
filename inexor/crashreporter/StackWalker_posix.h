/// Show stacktrace on unix, do not include directly.
/// Code mainly written by Rafael Baptista.

#ifndef INEXOR_CRASHREPORTER_STACKWALKER_POSIX_H
#define INEXOR_CRASHREPORTER_STACKWALKER_POSIX_H

#include <execinfo.h>
#include <stdlib.h>
#include <cxxabi.h>

namespace inexor {
namespace crashreporter {

#ifdef DARWIN
static inline void demanglesymbol(char *output, int outputlen, char *symbol)
{
    char* begin_name = NULL;
    char* begin_offset = NULL;
    char* end_offset = NULL;

    // find parentheses and +address offset surrounding the mangled name
    for(char *p = symbol; *p; ++p)
    {
        if((*p == '_') && (*(p - 1) == ' ')) begin_name = p - 1;
        else if(*p == '+') begin_offset = p - 1;
    }

    if(begin_name && begin_offset && (begin_name < begin_offset))
    {
        *begin_name++ = '\0';
        *begin_offset++ = '\0';

        // mangled name is now in [begin_name, begin_offset) and caller
        // offset in [begin_offset, end_offset). now apply __cxa_demangle():
        int status;
        size_t funcnamesize = 1024;
        char funcname[1024];

        char* ret = abi::__cxa_demangle(begin_name, &funcname[0], &funcnamesize, &status);
        if(status == 0)
        {
            snprintf(output, outputlen, "  %-30s %-40s %s\n", symbol, ret, begin_offset);
        }
        else {
            // demangling failed. Output function name as a C function with no arguments.
            snprintf(output, outputlen, "  %-30s %-38s() %s\n", symbol, begin_name, begin_offset);
        }
    }
    else {
        // couldn't parse the line? print the whole line.
        snprintf(output, outputlen, "  %-40s\n", symbol);
    }
}
#else //NOT DARWIN (-> LINUX)

static inline void demanglesymbol(char *output, int outputlen, char *symbol)
{
    //before: ./module(function+0x15c) [0x8048a6d]
    char* begin_name = NULL;
    char* begin_offset = NULL;
    char* end_offset = NULL;

    // find parentheses and +address offset surrounding the mangled name
    for(char *p = symbol; *p; ++p)
    {
        if(*p == '(') begin_name = p;
        else if(*p == '+') begin_offset = p;
        else if(*p == ')' && (begin_offset || begin_name)) end_offset = p;
    }

    if(begin_name && end_offset && (begin_name < end_offset))
    {
        *begin_name++ = '\0';
        *end_offset++ = '\0';
        if(begin_offset) *begin_offset++ = '\0';

        // mangled name is now in [begin_name, begin_offset) and caller
        // offset in [begin_offset, end_offset). now apply __cxa_demangle():

        int status = 0;
        size_t funcnamesize = 1024;
        char funcname[1024];

        char* ret = abi::__cxa_demangle(begin_name, funcname, &funcnamesize, &status);
        char* fname = begin_name;
        if(status == 0) fname = ret;

        if(begin_offset) snprintf(output, outputlen, "  %-30s ( %-40s  + %-6s) %s\n", symbol, fname, begin_offset, end_offset);
        else             snprintf(output, outputlen, "  %-30s ( %-40s    %-6s) %s\n", symbol, fname, "", end_offset);
    }
    else {
        // couldn't parse the line? print the whole line.
        snprintf(output, outputlen, "  %-40s\n", symbol);
    }
}
#endif // LINUX

#define MAX_FRAMES 9

static inline void printStackTrace(char *output, int outputlen)
{
    snprintf(output, outputlen, "stack trace:\n");

    // storage array for stack trace address data
    void* addrlist[MAX_FRAMES + 1];

    // retrieve current stack addresses
    unsigned int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

    if(addrlen == 0)
    {
        snprintf(output, outputlen, "  \n");
        return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // Actually it will be ## program address function + offset
    // this array must be free()-ed
    char** symbollist = backtrace_symbols(addrlist, addrlen);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for(unsigned int i = 4; i < addrlen; i++)
    {
        demanglesymbol(output, outputlen, symbollist[i]);
    }

    free(symbollist);
}

} // namespace crashreporter
} // namespace inexor

#endif // INEXOR_CRASHREPORTER_STACKWALKER_POSIX_H
