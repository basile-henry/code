# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY glenn_png ##################################
# with interface glenn_png_interface

# Source code files of the library
SET(BII_LIB_SRC  png.c
			png.h
			pngconf.h
			pngdebug.h
			pngerror.c
			pngget.c
			pnginfo.h
			pngmem.c
			pngpread.c
			pngpriv.h
			pngread.c
			pngrio.c
			pngrtran.c
			pngrutil.c
			pngset.c
			pngstruct.h
			pngtrans.c
			pngwio.c
			pngwrite.c
			pngwtran.c
			pngwutil.c)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS glenn_png_interface zlib_zlib)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS crtdbg.h errno.h float.h limits.h math.h mem.h setjmp.h stddef.h stdio.h stdlib.h string.h time.h windows.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
