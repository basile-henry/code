# Automatically generated file, do not edit
SET(BII_IS_DEP False)


# LIBRARY inexor_code ##################################
# with interface inexor_code_interface

# Source code files of the library
SET(BII_LIB_SRC  inexor/engine/3dgui.cpp
			inexor/engine/animmodel.h
			inexor/engine/bih.cpp
			inexor/engine/bih.h
			inexor/engine/blend.cpp
			inexor/engine/blob.cpp
			inexor/engine/client.cpp
			inexor/engine/command.cpp
			inexor/engine/console.cpp
			inexor/engine/decal.cpp
			inexor/engine/depthfx.h
			inexor/engine/dynlight.cpp
			inexor/engine/engine.h
			inexor/engine/explosion.h
			inexor/engine/glare.cpp
			inexor/engine/glemu.cpp
			inexor/engine/glemu.h
			inexor/engine/glexts.h
			inexor/engine/grass.cpp
			inexor/engine/iqm.h
			inexor/engine/lensflare.h
			inexor/engine/lightmap.cpp
			inexor/engine/lightmap.h
			inexor/engine/lightning.h
			inexor/engine/main.cpp
			inexor/engine/master.cpp
			inexor/engine/material.cpp
			inexor/engine/md2.h
			inexor/engine/md3.h
			inexor/engine/md5.h
			inexor/engine/menus.cpp
			inexor/engine/model.h
			inexor/engine/movie.cpp
			inexor/engine/mpr.h
			inexor/engine/normal.cpp
			inexor/engine/obj.h
			inexor/engine/octa.cpp
			inexor/engine/octa.h
			inexor/engine/octaedit.cpp
			inexor/engine/octarender.cpp
			inexor/engine/physics.cpp
			inexor/engine/pvs.cpp
			inexor/engine/ragdoll.h
			inexor/engine/rendergl.cpp
			inexor/engine/rendermodel.cpp
			inexor/engine/renderparticles.cpp
			inexor/engine/rendersky.cpp
			inexor/engine/rendertarget.h
			inexor/engine/rendertext.cpp
			inexor/engine/renderva.cpp
			inexor/engine/scale.h
			inexor/engine/server.cpp
			inexor/engine/serverbrowser.cpp
			inexor/engine/shader.cpp
			inexor/engine/shadowmap.cpp
			inexor/engine/skelmodel.h
			inexor/engine/smd.h
			inexor/engine/sound.cpp
			inexor/engine/textedit.h
			inexor/engine/texture.cpp
			inexor/engine/texture.h
			inexor/engine/vertmodel.h
			inexor/engine/water.cpp
			inexor/engine/world.cpp
			inexor/engine/world.h
			inexor/engine/worldio.cpp
			inexor/fpsgame/ai.cpp
			inexor/fpsgame/ai.h
			inexor/fpsgame/aiman.h
			inexor/fpsgame/bomb.h
			inexor/fpsgame/capture.h
			inexor/fpsgame/client.cpp
			inexor/fpsgame/collect.h
			inexor/fpsgame/ctf.h
			inexor/fpsgame/entities.cpp
			inexor/fpsgame/extinfo.h
			inexor/fpsgame/fps.cpp
			inexor/fpsgame/game.h
			inexor/fpsgame/hideandseek.h
			inexor/fpsgame/monster.cpp
			inexor/fpsgame/movable.cpp
			inexor/fpsgame/render.cpp
			inexor/fpsgame/scoreboard.cpp
			inexor/fpsgame/server.cpp
			inexor/fpsgame/waypoint.cpp
			inexor/fpsgame/weapon.cpp
			inexor/rpc/SharedVar.h
			inexor/shared/command.h
			inexor/shared/crypto.cpp
			inexor/shared/cube.h
			inexor/shared/ents.h
			inexor/shared/filesystem.cpp
			inexor/shared/filesystem.h
			inexor/shared/geom.cpp
			inexor/shared/geom.h
			inexor/shared/iengine.h
			inexor/shared/igame.h
			inexor/shared/json.cpp
			inexor/shared/json.h
			inexor/shared/stream.cpp
			inexor/shared/tools.cpp
			inexor/shared/tools.h
			inexor/shared/zip.cpp
			inexor/ui/CefSubsystem.cpp
			inexor/ui/CefSubsystem.h
			inexor/ui/cefapp.cpp
			inexor/ui/cefapp.h
			inexor/ui/cefbrowsersettings.h
			inexor/ui/cefcontextbindings.h
			inexor/ui/cefcontextmanager.cpp
			inexor/ui/cefcontextmanager.h
			inexor/ui/cefcontextprovider.cpp
			inexor/ui/cefcontextprovider.h
			inexor/ui/cefframe.cpp
			inexor/ui/cefframe.h
			inexor/ui/cefkeyboard.cpp
			inexor/ui/cefkeyboard.h
			inexor/ui/ceflayer.cpp
			inexor/ui/ceflayer.h
			inexor/ui/ceflayermanager.cpp
			inexor/ui/ceflayermanager.h
			inexor/ui/ceflayerprovider.h
			inexor/ui/cefmouse.cpp
			inexor/ui/cefmouse.h
			inexor/ui/cefrenderhandler.cpp
			inexor/ui/cefrenderhandler.h
			inexor/ui/cefsettings.h
			inexor/ui/ceftypes.h
			inexor/ui/cefwindowinfo.h
			inexor/ui/ui.h
			inexor/util/InexorException.h
			inexor/util/Observe.h
			inexor/util/StringFormatter.cpp
			inexor/util/StringFormatter.h
			inexor/util/Subsystem.h
			inexor/util/util.h)
# STATIC by default if empty, or SHARED
SET(BII_LIB_TYPE )
# Dependencies to other libraries (user2_block2, user3_blockX)
SET(BII_LIB_DEPS inexor_code_interface miguel_sdl2 miguel_sdl2_mixer)
# System included headers
SET(BII_LIB_SYSTEM_HEADERS algorithm assert.h cstddef ctype.h direct.h dirent.h exception fcntl.h float.h functional initializer_list limits.h list map math.h new set shellapi.h shlobj.h signal.h sstream stdarg.h stdio.h stdlib.h string string.h sys/stat.h sys/types.h time.h unistd.h unordered_map utility wchar.h windows.h)
# Required include paths
SET(BII_LIB_INCLUDE_PATHS ${BII_PROJECT_ROOT}///
					${BII_PROJECT_ROOT}/bii/deps/miguel/sdl2/include
					${BII_PROJECT_ROOT}/bii/deps/miguel/sdl2_mixer)


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
SET(BII_inexor_engine_master_INCLUDE_PATHS ${BII_PROJECT_ROOT}///)


# EXECUTABLE inexor_test_main ##################################

SET(BII_inexor_test_main_SRC inexor/test/main.cpp)
SET(BII_inexor_test_main_DEPS inexor_code_interface google_gtest)
# System included headers
SET(BII_inexor_test_main_SYSTEM_HEADERS )
# Required include paths
SET(BII_inexor_test_main_INCLUDE_PATHS ${BII_PROJECT_ROOT}/bii/deps/google/gtest/include)


# EXECUTABLE inexor_engine_main ##################################

SET(BII_inexor_engine_main_SRC inexor/engine/main.cpp)
SET(BII_inexor_engine_main_DEPS inexor_code_interface inexor_code)
# System included headers
SET(BII_inexor_engine_main_SYSTEM_HEADERS )
# Required include paths
SET(BII_inexor_engine_main_INCLUDE_PATHS ${BII_PROJECT_ROOT}///)


# EXECUTABLE inexor_engine_server ##################################

SET(BII_inexor_engine_server_SRC inexor/engine/server.cpp)
SET(BII_inexor_engine_server_DEPS inexor_code_interface inexor_code)
# System included headers
SET(BII_inexor_engine_server_SYSTEM_HEADERS shellapi.h)
# Required include paths
SET(BII_inexor_engine_server_INCLUDE_PATHS ${BII_PROJECT_ROOT}///)
