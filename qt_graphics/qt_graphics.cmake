set(CURRENT_ROOT_DIR qt_graphics)
set(QT_GRAPHICS_EXAMPLES
        2dpainting
        cube
        hellogl2
        qt_graphics_keypress
        opengl_window
        qt_mult_glwidget
        textures)

add_executable(2dpainting
        ${CURRENT_ROOT_DIR}/2dpainting/main.cpp
        ${CURRENT_ROOT_DIR}/2dpainting/window.cpp
        ${CURRENT_ROOT_DIR}/2dpainting/helper.cpp
        ${CURRENT_ROOT_DIR}/2dpainting/widget.cpp
        ${CURRENT_ROOT_DIR}/2dpainting/glwidget.cpp)

add_executable(cube
        ${CURRENT_ROOT_DIR}/cube/main.cpp
        ${CURRENT_ROOT_DIR}/cube/mainwidget.cpp
        ${CURRENT_ROOT_DIR}/cube/geometryengine.cpp
        ${CURRENT_ROOT_DIR}/cube/shaders.qrc
        ${CURRENT_ROOT_DIR}/cube/textures.qrc)

add_executable(hellogl2
        ${CURRENT_ROOT_DIR}/hellogl2/main.cpp
        ${CURRENT_ROOT_DIR}/hellogl2/mainwindow.cpp
        ${CURRENT_ROOT_DIR}/hellogl2/window.cpp
        ${CURRENT_ROOT_DIR}/hellogl2/glwidget.cpp
        ${CURRENT_ROOT_DIR}/hellogl2/logo.cpp)

add_executable(qt_graphics_keypress
        ${CURRENT_ROOT_DIR}/qt_graphics_keypress/main.cpp
        ${CURRENT_ROOT_DIR}/qt_graphics_keypress/glwidget.cpp)

add_executable(opengl_window
        ${CURRENT_ROOT_DIR}/opengl_window/main.cpp
        ${CURRENT_ROOT_DIR}/opengl_window/openglwindow.cpp)

add_executable(qt_mult_glwidget
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/main.cpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/mainwindow.cpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/mainwindow.hpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/calculator.cpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/calculator.hpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/button.cpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/glwidget.cpp
        ${CURRENT_ROOT_DIR}/qt_mult_glwidget/mainwindow2.cpp)

add_executable(textures
        ${CURRENT_ROOT_DIR}/textures/main.cpp
        ${CURRENT_ROOT_DIR}/textures/glwidget.cpp
        ${CURRENT_ROOT_DIR}/textures/windows.cpp
        ${CURRENT_ROOT_DIR}/textures/textures.qrc)

foreach(QT_GRAPHICS_EXAMPLE ${QT_GRAPHICS_EXAMPLES})
    target_include_directories(${QT_GRAPHICS_EXAMPLE} PUBLIC ${CURRENT_ROOT_DIR}/${QT_GRAPHICS_EXAMPLE})
    target_link_libraries(${QT_GRAPHICS_EXAMPLE} Qt5::Widgets)
endforeach(QT_GRAPHICS_EXAMPLE)