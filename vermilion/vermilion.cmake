set(CURRENT_ROOT_DIR vermilion)
set(VERMILION_EXAMPLES
        01_keypress
        02_uniformblock
        03_drawcommands
        03_instancing
        04_gouraud
        04_shadowmap
        06_statictexture)

foreach(EXAMPLE ${VERMILION_EXAMPLES})
    add_executable(${EXAMPLE}
            ${CURRENT_ROOT_DIR}/${EXAMPLE}/main.cpp
            ${CURRENT_ROOT_DIR}/${EXAMPLE}/${EXAMPLE}.cpp
            lib/vbm/vbm.cpp
            lib/vmath.h)

    set_property(TARGET ${EXAMPLE} PROPERTY DEBUG_POSTFIX _d)
    target_link_libraries(${EXAMPLE} Qt5::Core Qt5::Widgets "-framework OpenGL" loadshader)
endforeach(EXAMPLE)