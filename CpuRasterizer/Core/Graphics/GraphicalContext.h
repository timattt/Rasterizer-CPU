#pragma once

// Constants
//=================================================
#define WIDTH 800
#define HEIGHT 800
//=================================================

// Std includes
//=================================================
#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
//=================================================


// Typedefs
//=================================================
typedef struct VertexBuffer vbo_t;
typedef struct VertexBuffer * vbo_p;
typedef struct GraphicalContext grcntx_t;
typedef struct GraphicalContext * grcntx_p;
typedef struct Mat4f mat4f_t;
typedef struct Vec4f vec4f_t;
typedef struct Vec3f vec3f_t;
typedef struct Mat4f * mat4f_p;
typedef struct Vec4f * vec4f_p;
typedef struct Vec3f * vec3f_p;
typedef struct Vertex vert;
//=================================================


// Defines
//=================================================
#define VERTEX_COORDS 1
#define COLOR 2
//=================================================


// Structures
//=================================================
// Vertex buffer
struct VertexBuffer {
	char * buffer;
	char mask;
	int capacity;// vertex number
};

// Math
struct Mat4f {
	float mat[4][4];
};
struct Vec4f {
	float x;
	float y;
	float z;
	float w;
};
struct Vec3f {
	float x;
	float y;
	float z;
};

// Vertex
struct Vertex {
	vec3f_t pos;
	vec4f_t color;
};

// Context
struct GraphicalContext {
	mat4f_t modelMatrix;
	mat4f_t projectionMatrix;
	vbo_p vbo;
};
//=================================================


// Functions
//=================================================
// window
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int SetFbPixel(int x, int y, int r, int g, int b);

// Test
int init();
int loop();
int destroy();

// vertex shader
int VertexShader(grcntx_t cnt);

// fragment shader
int FragmentShader(vert * primitive);

// math
int print_mat4f(mat4f_t mat);
mat4f_t mul_mat_mat4f(mat4f_t a, mat4f_t b);
vec4f_t mul_mat_vec4f(mat4f_t mat, vec4f_t vec);
vec3f_t fromHomogeneousCoordinates(vec4f_t vec);
vec4f_t toHomogeneousCoordinates(vec3f_t vec);
mat4f_t createXrotation(float angle);
mat4f_t createProjection(float fow, float aspect, float n, float f);
mat4f_t createTranslationMatrix(float dx, float dy, float dz);
vec3f_t cross(vec3f_t a, vec3f_t b);
vec3f_t add(vec3f_t a, vec3f_t b);
vec3f_t sub(vec3f_t a, vec3f_t b);
vec3f_t neg(vec3f_t a);
float dot(vec3f_t a, vec3f_t b);
float vecabs(vec3f_t a);
float calcSquare(vec3f_t a, vec3f_t b, vec3f_t c);

// framebuffer
int CalcVertexSizeByMask(int mask);
vbo_p CreateVertexBuffer(int verts_number, int mask);
int DestroyVertexBuffer(vbo_p buf);
int LoadIntoVertexBuffer(vbo_p buf, char * raw_buf);
int BindBuffer(vbo_p buf);
int UnbindBuffer(vbo_p buf);

// projection maxtrix
int SetProjectionMaxtrix(mat4f_t proj);
int SetModelMatrix(mat4f_t model);

// graphical context
int Draw();
//=================================================

