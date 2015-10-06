# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY tiff_tiff ##################################
# with interface tiff_tiff_interface

# Source code files of the library
SET(BII_LIB_SRC  contrib/pds/tif_imageiter.c
			contrib/pds/tif_imageiter.h
			libtiff/t4.h
			libtiff/tif_acorn.c
			libtiff/tif_apple.c
			libtiff/tif_atari.c
			libtiff/tif_aux.c
			libtiff/tif_close.c
			libtiff/tif_codec.c
			libtiff/tif_color.c
			libtiff/tif_compress.c
			libtiff/tif_dir.c
			libtiff/tif_dir.h
			libtiff/tif_dirinfo.c
			libtiff/tif_dirread.c
			libtiff/tif_dirwrite.c
			libtiff/tif_dumpmode.c
			libtiff/tif_error.c
			libtiff/tif_extension.c
			libtiff/tif_fax3.c
			libtiff/tif_fax3.h
			libtiff/tif_fax3sm.c
			libtiff/tif_flush.c
			libtiff/tif_getimage.c
			libtiff/tif_jbig.c
			libtiff/tif_jpeg.c
			libtiff/tif_jpeg_12.c
			libtiff/tif_luv.c
			libtiff/tif_lzma.c
			libtiff/tif_lzw.c
			libtiff/tif_msdos.c
			libtiff/tif_next.c
			libtiff/tif_ojpeg.c
			libtiff/tif_open.c
			libtiff/tif_packbits.c
			libtiff/tif_pixarlog.c
			libtiff/tif_predict.c
			libtiff/tif_predict.h
			libtiff/tif_print.c
			libtiff/tif_read.c
			libtiff/tif_strip.c
			libtiff/tif_swab.c
			libtiff/tif_thunder.c
			libtiff/tif_tile.c
			libtiff/tif_unix.c
			libtiff/tif_version.c
			libtiff/tif_vms.c
			libtiff/tif_warning.c
			libtiff/tif_win3.c
			libtiff/tif_win32.c
			libtiff/tif_wince.c
			libtiff/tif_write.c
			libtiff/tif_zip.c
			libtiff/tiff.h
			libtiff/tiffio.h
			libtiff/tiffiop.h
			libtiff/tiffvers.h
			libtiff/uvcode.h
			port/lfind.c)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS tiff_tiff_interface jpeg_jpeg zlib_zlib)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS assert.h ctype.h errno.h fcntl.h io.h malloc.h math.h memory.h search.h setjmp.h stdarg.h stdio.h stdlib.h string.h sys/stat.h sys/types.h unistd.h windows.h windowsx.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
