#pragma once

// Constants
//=================================================
#define WIDTH 800
#define HEIGHT 800
#define MAX_GRAPHICAL_MEMORY_SIZE 10000000
#define BYTES_PER_PIXEL 4
#define STAGES_TRANSFER_BUFFER_SIZE 100
#define VERTICES_PER_PRIMITIVE 3
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
#define NORMAL 8
#define DEFAULT_ATTRIBUTES_QUANTITY 4
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
int AdditionalVertexDataMask(int quant);
int CalcVertexSizeByMask();
int CreateVertexBuffer(int total_verts, vbo_t * result);
int DestroyVertexBuffer(vbo_t buf);
int LoadIntoVertexBuffer(char * raw_buf, int cap);
int BindBuffer(vbo_t buf);
int UnbindBuffer();
int EnsureVBOComponent(int mask);

// Texture
int LoadTexture(char * path, txtr_p * dest);
int CreateTexture(int width, int height, char * pixs, txtr_p * dest);
int BindTexture(txtr_p txt);
int UnbindTexture();
txtr_p GetBindedTexture();
vec4f_t GetPixel_vec2f(txtr_p txtr, vec2f_t pos);
int DestroyTexture(txtr_p txt);

// Projection matrix
int SetProjectionMatrix(mat4f_t proj);
int SetModelMatrix(mat4f_t model);
mat4f_t GetProjectionMatrix();
mat4f_t GetModelMatrix();

// Errors
int PrintErrorMessage();
int GetErrorMessage(char * dest);

// Shader program
int SetShaderProgram(int (*vertexShader)(float * in, float * out), int (*fragmentShader)(float * in, float out[4]));
int ResetShaderProgram();

// Loader
float* LoadModel(char * fileName, int * total, int * mask);
//=================================================
