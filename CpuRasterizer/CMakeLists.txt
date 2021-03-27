cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Rasterizer)

add_library(Rasterizer Core/Rasterizator/FragmentShader.c Core/Rasterizator/VertexShader.c Core/Rasterizator/Math.c Core/Rasterizator/Rasterizer.c)
add_executable(RasterizerTest Core/GUITest/GraphicsTest.c Core/GUITest/Window.c)

target_link_libraries(RasterizerTest Rasterizer)