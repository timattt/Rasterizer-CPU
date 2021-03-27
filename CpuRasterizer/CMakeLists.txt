cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(Rasterizer)

add_executable(Rasterizer Core/Rasterizator/FragmentShader.c Core/Rasterizator/VertexShader.c Core/Rasterizator/Math.c Core/Rasterizator/Rasterizer.c Core/GUITest/GraphicsTest.c Core/GUITest/Window.c)