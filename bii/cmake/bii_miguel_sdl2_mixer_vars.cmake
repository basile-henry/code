# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY miguel_sdl2_mixer ##################################
# with interface miguel_sdl2_mixer_interface

# Source code files of the library
SET(BII_LIB_SRC  SDL_mixer.h
			dynamic_flac.c
			dynamic_flac.h
			dynamic_fluidsynth.c
			dynamic_fluidsynth.h
			dynamic_mod.c
			dynamic_mod.h
			dynamic_modplug.c
			dynamic_modplug.h
			dynamic_mp3.c
			dynamic_mp3.h
			dynamic_ogg.c
			dynamic_ogg.h
			effect_position.c
			effect_stereoreverse.c
			effects_internal.c
			effects_internal.h
			fluidsynth.c
			fluidsynth.h
			load_aiff.c
			load_aiff.h
			load_flac.c
			load_flac.h
			load_ogg.c
			load_ogg.h
			load_voc.c
			load_voc.h
			mixer.c
			music.c
			music_cmd.c
			music_cmd.h
			music_flac.c
			music_flac.h
			music_mad.c
			music_mad.h
			music_mod.c
			music_mod.h
			music_modplug.c
			music_modplug.h
			music_ogg.c
			music_ogg.h
			timidity/common.c
			timidity/common.h
			timidity/config.h
			timidity/ctrlmode.c
			timidity/ctrlmode.h
			timidity/filter.c
			timidity/filter.h
			timidity/instrum.c
			timidity/instrum.h
			timidity/mix.c
			timidity/mix.h
			timidity/output.c
			timidity/output.h
			timidity/playmidi.c
			timidity/playmidi.h
			timidity/readmidi.c
			timidity/readmidi.h
			timidity/resample.c
			timidity/resample.h
			timidity/sdl_a.c
			timidity/sdl_c.c
			timidity/tables.c
			timidity/tables.h
			timidity/timidity.c
			timidity/timidity.h
			wavestream.c
			wavestream.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS miguel_sdl2_mixer_interface miguel_sdl2 miguel_smpeg miguel_vorbis)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS assert.h ctype.h errno.h limits.h math.h signal.h stdarg.h stdio.h stdlib.h string.h sys/types.h unistd.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS )


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
