# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY google_libwebp ##################################
# with interface google_libwebp_interface

# Source code files of the library
SET(BII_LIB_SRC  dec/alpha.c
			dec/buffer.c
			dec/decode_vp8.h
			dec/frame.c
			dec/idec.c
			dec/io.c
			dec/layer.c
			dec/quant.c
			dec/tree.c
			dec/vp8.c
			dec/vp8i.h
			dec/vp8l.c
			dec/vp8li.h
			dec/webp.c
			dec/webpi.h
			dsp/cpu.c
			dsp/dec.c
			dsp/dec_neon.c
			dsp/dec_sse2.c
			dsp/dsp.h
			dsp/enc.c
			dsp/enc_neon.c
			dsp/enc_sse2.c
			dsp/lossless.c
			dsp/lossless.h
			dsp/upsampling.c
			dsp/upsampling_neon.c
			dsp/upsampling_sse2.c
			dsp/yuv.c
			dsp/yuv.h
			enc/alpha.c
			enc/analysis.c
			enc/backward_references.c
			enc/backward_references.h
			enc/config.c
			enc/cost.c
			enc/cost.h
			enc/filter.c
			enc/frame.c
			enc/histogram.c
			enc/histogram.h
			enc/iterator.c
			enc/layer.c
			enc/picture.c
			enc/quant.c
			enc/syntax.c
			enc/token.c
			enc/tree.c
			enc/vp8enci.h
			enc/vp8l.c
			enc/vp8li.h
			enc/webpenc.c
			utils/bit_reader.c
			utils/bit_reader.h
			utils/bit_writer.c
			utils/bit_writer.h
			utils/color_cache.c
			utils/color_cache.h
			utils/filters.c
			utils/filters.h
			utils/huffman.c
			utils/huffman.h
			utils/huffman_encode.c
			utils/huffman_encode.h
			utils/quant_levels.c
			utils/quant_levels.h
			utils/quant_levels_dec.c
			utils/quant_levels_dec.h
			utils/rescaler.c
			utils/rescaler.h
			utils/thread.c
			utils/thread.h
			utils/utils.c
			utils/utils.h
			webp/decode.h
			webp/encode.h
			webp/format_constants.h
			webp/mux_types.h
			webp/types.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS google_libwebp_interface )
# System included headers
SET(BII_LIB_SYSTEM_HEADERS assert.h emmintrin.h intrin.h inttypes.h math.h process.h pthread.h stddef.h stdio.h stdlib.h string.h windows.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
