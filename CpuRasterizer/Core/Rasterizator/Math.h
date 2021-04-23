#pragma once

// Typedefs
//=================================================
// Matrix
typedef struct Mat4f mat4f_t;
typedef struct Mat4f * mat4f_p;

// Vectors
// 2
typedef struct Vec2f vec2f_t;
typedef struct Vec2f * vec2f_p;

// 3
typedef struct Vec3f vec3f_t;
typedef struct Vec3f * vec3f_p;

// 4
typedef struct Vec4f vec4f_t;
typedef struct Vec4f * vec4f_p;
//=================================================

// Structures
//=================================================
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

// Global functions
//=================================================
// Math
// Matrix
int Print_mat4f(mat4f_t mat);
mat4f_t Mul_mat4f_mat4f(mat4f_t a, mat4f_t b);
vec4f_t Mul_mat4f_vec4f(mat4f_t mat, vec4f_t vec);

// Rotation
mat4f_t CreateXrotation_mat4f(float angle);
mat4f_t CreateYrotation_mat4f(float angle);
mat4f_t CreateZrotation_mat4f(float angle);

// Projection
mat4f_t CreateProjection_mat4f(float fow, float aspect, float n, float f);

// Model
mat4f_t CreateTranslationMatrix_mat4f(float dx, float dy, float dz);

// Homogeneous coords
vec3f_t FromHomogeneousCoordinates_vec4f(vec4f_t vec);
vec4f_t ToHomogeneousCoordinates_vec3f(vec3f_t vec);

// Vec4f
vec4f_t Add_vec4f_vec4f(vec4f_t a, vec4f_t b);
vec4f_t Mul_vec4f_f(vec4f_t a, float f);
vec4f_t Mul_vec4f_vec4f(vec4f_t a, vec4f_t b);

// Vec3f
vec3f_t Cross_vec3f_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Add_vec3f_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Sub_vec3f_vec3f(vec3f_t a, vec3f_t b);
vec3f_t Neg_vec3f(vec3f_t a);
float Dot_vec3f_vec3f(vec3f_t a, vec3f_t b);
float Abs_vec3f(vec3f_t a);
float Square_vec3f_vec3f_vec3f(vec3f_t a, vec3f_t b, vec3f_t c);
vec3f_t Mul_vec3f_f(vec3f_t a, float f);
vec3f_t Normalize_vec3f(vec3f_t v);
vec3f_t Mul_vec3f_vec3f(vec3f_t a, vec3f_t b);

// Vec2f
vec2f_t Add_vec2f_vec2f(vec2f_t a, vec2f_t b);
vec2f_t Mul_vec2f_f(vec2f_t a, float f);
//=================================================
