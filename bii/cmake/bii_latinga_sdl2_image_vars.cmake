# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY latinga_sdl2_image ##################################
# with interface latinga_sdl2_image_interface

# Source code files of the library
SET(BII_LIB_SRC  IMG.c
			IMG_ImageIO.m
			IMG_UIImage.m
			IMG_bmp.c
			IMG_gif.c
			IMG_jpg.c
			IMG_lbm.c
			IMG_pcx.c
			IMG_png.c
			IMG_pnm.c
			IMG_tga.c
			IMG_tif.c
			IMG_webp.c
			IMG_xcf.c
			IMG_xpm.c
			IMG_xv.c
			IMG_xxx.c
			SDL_image.h
			miniz.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS latinga_sdl2_image_interface glenn_png google_libwebp jpeg_jpeg latinga_sdl2 tiff_tiff)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS assert.h ctype.h setjmp.h stdio.h stdlib.h string.h sys/stat.h sys/utime.h time.h utime.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
