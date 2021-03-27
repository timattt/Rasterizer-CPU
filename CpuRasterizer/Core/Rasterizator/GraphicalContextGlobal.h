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
//=================================================


// Typedefs
//=================================================
typedef struct VertexBuffer * vbo_p;
typedef struct Mat4f mat4f_t;
typedef struct Vec4f vec4f_t;
typedef struct Vec3f vec3f_t;
typedef struct Mat4f * mat4f_p;
typedef struct Vec4f * vec4f_p;
typedef struct Vec3f * vec3f_p;
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
//=================================================

// Functions
//=================================================
// graphical context
int Draw();
int SetFrameBufferCallFunction(int (*frameBufferSetPixel)(int, int, int, int, int));

// Vertex buffer
int CalcVertexSizeByMask(int mask);
int CreateVertexBuffer(int verts_number, int mask, vbo_p * result);
int DestroyVertexBuffer(vbo_p buf);
int LoadIntoVertexBuffer(char * raw_buf);
int BindBuffer(vbo_p buf);
int UnbindBuffer(vbo_p buf);

// Math
int Print_mat4f(mat4f_t mat);
mat4f_t Mul_mat4f_mat4f(mat4f_t a, mat4f_t b);
vec4f_t Mul_mat4f_vec4f(mat4f_t mat, vec4f_t vec);
vec3f_t FromHomogeneousCoordinates_vec4f(vec4f_t vec);
vec4f_t ToHomogeneousCoordinates_vec3f(vec3f_t vec);
mat4f_t CreateXrotation_mat4f(float angle);
mat4f_t CreateYrotation_mat4f(float angle);
mat4f_t CreateProjection_mat4f(float fow, float aspect, float n, float f);
mat4f_t CreateTranslationMatrix_mat4f(float dx, float dy, float dz);
vec3f_t Cross_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Add_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Sub_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Neg_vec3f(vec3f_t a);
float Dot_vec3f(vec3f_t a, vec3f_t b);
float Abs_vec3f(vec3f_t a);
float Square_vec3f(vec3f_t a, vec3f_t b, vec3f_t c);
float SquarePlane_vec3f(vec3f_t a, vec3f_t b, vec3f_t c);

// projection maxtrix
int SetProjectionMaxtrix(mat4f_t proj);
int SetModelMatrix(mat4f_t model);
//=================================================
