# Automatically generated file, do not edit
SET(BII_IS_DEP False)


# LIBRARY inexor_code ##################################
# with interface inexor_code_interface

# Source code files of the library
SET(BII_LIB_SRC  inexor/engine/blend.cpp
			inexor/engine/client.cpp
			inexor/engine/command.cpp
			inexor/engine/console.cpp
			inexor/engine/iqm.h
			inexor/engine/lightmap.cpp
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
			inexor/engine/world.cpp)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS inexor_code_interface miguel_sdl2_mixer)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS fcntl.h set shellapi.h sys/stat.h sys/types.h unistd.h wchar.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/miguel/sdl2_mixer)


# Executables to be created
SET(BII_BLOCK_EXES inexor_engine_main
			inexor_engine_master
			inexor_engine_server
			inexor_test_main)

SET(BII_BLOCK_TESTS )


# EXECUTABLE inexor_engine_master ##################################

SET(BII_inexor_engine_master_SRC inexor/engine/master.cpp)
SET(BII_inexor_engine_master_DEPS inexor_code_interface inexor_code)
# System included headers
SET(BII_inexor_engine_master_SYSTEM_HEADERS signal.h sys/types.h)
# Required include paths
SET(BII_inexor_engine_master_INCLUDE_PATHS )


# EXECUTABLE inexor_test_main ##################################

SET(BII_inexor_test_main_SRC inexor/test/main.cpp)
SET(BII_inexor_test_main_DEPS inexor_code_interface google_gtest)
# System included headers
SET(BII_inexor_test_main_SYSTEM_HEADERS )
# Required include paths
SET(BII_inexor_test_main_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/google/gtest/include)


# EXECUTABLE inexor_engine_server ##################################

SET(BII_inexor_engine_server_SRC inexor/engine/server.cpp)
SET(BII_inexor_engine_server_DEPS inexor_code_interface inexor_code)
# System included headers
SET(BII_inexor_engine_server_SYSTEM_HEADERS shellapi.h)
# Required include paths
SET(BII_inexor_engine_server_INCLUDE_PATHS )


# EXECUTABLE inexor_engine_main ##################################

SET(BII_inexor_engine_main_SRC inexor/engine/main.cpp)
SET(BII_inexor_engine_main_DEPS inexor_code_interface inexor_code)
# System included headers
SET(BII_inexor_engine_main_SYSTEM_HEADERS )
# Required include paths
SET(BII_inexor_engine_main_INCLUDE_PATHS )
