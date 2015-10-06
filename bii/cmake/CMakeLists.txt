PROJECT( code )
cmake_minimum_required(VERSION 3.0)

# Set project layout variables
SET(BII_PROJECT_ROOT "/home/fohlen/workspace/inexor/code")
SET(BII_BLOCKS_DIR blocks)
SET(BII_DEPS_DIR bii/deps)
SET(BII_LIB_DIR bii/lib)
SET(BII_CMAKE_DIR bii/cmake)
SET(BII_BIN_DIR bii/bin)
set(CMAKE_MODULE_PATH "${BII_PROJECT_ROOT}/blocks"
					  "${BII_PROJECT_ROOT}/bii/deps")

# inclusion of general biicode macros, biicode.cmake 
INCLUDE(biicode.cmake) 
IF (${CMAKE_SYSTEM_NAME} STREQUAL "Arduino")
	OPTION(BII_DEPS_SYSTEM "Handle deps as SYSTEM, avoiding warnings" OFF)
ELSE()
	OPTION(BII_DEPS_SYSTEM "Handle deps as SYSTEM, avoiding warnings" ON)
ENDIF()
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BII_PROJECT_ROOT}/bii/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BII_PROJECT_ROOT}/bii/bin)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BII_PROJECT_ROOT}/bii/bin)

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BII_PROJECT_ROOT}/bii/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${BII_PROJECT_ROOT}/bii/lib)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${BII_PROJECT_ROOT}/bii/lib)

# Including /blocks and /deps directories
INCLUDE_DIRECTORIES(${BII_PROJECT_ROOT}/blocks)
IF(BII_DEPS_SYSTEM)
	INCLUDE_DIRECTORIES(SYSTEM ${BII_PROJECT_ROOT}/bii/deps)
ELSE()
	INCLUDE_DIRECTORIES(${BII_PROJECT_ROOT}/bii/deps)
ENDIF()
ADD_DEFINITIONS(-DBIICODE)
SET(BIICODE_ENV_DIR "/home/fohlen/.biicode")

#artifact to allow upstream configurations
BII_PREBUILD_STEP(bii/deps/google/gtest)
BII_PREBUILD_STEP(bii/deps/miguel/ogg)
BII_PREBUILD_STEP(bii/deps/miguel/sdl2)
BII_PREBUILD_STEP(bii/deps/miguel/vorbis)
BII_PREBUILD_STEP(bii/deps/miguel/smpeg)
BII_PREBUILD_STEP(bii/deps/miguel/sdl2_mixer)
BII_PREBUILD_STEP(inexor/code)

# Enable tests with CTest
enable_testing()
# Creating a custom target which will bring associated
# all the test targets
add_custom_target(biitest)

# Inclusion of the blocks affected by the build
BII_INCLUDE_BLOCK(bii/deps/google/gtest)
BII_INCLUDE_BLOCK(bii/deps/miguel/ogg)
BII_INCLUDE_BLOCK(bii/deps/miguel/sdl2)
BII_INCLUDE_BLOCK(bii/deps/miguel/vorbis)
BII_INCLUDE_BLOCK(bii/deps/miguel/smpeg)
BII_INCLUDE_BLOCK(bii/deps/miguel/sdl2_mixer)
BII_INCLUDE_BLOCK(inexor/code)
