# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY zlib_zlib ##################################
# with interface zlib_zlib_interface

# Source code files of the library
SET(BII_LIB_SRC  adler32.c
			compress.c
			crc32.c
			crc32.h
			deflate.c
			deflate.h
			gzclose.c
			gzguts.h
			gzlib.c
			gzread.c
			gzwrite.c
			infback.c
			inffast.c
			inffast.h
			inffixed.h
			inflate.c
			inflate.h
			inftrees.c
			inftrees.h
			trees.c
			trees.h
			uncompr.c
			zlib.h
			zutil.c
			zutil.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS zlib_zlib_interface )
# System included headers
SET(BII_LIB_SYSTEM_HEADERS ctype.h errno.h fcntl.h io.h limits.h malloc.h stdarg.h stddef.h stdio.h stdlib.h string.h windows.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
