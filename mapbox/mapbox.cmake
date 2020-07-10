set(CURRENT_ROOT_DIR mapbox)
set(MAPBOX_EXAMPLES
        drawcircle
        drawline
        clip_plane
        outline
        )

# Qt5 always build OpenGL ES2 which is the compatibility
# mode. Qt5 will take care of translating the desktop
# version of OpenGL to ES2.
add_definitions("-DMBGL_USE_GLES2")

add_library(mapboxgl
        ${CURRENT_ROOT_DIR}/util/optional.hpp
        ${CURRENT_ROOT_DIR}/util/nocopyable.hpp
        ${CURRENT_ROOT_DIR}/util/ignore.hpp
        ${CURRENT_ROOT_DIR}/util/unique_resource.hpp
        ${CURRENT_ROOT_DIR}/util/type_list.hpp
        ${CURRENT_ROOT_DIR}/util/indexed_tuple.hpp
        ${CURRENT_ROOT_DIR}/util/util.hpp
        ${CURRENT_ROOT_DIR}/util/color.hpp
        ${CURRENT_ROOT_DIR}/util/color.cpp
        ${CURRENT_ROOT_DIR}/util/csscolorparser.cpp
        ${CURRENT_ROOT_DIR}/util/size.hpp

        ${CURRENT_ROOT_DIR}/gl/platform/gl_functions.cpp
        ${CURRENT_ROOT_DIR}/gl/gl_functions.cpp

        ${CURRENT_ROOT_DIR}/gl/gfx/attribute.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/color_mode.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/cull_face_mode.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/depth_mode.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/draw_mode.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/primitives.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/stencil_mode.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/types.hpp
        ${CURRENT_ROOT_DIR}/gl/gfx/uniform.hpp

        ${CURRENT_ROOT_DIR}/gl/types.hpp
        ${CURRENT_ROOT_DIR}/gl/object.cpp
        ${CURRENT_ROOT_DIR}/gl/context.cpp
        ${CURRENT_ROOT_DIR}/gl/vertex_buffer.hpp
        ${CURRENT_ROOT_DIR}/gl/index_buffer.hpp
        ${CURRENT_ROOT_DIR}/gl/attribute.cpp
        ${CURRENT_ROOT_DIR}/gl/value.cpp
        ${CURRENT_ROOT_DIR}/gl/state.hpp
        ${CURRENT_ROOT_DIR}/gl/extension.hpp
        ${CURRENT_ROOT_DIR}/gl/vertex_array_extension.hpp
        ${CURRENT_ROOT_DIR}/gl/enum.cpp
)
target_link_libraries(mapboxgl Qt5::Widgets)

target_include_directories(mapboxgl
        PRIVATE ${CURRENT_ROOT_DIR}/gl
        PRIVATE ${CURRENT_ROOT_DIR}
        PRIVATE ${CURRENT_ROOT_DIR}/vendor/variant/include)

add_executable(drawcircle
        ${CURRENT_ROOT_DIR}/drawcircle/main.cpp
        ${CURRENT_ROOT_DIR}/drawcircle/glwidget.cpp
        ${CURRENT_ROOT_DIR}/drawcircle/circle.cpp)

add_executable(drawline
        ${CURRENT_ROOT_DIR}/drawline/main.cpp
        ${CURRENT_ROOT_DIR}/drawline/drawlinewidget.cpp
        ${CURRENT_ROOT_DIR}/drawline/resource/common.qrc)

add_executable(clip_plane
        ${CURRENT_ROOT_DIR}/clip_plane/main.cpp
        ${CURRENT_ROOT_DIR}/clip_plane/clipplanewidget.hpp
        ${CURRENT_ROOT_DIR}/clip_plane/clipplanewidget.cpp)

add_executable(outline
        ${CURRENT_ROOT_DIR}/outline/main.cpp
        ${CURRENT_ROOT_DIR}/outline/outlinewidget.cpp)

foreach(EXAMPLE ${MAPBOX_EXAMPLES})
    target_include_directories(${EXAMPLE} PUBLIC ${CURRENT_ROOT_DIR}/${EXAMPLE})
    target_link_libraries(${EXAMPLE} Qt5::Widgets "-framework OpenGL" loadshader)
endforeach(EXAMPLE)

add_executable(mapbox_test
        ${CURRENT_ROOT_DIR}/main.cpp)
target_include_directories(mapbox_test PRIVATE ${CURRENT_ROOT_DIR})
