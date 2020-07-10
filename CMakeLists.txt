cmake_minimum_required(VERSION 3.9)
project(qt_opengl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5WebEngineWidgets)

add_library(loadshader STATIC lib/loadshader/LoadShader.hpp lib/loadshader/LoadShader.cpp)
target_link_libraries(loadshader PUBLIC "-framework OpenGL")

add_library(loadtexture lib/loadtexture/vermilion.hpp lib/loadtexture/loadtexture.cpp)
target_link_libraries(loadtexture "-framework OpenGL")

include(qt_graphics/qt_graphics.cmake)
include(vermilion/vermilion.cmake)
include(mapbox/mapbox.cmake)

# Qt codecs
add_executable(qt_codecs qt_codecs/main.cpp qt_codecs/mainwindow.cpp qt_codecs/mainwindow.hpp qt_codecs/previewform.cpp qt_codecs/previewform.hpp)
target_link_libraries(qt_codecs Qt5::Widgets)
# Qt codecs -- end

add_executable(web_engine qt_web_engine/main.cpp)
target_link_libraries(web_engine Qt5::Widgets Qt5::WebEngineWidgets)






