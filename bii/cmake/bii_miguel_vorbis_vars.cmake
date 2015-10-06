# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY miguel_vorbis ##################################
# with interface miguel_vorbis_interface

# Source code files of the library
SET(BII_LIB_SRC  include/vorbis/codec.h
			include/vorbis/vorbisenc.h
			include/vorbis/vorbisfile.h
			lib/analysis.c
			lib/backends.h
			lib/bitrate.c
			lib/bitrate.h
			lib/block.c
			lib/books/coupled/res_books_51.h
			lib/books/coupled/res_books_stereo.h
			lib/books/floor/floor_books.h
			lib/books/uncoupled/res_books_uncoupled.h
			lib/codebook.c
			lib/codebook.h
			lib/codec_internal.h
			lib/envelope.c
			lib/envelope.h
			lib/floor0.c
			lib/floor1.c
			lib/highlevel.h
			lib/info.c
			lib/lookup.c
			lib/lookup.h
			lib/lookup_data.h
			lib/lpc.c
			lib/lpc.h
			lib/lsp.c
			lib/lsp.h
			lib/mapping0.c
			lib/masking.h
			lib/mdct.c
			lib/mdct.h
			lib/misc.h
			lib/modes/floor_all.h
			lib/modes/psych_11.h
			lib/modes/psych_16.h
			lib/modes/psych_44.h
			lib/modes/psych_8.h
			lib/modes/residue_16.h
			lib/modes/residue_44.h
			lib/modes/residue_44p51.h
			lib/modes/residue_44u.h
			lib/modes/residue_8.h
			lib/modes/setup_11.h
			lib/modes/setup_16.h
			lib/modes/setup_22.h
			lib/modes/setup_32.h
			lib/modes/setup_44.h
			lib/modes/setup_44p51.h
			lib/modes/setup_44u.h
			lib/modes/setup_8.h
			lib/modes/setup_X.h
			lib/os.h
			lib/psy.c
			lib/psy.h
			lib/registry.c
			lib/registry.h
			lib/res0.c
			lib/scales.h
			lib/sharedbook.c
			lib/smallft.c
			lib/smallft.h
			lib/synthesis.c
			lib/vorbisenc.c
			lib/vorbisfile.c
			lib/window.c
			lib/window.h
			vq/bookutil.c
			vq/bookutil.h
			vq/localcodebook.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS miguel_vorbis_interface miguel_ogg)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS alloca.h ctype.h emmintrin.h errno.h malloc.h math.h memory.h stdio.h stdlib.h string.h sys/time.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/miguel/vorbis/lib
					${BII_PROJECT_ROOT}/bii/deps/miguel/vorbis/include)


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
