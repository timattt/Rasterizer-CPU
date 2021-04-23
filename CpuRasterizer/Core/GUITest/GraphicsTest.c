#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#include "../Rasterizator/CPURasterizerGlobal.h"
#include "../Rasterizator/Math.h"
#include "TestWindow.h"

// SIMPLE CUBE LOADING
//=============================================

struct tmpVert {
	vec3f_t pos;
	vec4f_t color;
	vec2f_t tpos;
};

void loadCube(struct tmpVert * verts) {
	vec4f_t c0 = { 0 };

	vec3f_t p1 = { 1.0f, 1.0f, 1.0f };
	vec3f_t p2 = { 1.0f, -1.0f, 1.0f };
	vec3f_t p3 = { -1.0f, 1.0f, 1.0f };
	vec3f_t p4 = { -1.0f, -1.0f, 1.0f };
	vec3f_t p5 = { 1.0f, 1.0f, -1.0f };
	vec3f_t p6 = { 1.0f, -1.0f, -1.0f };
	vec3f_t p7 = { -1.0f, 1.0f, -1.0f };
	vec3f_t p8 = { -1.0f, -1.0f, -1.0f };

	vec4f_t c1 = { 1.0f, 0.0f, 0.0f, 1.0f }; //red
	vec4f_t c2 = { 0.0f, 1.0f, 0.0f, 1.0f }; //green
	vec4f_t c3 = { 0.0f, 0.0f, 1.0f, 1.0f }; //blue
	vec4f_t c4 = { 0.5f, 0.0f, 0.0f, 1.0f }; //black
	vec4f_t c5 = { 1.0f, 0.0f, 1.0f, 1.0f };
	vec4f_t c6 = { 1.0f, 1.0f, 0.0f, 1.0f };
	vec4f_t c7 = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4f_t c8 = { 0.0f, 1.0f, 1.0f, 1.0f };

	vec2f_t t_1 = {-1, -1};

	vec2f_t t1 = { 0.0f, 0.0f };
	vec2f_t t2 = { 1.0f, 0.0f };
	vec2f_t t3 = { 0.0f, 1.0f };
	vec2f_t t4 = { 1.0f, 1.0f };

	// CUBE VERTICES
	//======================================

	int i = 0;

	//1
	verts[i++].tpos = t1;
	verts[i++].tpos = t2;
	verts[i++].tpos = t3;

	verts[i++].tpos = t2;
	verts[i++].tpos = t3;
	verts[i++].tpos = t4;
	//2
	verts[i++].tpos = t1;
	verts[i++].tpos = t2;
	verts[i++].tpos = t3;

	verts[i++].tpos = t2;
	verts[i++].tpos = t3;
	verts[i++].tpos = t4;

	for(i = 12; i < 36; i++) verts[i].tpos = t_1;

	i = 0;
	//1
	verts[i++].pos = p1;
	verts[i++].pos = p2;
	verts[i++].pos = p3;

	verts[i++].pos = p2;
	verts[i++].pos = p3;
	verts[i++].pos = p4;
	//2
	verts[i++].pos = p5;
	verts[i++].pos = p6;
	verts[i++].pos = p7;

	verts[i++].pos = p6;
	verts[i++].pos = p7;
	verts[i++].pos = p8;
	//3
	verts[i++].pos = p1;
	verts[i++].pos = p2;
	verts[i++].pos = p6;

	verts[i++].pos = p1;
	verts[i++].pos = p5;
	verts[i++].pos = p6;
	//4
	verts[i++].pos = p3;
	verts[i++].pos = p4;
	verts[i++].pos = p8;

	verts[i++].pos = p3;
	verts[i++].pos = p7;
	verts[i++].pos = p8;
	//5
	verts[i++].pos = p1;
	verts[i++].pos = p3;
	verts[i++].pos = p7;

	verts[i++].pos = p1;
	verts[i++].pos = p5;
	verts[i++].pos = p7;
	//6
	verts[i++].pos = p2;
	verts[i++].pos = p4;
	verts[i++].pos = p8;

	verts[i++].pos = p2;
	verts[i++].pos = p6;
	verts[i++].pos = p8;

	i = 0;

	verts[i++].color = c0;
	verts[i++].color = c0;
	verts[i++].color = c0;

	verts[i++].color = c0;
	verts[i++].color = c0;
	verts[i++].color = c0;

	verts[i++].color = c0;
	verts[i++].color = c0;
	verts[i++].color = c0;

	verts[i++].color = c0;
	verts[i++].color = c0;
	verts[i++].color = c0;

	verts[i++].color = c1;
	verts[i++].color = c2;
	verts[i++].color = c6;

	verts[i++].color = c1;
	verts[i++].color = c5;
	verts[i++].color = c6;

	verts[i++].color = c3;
	verts[i++].color = c4;
	verts[i++].color = c8;

	verts[i++].color = c3;
	verts[i++].color = c7;
	verts[i++].color = c8;

	verts[i++].color = c1;
	verts[i++].color = c3;
	verts[i++].color = c7;

	verts[i++].color = c1;
	verts[i++].color = c5;
	verts[i++].color = c7;

	verts[i++].color = c2;
	verts[i++].color = c4;
	verts[i++].color = c8;

	verts[i++].color = c2;
	verts[i++].color = c6;
	verts[i++].color = c8;

	//======================================
}
//=============================================


//=============================================
// SHADER PROGRAM
// NAME: TEST
//=============================================
#include "../Rasterizator/SL.h"
//=============================================
// GLOBAL UNIFORMS
// Ambient light
const float ambientStrength = 0.1;
const float specularStrength = 0.8;
const float alpha = 320.0f;
const vec3f_t lightColor = {.x = 0.7f, .y = 0.4f, .z = 0.8f};
const vec3f_t ambientLightDirection = {.x = 1.0f, .y = 1.0f, .z = 1.0f};
//=============================================
VERTEX_SHADER(TEST, {
		// Attributes
		//------------------
		// IN
		V_IN_ATTRIBUTE_F(3, POS, 0);
		V_IN_ATTRIBUTE_F(3, NORM, 3);
		// OUT
		V_OUT_ATTRIBUTE_F(3, M_NORM, 0);
		V_OUT_ATTRIBUTE_F(3, M_POS, 3);
		//------------------

		// Code
		VEC(4) ps = VEC4(POS, 1);
		VEC(4) nm = VEC4(NORM, 1);
		OUT_ATTRIBUTE(M_NORM) = FROM_HOM(MUL_MV(4, MODEL_MAT, nm));
		OUT_ATTRIBUTE(M_POS) = FROM_HOM(MUL_MV(4, MODEL_MAT, ps));
		OUT_ATTRIBUTE(CVV_POS) = MUL_MV(4, PROJ_MAT, MUL_MV(4, MODEL_MAT, ps));
});
//=============================================
FRAGMENT_SHADER(TEST, {
		// Attributes
		//------------------
		// IN
		F_IN_ATTRIBUTE_F(3, M_NORM, 0);
		F_IN_ATTRIBUTE_F(3, M_POS, 3);
		//------------------

		VEC(4) staticCol = {0};
		staticCol.x = 0.5f;
		staticCol.y = 0;
		staticCol.z = 0.5f;
		staticCol.w = 1;

		//
		VEC(3) N = NORM(3, M_NORM);
		VEC(3) L = ambientLightDirection;
		VEC(3) V = NEG(3, M_POS);
		VEC(3) R = SUB(3, MUL_FV(3, N, DOT(3, N, L) * 2), L);

		// Background light
		VEC(3) ambient = MUL_VF(3,lightColor, ambientStrength);

		// Diffuse light
		float diff_factor = MAX(0.0f, DOT(3, N, L));
		VEC(3) diffuse = MUL_VF(3, lightColor, diff_factor);

		// Specular light
		float spec_factor = pow(MAX(DOT(3, V, R), 0.0),alpha);
		VEC(3) specular = MUL_FV(3, lightColor, spec_factor * specularStrength);

		OUT_ATTRIBUTE(FRAG_COLOR) = MUL_VV(4, staticCol, ADD_VV(4, ADD_VV(4, VEC4(ambient, 1), VEC4(specular, 1)), VEC4(diffuse, 1)));
});
//=============================================

// To draw
vbo_t vbo_teapot = NULL;
vbo_t vbo_cube = NULL;
mat4f_t model_teapot = {0};
mat4f_t model_cube = {0};
mat4f_t small_rot = {0};
txtr_p txtr_cube = {0};

int totalTeapotVerts = 0;
int totalCubeVerts = 0;

#define TOTAL_CUBE_VERTS 36

int init() {
	// CONTEXT INIT
	//---------------------------------

	// Init context
	InitContext();

	// Set pixel draw function
	SetFrameBufferCallFunction(SetFbPixel);

	// Set texture loader
	SetTextureLoader(loadTexture);

	// Set projection matrix
	SetProjectionMatrix(CreateProjection_mat4f(3.1415f / 2.0f, 1.0f, 0.5f, 15.0f));//cast here is to calm down my beloved mingw compiler
	//---------------------------------


	// CUBE
	//---------------------------------
	struct tmpVert raw_cube[TOTAL_CUBE_VERTS] = {0}; // 6 faces, 2 triangles per face, 3 vertices per triangle
	loadCube(raw_cube);
	totalCubeVerts = TOTAL_CUBE_VERTS;

	// Set cube vbo recognition mask
	SetVBOMask(VERTEX_COORDS | COLOR | TEXTURE_COORDS);

	// Vbo
	CreateVertexBuffer(totalCubeVerts, &vbo_cube);

	// Texture
	LoadTexture((char*)(L"Resources/Texture.bmp"), &txtr_cube);

	// Bind
	BindBuffer(vbo_cube);

	// load into buffer
	LoadIntoVertexBuffer((char*) raw_cube, totalCubeVerts);

	// Unbind cube buffer
	UnbindBuffer();

	// Create model matrix
	model_cube = CreateTranslationMatrix_mat4f(4.0f, 4.0f, 8.0f);
	//---------------------------------


	// TEAPOT
	//---------------------------------
	// Set vbo_teapot recognition mask
	SetVBOMask(VERTEX_COORDS | NORMAL);

	int teapotMask = 0;
	float * raw_teapot = LoadModel("Resources/teapot.obj", &totalTeapotVerts, &teapotMask);
	if (EnsureVBOComponent(teapotMask) == -1) {
		printf("Bad teapot model!\n");
		exit(0);
	}

	// Create VBO
	CreateVertexBuffer(totalTeapotVerts, &vbo_teapot);

	// Bind vbo_teapot
	BindBuffer(vbo_teapot);

	// load into vbo_teapot
	LoadIntoVertexBuffer((char*) raw_teapot, totalTeapotVerts);

	// Unbind vbo_teapot
	UnbindBuffer();

	// After copying into graphical memory raw buffer can be freed
	free(raw_teapot);

	// Model matrix
	model_teapot = Mul_mat4f_mat4f(CreateTranslationMatrix_mat4f(-0.0f, 0, 6.0f), CreateZrotation_mat4f(3.1415f));
	//---------------------------------


	// UTILS
	//---------------------------------
	small_rot = Mul_mat4f_mat4f(CreateXrotation_mat4f(0.04f), CreateYrotation_mat4f(0.03f));
	//---------------------------------

	return 0;
}

int draw() {
	// Flush depth buffer
	FlushDepthBuffer();

	// TEAPOT
	//---------------------------------
	// Bind shaders
	USE_SHADER_PROGRAM(TEST);

	// Move teapot
	SetModelMatrix(model_teapot = Mul_mat4f_mat4f(model_teapot, small_rot));

	// Set buffer mask
	SetVBOMask(VERTEX_COORDS | NORMAL);

	// Bind buffer
	BindBuffer(vbo_teapot);

	// Draw call
	Draw(totalTeapotVerts);

	// Unbind buffer
	UnbindBuffer();

	// Unbind shader
	RESET_SHADER_PROGRAM;
	//---------------------------------

	// Flush depth buffer
	FlushDepthBuffer();

	// CUBE
	//---------------------------------
	// Move cube
	SetModelMatrix(model_cube = Mul_mat4f_mat4f(model_cube, small_rot));

	// Bind buffer
	BindBuffer(vbo_cube);

	// Bind texture
	BindTexture(txtr_cube);

	// Set buffer mask
	SetVBOMask(VERTEX_COORDS | COLOR | TEXTURE_COORDS);

	Draw(totalCubeVerts);

	// Unbind texture
	UnbindTexture();

	// Unbind buffer
	UnbindBuffer();

	//---------------------------------

	return 0;
}

int destroy() {
	DestroyVertexBuffer(vbo_teapot);
	DestroyVertexBuffer(vbo_cube);
	DestroyTexture(txtr_cube);
	DestroyContext();
	return 0;
}
