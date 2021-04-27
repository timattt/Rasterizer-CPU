# Fundamental study of computers
This repository contains theoretical minimums and projects for the following computer science topics: operating systems, 3D graphics.
Projects presented here: Processor Rasterizer.

# English version
You can find english version of this README [here](https://github.com/timattt/Computer-science-knowledge/blob/master/README_EN.md)

# Schematic overview of tasks from this repository on 3D graphics
![](https://github.com/timattt/Computer-science-knowledge/blob/master/about/SYNOPSIS_SCHEME.png)

# Rasterizer on CPU

## Formulation of the problem
We want to emulate the work of a GPU on a CPU, as well as build the entire cycle of operations of classic OpenGL.
We have initial data about space and objects in it (in the example, a cube, which means we have the coordinates of its vertices in its local space, a texture is stretched over the cube,
then we have the texture coordinates of the vertices and the picture itself), our task is to project it all from three-dimensional space into two-dimensional space and draw it in the screen buffer.
The screen buffer is provided by the OS. In this case, we use winapi.

## Example
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/NiceExample.gif)

## A more complex example
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/FINAL_EXAMPLE.gif)

## Theoremminum

### CMake
Good video [here](https://www.youtube.com/watch?v=gSTLzOmFChs)
But [here](https://stackoverflow.com/questions/59095842/cmake-mingw-compilation-on-windows-without-needing-the-g-mingw-makefiles-f) it is written about how to use with MinGW
But [here](https://stackoverflow.com/questions/52255867/adding-a-dll-to-cmake) says how to connect libraries
And here [here](https://stackoverflow.com/questions/34799916/copy-file-from-source-directory-to-binary-directory-using-cmake) and [here] (https://stackoverflow.com / questions / 697560 / how-to-copy-directory-from-source-tree-to-binary-tree) information on how to copy files

### Assimp
Examples to get started [here](http://assimp.sourceforge.net/lib_html/usage.html)

### Perspective projection matrix
Good article [here](https://habr.com/ru/post/252771/)

### GDI
Examples of use [here](https://zetcode.com/gui/winapi/gdi/)

### Checking whether a point belongs to a triangle
Good article [here](https://cpp.mazurok.com/triangle/)

### General concept
Excellent article [here](https://habr.com/ru/post/257107/)

### Phong Lighting Model
Two good articles [here](https://compgraphics.info/3D/lighting/phong_reflection_model.php) and [here] (https://ravesli.com/urok-11-bazovoe-osveshhenie-v-opengl/)

## Work organization
The logic is as follows: the code is divided into two parts - the rasterizer itself and the system window for testing.
The code is written in such a way that the rasterizer can be easily implemented on any system, it is enough to specify the function for drawing the pixel and call the necessary drawing functions.