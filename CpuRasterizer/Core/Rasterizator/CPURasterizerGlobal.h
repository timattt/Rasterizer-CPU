#pragma once

// Constants
//=================================================
#define WIDTH 800
#define HEIGHT 800
#define MAX_GRAPHICAL_MEMORY_SIZE 100000
#define BYTES_PER_PIXEL 4
//=================================================

// Includes
//=================================================
#include "Math.h"
//=================================================

// Defines
//=================================================
#define VERTEX_COORDS 1
#define COLOR 2
#define TEXTURE_COORDS 4
//=================================================


// Functional defines
//=================================================
#define MAX2(A, B) ((A) > (B) ? (A) : (B))
#define MIN2(A, B) ((A) > (B) ? (B) : (A))
#define MAX3(A, B, C) MAX2(A, MAX2(B, C))
#define MIN3(A, B, C) MIN2(A, MIN2(B, C))
//=================================================


// Typedefs
//=================================================
// VBO
typedef char * vbo_t;

// Texture
typedef struct Texture * txtr_p;
//=================================================

// Functions
//=================================================
// graphical context
int Draw(int total_prims);
int InitContext();
int DestroyContext();
int FlushDepthBuffer();
int SetVBOMask(int mask);

// system setters
int SetFrameBufferCallFunction(int (*frameBufferSetPixel)(int, int, int, int, int));
int SetTextureLoader(int (*textureLoader)(char*, struct Texture **));

// Vertex buffer
int CalcVertexSizeByMask();
int CreateVertexBuffer(int total_verts, vbo_t * result);
int DestroyVertexBuffer(vbo_t buf);
int LoadIntoVertexBuffer(char * raw_buf, int cap);
int BindBuffer(vbo_t buf);
int UnbindBuffer();

// Texture
int LoadTexture(char * path, txtr_p * dest);
int CreateTexture(int width, int height, char * pixs, txtr_p * dest);
int BindTexture(txtr_p txt);
int UnbindTexture();

// Projection matrix
int SetProjectionMaxtrix(mat4f_t proj);
int SetModelMatrix(mat4f_t model);

// Errors
int PrintErrorMessage();
int GetErrorMessage(char * dest);
//=================================================
