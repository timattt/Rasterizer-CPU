#pragma once

// Variables
#define VEC(N) vec ## N ## f_t
#define VEC4(V, W) { .x = V.x, .y = V.y, .z = V.z, .w = W }

// Functions
#define MUL_MV(N, MAT, VEC) Mul_mat ## N ## f_vec ## N ## f(MAT, VEC)
#define MUL_MM(N, MAT1, MAT2) Mul_mat ## N ## f_mat ## N ## f(MAT1, MAT2)
#define ADD_VV(N, V1, V2) Add_vec ## N ## f(V1, V2)
#define SAMPLER_2D(TXTR, V) GetPixel_vec2f(TXTR, V)

// Uniforms
#define MODEL_MAT GetModelMatrix()
#define PROJ_MAT GetProjectionMatrix()
#define TEXTURE GetBindedTexture()

// Attributes
#define V_IN_ATTRIBUTE_F(N, NAME, SHIFT) VEC(N) * NAME ## _inp = (VEC(N) *)(in + SHIFT); VEC(N) NAME = *(NAME ## _inp); NAME = NAME;
#define V_OUT_ATTRIBUTE_F(N, NAME, SHIFT) VEC(N) * NAME ## _op = (VEC(N)*)(out + SHIFT + 4); NAME ## _op = NAME ## _op;

#define F_IN_ATTRIBUTE_F(N, NAME, SHIFT) VEC(N) * NAME ## _inp = (VEC(N) *)(in + SHIFT); VEC(N) NAME = *(NAME ## _inp); NAME = NAME;
#define F_OUT_ATTRIBUTE_F(N, NAME, SHIFT) VEC(N) * NAME ## _op = (VEC(N)*)(out + SHIFT); NAME ## _op = NAME ## _op;

#define OUT_ATTRIBUTE(NAME) (*(NAME ## _op))

#define VERTEX_SHADER(PROG_NAME, CODE)\
	int vshader ## PROG_NAME (float * in, float * out) {\
		V_OUT_ATTRIBUTE_F(4, CVV_POS, -4)\
		CODE\
		return 0;\
	}\

#define FRAGMENT_SHADER(PROG_NAME, CODE)\
	int fshader ## PROG_NAME (float * in, float * out) {\
		F_IN_ATTRIBUTE_F(4, CVV_POS, -4)\
		F_OUT_ATTRIBUTE_F(4, FRAG_COLOR, 0)\
		CODE\
		return 0;\
	}\

#define SHADER_PROGRAM(NAME, V_CODE, F_CODE) \
	int vshader ## NAME (float * in, float * out) {\
		V_CODE\
		return 0;\
	}\
	int fshader ## NAME (float * in, float out[4]) {\
		F_CODE\
		return 0;\
	}

#define USE_SHADER_PROGRAM(NAME) SetShaderProgram(vshader##NAME, fshader##NAME)
