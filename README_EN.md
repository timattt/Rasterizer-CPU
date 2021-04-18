# Fundamental study of computer science
This repository contains theoretical minimums and projects for the following computer science topics: operating systems, 3D graphics.
Projects presented here: CPU rasterizer.

# Schematic overview of tasks from this repository on 3D graphics
![](https://github.com/timattt/Computer-science-knowledge/blob/master/about/SYNOPSIS_SCHEME.png)


## Formulation of the problem
We want to emulate the work of a GPU on a CPU, as well as build the entire cycle of operations of classic OpenGL.
We have initial data about space and objects in it (in the example, a cube, which means we have the coordinates of its vertices in its local space, a texture is stretched over the cube,
then we have the texture coordinates of the vertices and the picture itself), our task is to project it all from three-dimensional space into two-dimensional space and draw it in the screen buffer.
The screen buffer is provided by the OS. In this case, we use winapi.

## Example
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/NiceExample.gif)

## Code examples

### Fixed pipeline
```
int init() {
	// Init context
	InitContext();

	// Set pixel draw function
	SetFrameBufferCallFunction(SetFbPixel);

	// Set texture loader
	SetTextureLoader(loadTexture);

	// Texture
	LoadTexture((char*)(L"Texture.bmp"), &txtr);

	// Set vbo recognition mask
	SetVBOMask(VERTEX_COORDS | COLOR | TEXTURE_COORDS);

	// Create VBO
	CreateVertexBuffer(TOTAL_CUBE_VERTS, &vbo);

	// Bind vbo
	BindBuffer(vbo);

	// load into vbo
	LoadIntoVertexBuffer((char*) SOME_BUFFER, TOTAL_CUBE_VERTS);

	// Unbind vbo
	UnbindBuffer();

	// Set projection matrix
	SetProjectionMaxtrix(CreateProjection_mat4f(3.1415f / 2.0f, 1.0f, 0.5f, 6.0f));

	// Set model matrix
	SetModelMatrix(CreateTranslationMatrix_mat4f(0, 0, 4.0f));

	return 0;
}

int draw() {
	// Flush depth buffer
	FlushDepthBuffer();

	// Set buffer mask
	SetVBOMask(VERTEX_COORDS | COLOR | TEXTURE_COORDS);

	// Bind buffer
	BindBuffer(vbo);

	// Bind texture
	BindTexture(txtr);

	// Draw call
	Draw(TOTAL_CUBE_VERTS);

	// Unbin texture
	UnbindTexture();

	// Unbind buffer
	UnbindBuffer(vbo);

	return 0;
}

int destroy() {
	DestroyVertexBuffer(vbo);
	DestroyContext();
	return 0;
}
```
### Simple shader example
```
VERTEX_SHADER(TEST, {
		// Attributes
		//------------------
		// IN
		V_IN_ATTRIBUTE_F(3, POS, 0);
		V_IN_ATTRIBUTE_F(4, COL, 3);
		V_IN_ATTRIBUTE_F(2, TXTR_POS, 7);

		// OUT
		V_OUT_ATTRIBUTE_F(4, OUT_COL, 0);
		V_OUT_ATTRIBUTE_F(2, OUT_TXTR_POS, 4);
		//------------------

		// Code
		VEC(4) ps = VEC4(POS, 1);

		OUT_ATTRIBUTE(CVV_POS) = MUL_MV(4, PROJ_MAT, MUL_MV(4, MODEL_MAT, ps));
		OUT_ATTRIBUTE(OUT_COL) = COL;
		OUT_ATTRIBUTE(OUT_TXTR_POS) = TXTR_POS;

});

FRAGMENT_SHADER(TEST, {
		// Attributes
		//------------------
		// IN
		F_IN_ATTRIBUTE_F(4, COL, 0);
		F_IN_ATTRIBUTE_F(2, TXTR_POS, 4);
		//------------------

		// Code
		OUT_ATTRIBUTE(FRAG_COLOR) = ADD_VV(4, SAMPLER_2D(TEXTURE, TXTR_POS), COL);
});
```

## Theoremminum

### CMake
Good video [here](https://www.youtube.com/watch?v=gSTLzOmFChs)
But [here](https://stackoverflow.com/questions/59095842/cmake-mingw-compilation-on-windows-without-needing-the-g-mingw-makefiles-f) it is written about how to use with MinGW

### Perspective projection matrix
Good article [here](https://habr.com/ru/post/252771/)

### GDI
Examples of use [here](https://zetcode.com/gui/winapi/gdi/)

### Checking whether a point belongs to a triangle
Good article [here](https://cpp.mazurok.com/triangle/)

### General concept
Excellent article [here](https://habr.com/ru/post/257107/)

## Work organization
The logic is as follows: the code is divided into two parts - the rasterizer itself and the system window for testing.
The code is written in such a way that the rasterizer can be easily implemented on any system, it is enough to specify the function for drawing the pixel and call the necessary drawing functions.
### Chart
![](https://github.com/timattt/Computer-science-knowledge/blob/master/CpuRasterizer/about/Concept.png)
