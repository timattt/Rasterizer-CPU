#pragma once

// Errors handle
//=================================================
int errcode;
#define NULL_ERR_CODE 1
#define BAD_ARGS_ERR_CODE 2
#define NOT_NULL(A) do {if (A == NULL) {errcode = NULL_ERR_CODE;return -1;}} while (0)
#define ENSURE(A) do {if (!(A)) {errcode = BAD_ARGS_ERR_CODE;return -1;}} while (0)
//=================================================


// Includes
//=================================================
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "../Rasterizator/GraphicalContextGlobal.h"
//=================================================


// Typedefs
//=================================================
typedef struct GraphicalContext grcntx_t;
typedef struct GraphicalContext * grcntx_p;
typedef struct Vertex vert;
typedef struct VertexBuffer vbo_t;
//=================================================


// Structures
//=================================================
// Vertex
struct Vertex {
	vec3f_t pos;
	vec4f_t color;
};
// Vertex buffer
struct VertexBuffer {
	char * buffer;
	char mask;
	int capacity;// vertex number
};
// Context
struct GraphicalContext {
	mat4f_t modelMatrix;
	mat4f_t projectionMatrix;
	vbo_p vbo;
	int (*frameBufferSetPixel)(int, int, int, int, int);
} currentContext;
//=================================================


// Functions
//=================================================
// vertex shader
int VertexShader(grcntx_p cnt);

// fragment shader
int FragmentShader(grcntx_p cnt, vert * primitive);
int flushDepthBuffer();
//=================================================

