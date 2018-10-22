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

        ${CURRENT_ROOT_DIR}/gl/gl.cpp
        ${CURRENT_ROOT_DIR}/gl/types.hpp
        ${CURRENT_ROOT_DIR}/gl/context.cpp
        ${CURRENT_ROOT_DIR}/gl/attribute.cpp
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