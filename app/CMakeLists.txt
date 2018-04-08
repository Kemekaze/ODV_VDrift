cmake_minimum_required(VERSION 3.5)
project(vDODV)
set(CMAKE_CXX_STANDARD 14)

find_package(libcluon REQUIRED)
include_directories(SYSTEM ${CLUON_INCLUDE_DIRS})

add_custom_command(OUTPUT ${CMAKE_BINARY_DIR}/messages.cpp
                   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
                   COMMAND cluon-msc --cpp-sources --cpp-add-include-file=messages.hpp --out=${CMAKE_BINARY_DIR}/messages.cpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   COMMAND cluon-msc --cpp-headers --out=${CMAKE_BINARY_DIR}/messages.hpp ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd
                   DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/messages.odvd)
include_directories(SYSTEM ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME}
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/aabb.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/aabbtree.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/ai/ai_car_experimental.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/ai/ai_car_standard.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/ai/ai.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/autoupdate.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/bezier.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/camera_chase.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/camera_free.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/camera_mount.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/camera_orbit.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/carcontrolmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/cargraphics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/carsound.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/cfg/config.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/cfg/ptree.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/cfg/ptree_inf.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/cfg/ptree_ini.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/cfg/ptree_xml.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/containeralgorithm.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/content/configfactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/content/contentmanager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/content/modelfactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/content/soundfactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/content/texturefactory.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/crashdetection.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/downloadable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/dynamicsdraw.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/eventsystem.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/forcefeedback.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/game.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/dds.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/drawable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/fbobject.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/fbtexture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/glenums.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/glwrapper.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/renderdimensions.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/renderer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/rendermodel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/rendermodelext.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/renderpass.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/rendersampler.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/renderstate.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/rendertextureentry.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/renderuniform.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/renderuniformentry.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/gl3v/stringidmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/glcore.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/glutil.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/graphics_config_condition.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/graphics_config.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/graphics_gl2.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/graphics_gl3v.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/mesh_gen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/model.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/model_joe03.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/model_obj.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/render_input_postprocess.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/render_input_scene.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/render_output.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/scenenode.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/shader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/sky.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/texture.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/vertexarray.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/vertexbuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/graphics/vertexformat.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/font.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guicontrol.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guicontrollist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/gui.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guiimage.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guiimagelist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guilabel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guilabellist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guilanguage.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guioption.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guipage.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guislider.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guiwidget.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/guiwidgetlist.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/gui/text_draw.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/http.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/hudbar.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/hud.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/hudgauge.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/joepack.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/joeserialize.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/k1999.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/keyed_container.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/linearinterp.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/loadcamera.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/loadcollisionshape.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/loaddrawable.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/loadingscreen.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/vdrift.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/mathplane.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/mathvector.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/matrix4.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/optional.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/parallel_task.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/particle.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/pathmanager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/performance_testing.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/cardifferential.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/cardynamics.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/carengine.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/carsuspension.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/cartire.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/dynamicsworld.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/fracturebody.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/physics/tire.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/quaternion.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/radix.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/random.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/replay.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/reseatable_reference.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/roadpatch.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/roadstrip.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/settings.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/sound/soundbuffer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/sound/sound.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/sound/soundfilter.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/sprite2d.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/suspensionbumpdetection.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/svn_sourceforge.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/timer.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/toggle.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/track.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/trackloader.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/trackmap.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/updatemanager.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/utils.cpp
${CMAKE_CURRENT_SOURCE_DIR}/lib/vdrift/src/window.cpp
${CMAKE_CURRENT_SOURCE_DIR}/openVDrift.cpp
${CMAKE_BINARY_DIR}/messages.cpp



)
target_link_libraries(${PROJECT_NAME} ${CLUON_LIBRARIES})
