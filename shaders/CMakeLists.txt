
set(SHADER_DIR shaders)
set(IN_SHADER_DIR ${CMAKE_SOURCE_DIR}/${SHADER_DIR})
set(OUT_SHADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/${SHADER_DIR})

file(MAKE_DIRECTORY ${OUT_SHADER_DIR})

set(SHADERS
    vertexShader.glsl
    fragmentShader.glsl
)

foreach(S IN LISTS SHADERS)
    configure_file(${IN_SHADER_DIR}/${S} ${OUT_SHADER_DIR}/${S} COPYONLY)
endforeach()

