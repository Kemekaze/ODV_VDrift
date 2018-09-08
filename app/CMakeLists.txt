cmake_minimum_required(VERSION 3.5)
project(vDODV)

set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Isrc -I/usr/include/SDL2")
#SET(CMAKE_EXE_LINKER_FLAGS   "-Lbuild -Lsrc -Llib -L/usr/lib/x86_64-linux-gnu -lBulletSoftBody -lBulletDynamics -lBulletCollision -lLinearMath -lSDL2 -lGL -lpthread -lSDL2_image -lvorbisfile -lcurl " CACHE INTERNAL "" FORCE)
#/usr/bin/g++ -isystem /app/build -I/usr/include/bullet  -c -Wall -Wextra -Wno-unused-parameter -g3 -D_REENTRANT -Isrc -I/usr/include/SDL2   -std=gnu++14   -c /app/lib/_vdrift/loadcamera.cpp
#g++ -o build/loadcamera.o -c -Wall -Wextra -Wno-unused-parameter -g3 -D_REENTRANT -Isrc -I/usr/include/bullet -I/usr/include/SDL2 src/loadcamera.cpp
#g++ -o build/vdrift -lvorbisfile -lcurl



find_package(libcluon REQUIRED)
find_package(Bullet REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(CURL REQUIRED)

include_directories(
 SYSTEM ${CMAKE_BINARY_DIR}
 ${CLUON_INCLUDE_DIRS}
 ${BULLET_INCLUDE_DIR}
 ${SDL2_INCLUDE_DIR}
 ${OPENGL_INCLUDE_DIR}
 ${CURL_INCLUDE_DIRS}
 ${CMAKE_CURRENT_SOURCE_DIR}/lib
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/ai
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cfg
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/content
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics
 ${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/sound
)

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp /config/messages.odvd
                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp /config/messages.odvd
                   DEPENDS /config/messages.odvd)

add_executable(${PROJECT_NAME}
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/cardynamics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/game.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/trackloader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/vdrift.cpp
${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/cluon_handler.cpp
${CMAKE_BINARY_DIR}/messages.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/aabb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/aabbtree.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/ai/ai_car_experimental.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/ai/ai_car_standard.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/ai/ai.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/autoupdate.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/bezier.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/camera_chase.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/camera_free.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/camera_mount.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/camera_orbit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/carcontrolmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cargraphics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/carsound.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cfg/config.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cfg/ptree.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cfg/ptree_inf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cfg/ptree_ini.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/cfg/ptree_xml.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/containeralgorithm.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/content/configfactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/content/contentmanager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/content/modelfactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/content/soundfactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/content/texturefactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/crashdetection.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/downloadable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/dynamicsdraw.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/eventsystem.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/forcefeedback.cpp

${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/dds.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/drawable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/fbobject.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/fbtexture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/glenums.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/glwrapper.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/renderdimensions.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/renderer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/rendermodel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/rendermodelext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/renderpass.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/rendersampler.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/renderstate.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/rendertextureentry.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/renderuniform.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/renderuniformentry.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/gl3v/stringidmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/glcore.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/glutil.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/graphics_config_condition.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/graphics_config.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/graphics_gl2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/graphics_gl3v.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/mesh_gen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/model.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/model_joe03.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/model_obj.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/render_input_postprocess.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/render_input_scene.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/render_output.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/scenenode.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/shader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/sky.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/texture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/vertexarray.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/vertexbuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/graphics/vertexformat.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/font.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guicontrol.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guicontrollist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/gui.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guiimage.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guiimagelist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guilabel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guilabellist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guilanguage.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guioption.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guipage.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guislider.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guiwidget.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/guiwidgetlist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/gui/text_draw.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/http.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/hudbar.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/hud.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/hudgauge.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/joepack.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/joeserialize.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/k1999.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/keyed_container.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/linearinterp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/loadcamera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/loadcollisionshape.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/loaddrawable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/loadingscreen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/mathplane.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/mathvector.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/matrix4.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/optional.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/parallel_task.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/particle.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/pathmanager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/performance_testing.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/cardifferential.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/carengine.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/carsuspension.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/cartire.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/dynamicsworld.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/fracturebody.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/physics/tire.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/quaternion.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/radix.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/random.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/replay.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/reseatable_reference.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/roadpatch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/roadstrip.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/settings.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/sound/soundbuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/sound/sound.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/sound/soundfilter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/sprite2d.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/suspensionbumpdetection.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/svn_sourceforge.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/timer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/toggle.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/track.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/trackmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/updatemanager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/utils.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/_vdrift/window.cpp
)

target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${BULLET_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} "-lvorbisfile")
