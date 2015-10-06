# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY miguel_smpeg ##################################
# with interface miguel_smpeg_interface

# Source code files of the library
SET(BII_LIB_SRC  MPEG.cpp
			MPEG.h
			MPEGaction.h
			MPEGaudio.h
			MPEGerror.h
			MPEGframe.h
			MPEGlist.cpp
			MPEGlist.h
			MPEGring.cpp
			MPEGring.h
			MPEGstream.cpp
			MPEGstream.h
			MPEGsystem.cpp
			MPEGsystem.h
			MPEGvideo.h
			audio/MPEGaudio.cpp
			audio/bitwindow.cpp
			audio/filter.cpp
			audio/filter_2.cpp
			audio/hufftable.cpp
			audio/mpeglayer1.cpp
			audio/mpeglayer2.cpp
			audio/mpeglayer3.cpp
			audio/mpegtable.cpp
			audio/mpegtoraw.cpp
			smpeg.cpp
			smpeg.h
			video/MPEGvideo.cpp
			video/decoders.cpp
			video/decoders.h
			video/dither.h
			video/floatdct.cpp
			video/gdith.cpp
			video/jrevdct.cpp
			video/motionvec.cpp
			video/parseblock.cpp
			video/proto.h
			video/readfile.cpp
			video/util.cpp
			video/util.h
			video/video.cpp
			video/video.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS miguel_smpeg_interface miguel_sdl2)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS assert.h cstring errno.h fcntl.h io.h limits.h math.h signal.h stdarg.h stdio.h stdlib.h string.h sys/stat.h sys/time.h sys/types.h unistd.h util.h windows.h winsock.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
