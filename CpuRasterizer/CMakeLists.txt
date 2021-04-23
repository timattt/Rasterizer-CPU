cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Rasterizer)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O3")

include_directories("${PROJECT_SOURCE_DIR}/External/Assimp/include")

add_library(Rasterizer Core/Rasterizator/Loader.c Core/Rasterizator/Texture.c Core/Rasterizator/FragmentShader.c Core/Rasterizator/VertexShader.c Core/Rasterizator/Math.c Core/Rasterizator/Rasterizer.c)
add_executable(RasterizerTest Core/GUITest/GraphicsTest.c Core/GUITest/Window.c)

target_link_libraries(RasterizerTest Rasterizer)
target_link_libraries(RasterizerTest "${PROJECT_SOURCE_DIR}/External/Assimp/libassimp.dll")

configure_file("${PROJECT_SOURCE_DIR}/External/Assimp/libassimp.dll" "${CMAKE_CURRENT_BINARY_DIR}/libassimp.dll" COPYONLY)
file(COPY "${PROJECT_SOURCE_DIR}/Resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")