
// Variables
#define VEC(N) vec ## N ## f_t
#define VEC4(V, W) (vec4f_t){ .x = V.x, .y = V.y, .z = V.z, .w = W }

// Functions
#define MUL_MV(N, MAT, VEC) Mul_mat ## N ## f_vec ## N ## f(MAT, VEC)
#define MUL_MM(N, MAT1, MAT2) Mul_mat ## N ## f_mat ## N ## f(MAT1, MAT2)
#define MUL_VV(N, A, B) Mul_vec ## N ## f_vec ## N ## f(A, B)
#define MUL_FV(N, V, F) Mul_vec ## N  ## f_f(V, F)
#define ADD_VV(N, V1, V2) Add_vec ## N ## f_vec ## N ## f(V1, V2)
#define SAMPLER_2D(TXTR, V) GetPixel_vec2f(TXTR, V)
#define FROM_HOM(V) (vec3f_t){.x = V.x / V.w, .y = V.y / V.w, .z = V.z / V.w,}
#define DOT(N, V1, V2) Dot_vec ## N ## f_vec ## N ## f(V1, V2)
#define SUB(N, V1, V2) Sub_vec ## N ## f_vec ## N ## f(V1, V2)
#define NORM(N, V) Normalize_vec ## N ## f(V)
#define NEG(N, V) Neg_vec ## N ## f(V)
#define MUL_VF(N, V, F) Mul_vec ## N ## f_f(V, F)
#define CLAMP(A, B, C) (A > B ? A : (B > C ? C : B))
#define MAX(A, B) (A > B ? A : B)


// Uniforms
#define MODEL_MAT (mat4f_t)(GetModelMatrix())
#define PROJ_MAT (mat4f_t)(GetProjectionMatrix())
#define TEXTURE (txtr_p)(GetBindedTexture())

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

#define USE_SHADER_PROGRAM(NAME) SetShaderProgram(vshader##NAME, fshader##NAME)
#define RESET_SHADER_PROGRAM ResetShaderProgram()
