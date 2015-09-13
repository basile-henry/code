This module provides a stackwalker on crash.

The stackwalker appears as soon as an signal from the OS arrives to terminate the program (e.g. a segfault, division by zero..).

It should work on Windows, Linux and OS/X with the exception of MINGW (since our debug information are not compatible there
and we do not actually need a stackwalker on mingw currently since we use visual studio for our deployed packages).

To use this module, just include the CrashReporter.h somewhere in your code, make sure you got a ´fatal(onst char *s, ...)´ function declared,
and then initialise this crashreporter-class somewhere (e.g. in your main). It does not need to be called just needs to be there.

The other files are just there to implement printstacktrace() on the different platforms.

This document served as a base for this module:
http://oroboro.com/stack-trace-on-crash/


Currently we this module is disabled on mingw, if you do want to change that:
* read http://theorangeduck.com/page/printing-stack-trace-mingw
* uncomment the specific lines in the module disabling cmake
* write the cmake commands to convert the debug info and add it to our dev environment
* fix appearing bugs
