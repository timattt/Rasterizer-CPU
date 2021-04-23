#pragma once

#define DEBUG

// Errors handle
//=================================================
extern int errcode;
#define ERROR_MESSAGE_LEN 10000
extern char errorMessage[ERROR_MESSAGE_LEN];
#define NULL_ERR_CODE 1
#define BAD_ARGS_ERR_CODE 2
#ifdef DEBUG
	#define NOT_NULL(A) do {if ((A) == NULL) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "NULL! In file %s on line %d\n", __FILE__, __LINE__); PrintErrorMessage(); exit(0); errcode = NULL_ERR_CODE;return -1;}} while (0)
	#define ENSURE_M(A, MES) do {if (!(A)) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "%s In file %s on line %d\n", MES, __FILE__, __LINE__); PrintErrorMessage(); exit(0); errcode = BAD_ARGS_ERR_CODE; return -1;}} while (0)
	#define ENSURE(A) ENSURE_M(A, "Not ensured!")
#else
	#define NOT_NULL(A) do {if ((A) == NULL) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "NULL! In file %s on line %d\n", __FILE__, __LINE__); errcode = NULL_ERR_CODE;return -1;}} while (0)
	#define ENSURE_M(A, MES) do {if (!(A)) {memset(errorMessage, 0, ERROR_MESSAGE_LEN); sprintf(errorMessage, "%s In file %s on line %d\n", MES, __FILE__, __LINE__); errcode = BAD_ARGS_ERR_CODE; return -1;}} while (0)
	#define ENSURE(A) ENSURE_M(A, "Not ensured!")
#endif
//=================================================


// Includes
//=================================================
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags
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
extern struct GraphicalContext {
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

	// Shader program
	int (*vertexShader)(float * in, float * out);
	int (*fragmentShader)(float * in, float out[4]);
} currentContext;
//=================================================


// Functions
//=================================================
// vertex shader
int VertexStage(grcntx_p cnt, int total_prim);

// Fragment shader
int FragmentStage(grcntx_p cnt, float * in);

// Depth buffer
int SetDepth(int x, int y, float val);
float GetDepth(int x, int y);

// Graphical memory
int AllocateGraphicalMemory(int sz, char ** dest);
int FreeGraphicalMemory(char * ptr);
//=================================================

