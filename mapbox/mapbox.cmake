set(CURRENT_ROOT_DIR mapbox)
set(MAPBOX_EXAMPLES
        drawcircle
        drawline
        clip_plane)

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

foreach(EXAMPLE ${MAPBOX_EXAMPLES})
    target_include_directories(${EXAMPLE} PUBLIC ${CURRENT_ROOT_DIR}/${EXAMPLE})
    target_link_libraries(${EXAMPLE} Qt5::Widgets "-framework OpenGL" loadshader)
endforeach(EXAMPLE)