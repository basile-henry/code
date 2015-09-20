/// @file we catch the signals send to us by the OS on crash and display a stackwalker afterwards.
/// This works on unix as well as on windows, in release mode as well as in debug mode.
/// (Just make sure you got debuginfo on windows and initiate this class somewhere in your code,
/// as singleton or as instance in your main functin, either works)

#ifndef INEXOR_UTIL_CRASH_REPORTER_H
#define INEXOR_UTIL_CRASH_REPORTER_H

#include <signal.h>

namespace inexor {
namespace crashreporter {

    extern void abortHandler(int signum);

    class CrashReporter
    {
      public:
        CrashReporter()
        {
            signal(SIGABRT, abortHandler);
            signal(SIGSEGV, abortHandler);
            signal(SIGILL, abortHandler);
            signal(SIGFPE, abortHandler);
        }
    };

} // namespace crashreporter
} // namespace inexor

#endif // INEXOR_UTIL_CRASH_REPORTER_H