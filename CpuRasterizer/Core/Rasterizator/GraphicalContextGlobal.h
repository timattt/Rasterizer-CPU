#pragma once

// Constants
//=================================================
#define WIDTH 800
#define HEIGHT 800
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
typedef struct VertexBuffer * vbo_p;

// Matrix
typedef struct Mat4f mat4f_t;
typedef struct Mat4f * mat4f_p;

// Vectors
// 2
typedef struct Vec2f vec2f_t;

// 3
typedef struct Vec3f vec3f_t;
typedef struct Vec3f * vec3f_p;

// 4
typedef struct Vec4f vec4f_t;
typedef struct Vec4f * vec4f_p;

// Texture
typedef struct Texture * txtr_p;
//=================================================


// Structures
//=================================================
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
struct Vec2f {
	float x;
	float y;
};
//=================================================

// Functions
//=================================================
// graphical context
int Draw();
int SetFrameBufferCallFunction(int (*frameBufferSetPixel)(int, int, int, int, int));
int SetTextureLoader(int (*textureLoader)(char*, struct Texture **));

// Vertex buffer
int CalcVertexSizeByMask(int mask);
int CreateVertexBuffer(int verts_number, int mask, vbo_p * result);
int DestroyVertexBuffer(vbo_p buf);
int LoadIntoVertexBuffer(char * raw_buf);
int BindBuffer(vbo_p buf);
int UnbindBuffer();

// Math
// Matrix
int Print_mat4f(mat4f_t mat);
mat4f_t Mul_mat4f_mat4f(mat4f_t a, mat4f_t b);
vec4f_t Mul_mat4f_vec4f(mat4f_t mat, vec4f_t vec);

// Rotation
mat4f_t CreateXrotation_mat4f(float angle);
mat4f_t CreateYrotation_mat4f(float angle);

// Projection
mat4f_t CreateProjection_mat4f(float fow, float aspect, float n, float f);

// Model
mat4f_t CreateTranslationMatrix_mat4f(float dx, float dy, float dz);

// Homogeneous coords
vec3f_t FromHomogeneousCoordinates_vec4f(vec4f_t vec);
vec4f_t ToHomogeneousCoordinates_vec3f(vec3f_t vec);

// Vec4f
vec4f_t Add_vec4f(vec4f_t a, vec4f_t b);
vec4f_t Mul_vec4f(vec4f_t a, float f);

// Vec3f
vec3f_t Cross_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Add_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Sub_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Neg_vec3f(vec3f_t a);
float Dot_vec3f(vec3f_t a, vec3f_t b);
float Abs_vec3f(vec3f_t a);
float Square_vec3f(vec3f_t a, vec3f_t b, vec3f_t c);
vec3f_t Mul_vec3f(vec3f_t a, float f);

// Vec2f
vec2f_t Add_vec2f(vec2f_t a, vec2f_t b);
vec2f_t Mul_vec2f(vec2f_t a, float f);

// Texture
int LoadTexture(char * path, txtr_p * dest);
int CreateTexture(int width, int height, char * pixs, txtr_p * dest);
int BindTexture(txtr_p txt);
int UnbindTexture();

// Projection matrix
int SetProjectionMaxtrix(mat4f_t proj);
int SetModelMatrix(mat4f_t model);
//=================================================
