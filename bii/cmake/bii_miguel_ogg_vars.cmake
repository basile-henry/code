# Automatically generated file, do not edit
SET(BII_IS_DEP True)


# LIBRARY miguel_ogg ##################################
# with interface miguel_ogg_interface

# Source code files of the library
SET(BII_LIB_SRC  include/ogg/ogg.h
			include/ogg/os_types.h
			src/bitwise.c
			src/framing.c)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS miguel_ogg_interface )
# System included headers
SET(BII_LIB_SYSTEM_HEADERS inttypes.h limits.h stddef.h stdint.h stdio.h stdlib.h string.h sys/types.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/miguel/ogg/include)


# Executables to be created
SET(BII_BLOCK_EXES )

SET(BII_BLOCK_TESTS )
