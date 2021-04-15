#pragma once

// Errors handle
//=================================================
int errcode;
#define ERROR_MESSAGE_LEN 10000
char errorMessage[ERROR_MESSAGE_LEN];
#define NULL_ERR_CODE 1
#define BAD_ARGS_ERR_CODE 2
#ifdef DEBUG
	#define NOT_NULL(A) do {if ((A) == NULL) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "NULL! In file %s on line %d\n", __FILE__, __LINE__); PrintErrorMessage(); exit(0); errcode = NULL_ERR_CODE;return -1;}} while (0)
	#define ENSURE(A) do {if (!(A)) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "Not ensured! In file %s on line %d\n", __FILE__, __LINE__); PrintErrorMessage(); exit(0); errcode = BAD_ARGS_ERR_CODE;return -1;}} while (0)
#else
	#define NOT_NULL(A) do {if ((A) == NULL) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "NULL! In file %s on line %d\n", __FILE__, __LINE__); errcode = NULL_ERR_CODE;return -1;}} while (0)
	#define ENSURE(A) do {if (!(A)) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "Not ensured! In file %s on line %d\n", __FILE__, __LINE__);errcode = BAD_ARGS_ERR_CODE;return -1;}} while (0)
#endif
//=================================================


// Includes
//=================================================
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "CPURasterizerGlobal.h"
//=================================================


// Typedefs
//=================================================
typedef struct GraphicalContext grcntx_t;
typedef struct GraphicalContext * grcntx_p;
typedef struct Vertex vert_t;
typedef struct Texture txtr_t;
//=================================================


// Structures
//=================================================
// Vertex
struct Vertex {
	vec4f_t pos;
	vec4f_t color;
	vec2f_t txtr_pos;
};
// Texture
struct Texture {
	int width;
	int height;
	char * pixels;
};
// Context
struct GraphicalContext {
	// decoding
	char vbo_mask;

	// memory
	char * graphicalMemory;
	float * depthBuffer;

	char * emptyMem;

	// uniforms and vbos
	mat4f_t modelMatrix;
	mat4f_t projectionMatrix;
	vbo_t vbo;
	txtr_p texture;

	// system
	int (*frameBufferSetPixel)(int, int, int, int, int);
	int (*textureLoader)(char*, struct Texture **);
} currentContext;
//=================================================


// Functions
//=================================================
// vertex shader
int VertexStage(grcntx_p cnt, int total_prim);

// Fragment shader
int FragmentStage(grcntx_p cnt, vert_t * primitive);

// Depth buffer
int SetDepth(int x, int y, float val);
float GetDepth(int x, int y);

// Texture
int GetPixel(txtr_p txtr, vec2f_t pos, vec4f_t * dest);

// Graphical memory
int AllocateGraphicalMemory(int sz, char ** dest);
//=================================================

