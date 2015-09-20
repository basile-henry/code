
#include <stdio.h>
#include "inexor/crashreporter/CrashReporter.h"
#ifdef WIN32
#include "inexor/crashreporter/StackWalker_windows.h"
#else
#include "inexor/crashreporter/StackWalker_posix.h"
#endif

extern void fatal(const char *s, ...);

namespace inexor {
namespace crashreporter {

#define CRASHREPORTER_OUTPUT_LEN 1000
char crashreporter_output[CRASHREPORTER_OUTPUT_LEN + 1];

/// This function serves as callback for the signals function.
/// It gets executed when an instance of the crashreporter class exists in your code
/// and it receives a signal by the OS to terminate the program.
void abortHandler(int signum)
{
    const char* name = NULL;
    switch(signum)
    {
        case SIGABRT: name = "SIGABRT";  break;
        case SIGSEGV: name = "SIGSEGV";  break;
        case SIGILL:  name = "SIGILL";   break;
        case SIGFPE:  name = "SIGFPE";   break;
      #ifndef WIN32
        case SIGBUS:  name = "SIGBUS";   break;
      #endif
    }

    if(name) snprintf(crashreporter_output, CRASHREPORTER_OUTPUT_LEN, "Caught signal %d (%s)\n\n", signum, name);
    else snprintf(crashreporter_output, CRASHREPORTER_OUTPUT_LEN, "Caught signal %d\n\n", signum);

    printStackTrace(crashreporter_output, CRASHREPORTER_OUTPUT_LEN);

    fatal(crashreporter_output);
}

} // namespace crashreporter
} // namespace inexor
