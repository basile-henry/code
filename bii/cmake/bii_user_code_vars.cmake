# Automatically generated file, do not edit
SET(BII_IS_DEP False)


# LIBRARY user_code ##################################
# with interface user_code_interface

# Source code files of the library
SET(BII_LIB_SRC  inexor/engine/blend.cpp
			inexor/engine/client.cpp
			inexor/engine/command.cpp
			inexor/engine/console.cpp
			inexor/engine/iqm.h
			inexor/engine/lightmap.cpp
			inexor/engine/main.cpp
			inexor/engine/md2.h
			inexor/engine/md3.h
			inexor/engine/md5.h
			inexor/engine/obj.h
			inexor/engine/octaedit.cpp
			inexor/engine/physics.cpp
			inexor/engine/rendergl.cpp
			inexor/engine/rendermodel.cpp
			inexor/engine/renderva.cpp
			inexor/engine/server.cpp
			inexor/engine/shader.cpp
			inexor/engine/smd.h
			inexor/engine/sound.cpp
			inexor/engine/texture.cpp
			inexor/engine/water.cpp
			inexor/engine/world.cpp
			inexor/libraries/muparser/samples/example1/example1.cpp)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS user_code_interface latinga_sdl2_image miguel_sdl2_mixer)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS cmath crtdbg.h cstdlib cstring fcntl.h iomanip ios iostream limits locale numeric set shellapi.h stdlib.h string sys/stat.h sys/types.h unistd.h wchar.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/miguel/sdl2_mixer
					${BII_PROJECT_ROOT}/bii/deps/latinga/sdl2_image)


# Executables to be created
SET(BII_BLOCK_EXES inexor_engine_main
			inexor_engine_master
			inexor_engine_server
			inexor_libraries_muparser_samples_example1_example1
			inexor_libraries_muparser_samples_example2_example2
			inexor_test_main)

SET(BII_BLOCK_TESTS )


# EXECUTABLE inexor_test_main ##################################

SET(BII_inexor_test_main_SRC inexor/test/main.cpp)
SET(BII_inexor_test_main_DEPS user_code_interface google_gtest)
# System included headers
SET(BII_inexor_test_main_SYSTEM_HEADERS )
# Required include paths
SET(BII_inexor_test_main_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/google/gtest/include)


# EXECUTABLE inexor_libraries_muparser_samples_example1_example1 ##################################

SET(BII_inexor_libraries_muparser_samples_example1_example1_SRC inexor/libraries/muparser/samples/example1/example1.cpp)
SET(BII_inexor_libraries_muparser_samples_example1_example1_DEPS user_code_interface )
# System included headers
SET(BII_inexor_libraries_muparser_samples_example1_example1_SYSTEM_HEADERS cmath crtdbg.h cstdlib cstring iomanip ios iostream limits locale numeric stdlib.h string)
# Required include paths
SET(BII_inexor_libraries_muparser_samples_example1_example1_INCLUDE_PATHS )


# EXECUTABLE inexor_libraries_muparser_samples_example2_example2 ##################################

SET(BII_inexor_libraries_muparser_samples_example2_example2_SRC inexor/libraries/muparser/samples/example2/example2.c)
SET(BII_inexor_libraries_muparser_samples_example2_example2_DEPS user_code_interface user_code)
# System included headers
SET(BII_inexor_libraries_muparser_samples_example2_example2_SYSTEM_HEADERS stdio.h stdlib.h string.h)
# Required include paths
SET(BII_inexor_libraries_muparser_samples_example2_example2_INCLUDE_PATHS )


# EXECUTABLE inexor_engine_master ##################################

SET(BII_inexor_engine_master_SRC inexor/engine/master.cpp)
SET(BII_inexor_engine_master_DEPS user_code_interface user_code)
# System included headers
SET(BII_inexor_engine_master_SYSTEM_HEADERS signal.h sys/types.h)
# Required include paths
SET(BII_inexor_engine_master_INCLUDE_PATHS )


# EXECUTABLE inexor_engine_server ##################################

SET(BII_inexor_engine_server_SRC inexor/engine/server.cpp)
SET(BII_inexor_engine_server_DEPS user_code_interface user_code)
# System included headers
SET(BII_inexor_engine_server_SYSTEM_HEADERS shellapi.h)
# Required include paths
SET(BII_inexor_engine_server_INCLUDE_PATHS )


# EXECUTABLE inexor_engine_main ##################################

SET(BII_inexor_engine_main_SRC inexor/engine/main.cpp)
SET(BII_inexor_engine_main_DEPS user_code_interface user_code)
# System included headers
SET(BII_inexor_engine_main_SYSTEM_HEADERS )
# Required include paths
SET(BII_inexor_engine_main_INCLUDE_PATHS )
