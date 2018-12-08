set(CURRENT_ROOT_DIR mapbox)
set(MAPBOX_EXAMPLES
        drawcircle
        drawline
        clip_plane
        outline
        )

add_library(mapboxgl
        ${CURRENT_ROOT_DIR}/gl/gl_impl.hpp
        ${CURRENT_ROOT_DIR}/util/optional.hpp
        ${CURRENT_ROOT_DIR}/util/nocopyable.hpp
        ${CURRENT_ROOT_DIR}/util/ignore.hpp
        ${CURRENT_ROOT_DIR}/util/unique_resource.hpp
        ${CURRENT_ROOT_DIR}/util/type_list.hpp
        ${CURRENT_ROOT_DIR}/util/indexed_tuple.hpp

        ${CURRENT_ROOT_DIR}/gl/gl.cpp
        ${CURRENT_ROOT_DIR}/gl/types.hpp
        ${CURRENT_ROOT_DIR}/gl/context.cpp
        ${CURRENT_ROOT_DIR}/gl/attribute.cpp
        ${CURRENT_ROOT_DIR}/gl/vertex_buffer.hpp
        ${CURRENT_ROOT_DIR}/gl/object.hpp
        ${CURRENT_ROOT_DIR}/gl/object.cpp
        ${CURRENT_ROOT_DIR}/gl/primitives.hpp
        ${CURRENT_ROOT_DIR}/gl/draw_mode.hpp
)

target_include_directories(mapboxgl
        PRIVATE ${CURRENT_ROOT_DIR}/gl
        PRIVATE ${CURRENT_ROOT_DIR})

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