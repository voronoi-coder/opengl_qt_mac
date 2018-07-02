cmake_minimum_required(VERSION 3.9)
project(qt_opengl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets)
find_package(Qt5OpenGL)

add_executable(Triangle triangle/main.cpp triangle/openglwindow.cpp triangle/openglwindow.h)
target_link_libraries(Triangle Qt5::Widgets)

add_executable(textures textures/main.cpp textures/glwidget.hpp textures/glwidget.cpp
        textures/windows.hpp textures/windows.cpp textures/textures.qrc)
target_link_libraries(textures Qt5::Widgets)

add_executable(2dpainting 2dpainting/main.cpp 2dpainting/window.cpp 2dpainting/window.hpp 2dpainting/helper.cpp 2dpainting/helper.hpp 2dpainting/widget.cpp 2dpainting/widget.hpp 2dpainting/glwidget.cpp 2dpainting/glwidget.hpp)
target_link_libraries(2dpainting Qt5::Widgets)

add_executable(cube cube/main.cpp cube/mainwidget.cpp cube/mainwidget.hpp cube/geometryengine.cpp cube/geometryengine.hpp
        cube/shaders.qrc cube/textures.qrc)
target_link_libraries(cube Qt5::Widgets)

add_executable(hellogl2 hellogl2/main.cpp hellogl2/main.cpp hellogl2/mainwindow.cpp hellogl2/mainwindow.hpp
        hellogl2/window.cpp hellogl2/window.hpp hellogl2/glwidget.cpp hellogl2/glwidget.hpp hellogl2/logo.cpp hellogl2/logo.hpp)
target_link_libraries(hellogl2 Qt5::Widgets)

add_executable(keypress keypress/main.cpp keypress/glwidget.cpp keypress/glwidget.hpp)
target_link_libraries(keypress Qt5::OpenGL Qt5::Widgets)