#include "../GUITest/TestWindow.h"

// To draw
vbo_p vbo = NULL;

struct tmpVert {
	vec3f_t pos;
	vec4f_t color;
};

void loadCube(struct tmpVert * verts) {
	vec3f_t p1 = { 1.0f, 1.0f, 1.0f };
	vec3f_t p2 = { 1.0f, 1.0f, -1.0f };
	vec3f_t p3 = { 1.0f, -1.0f, 1.0f };
	vec3f_t p4 = { 1.0f, -1.0f, -1.0f };
	vec3f_t p5 = { -1.0f, 1.0f, 1.0f };
	vec3f_t p6 = { -1.0f, 1.0f, -1.0f };
	vec3f_t p7 = { -1.0f, -1.0f, 1.0f };
	vec3f_t p8 = { -1.0f, -1.0f, -1.0f };

	vec4f_t c1 = { 1.0f, 0.0f, 0.0f, 1.0f }; //red
	vec4f_t c2 = { 0.0f, 1.0f, 0.0f, 1.0f }; //green
	vec4f_t c3 = { 0.0f, 0.0f, 1.0f, 1.0f }; //blue
	vec4f_t c4 = { 0.5f, 0.0f, 0.0f, 1.0f }; //black

	vec4f_t c5 = { 1.0f, 0.0f, 1.0f, 1.0f };
	vec4f_t c6 = { 1.0f, 1.0f, 0.0f, 1.0f };
	vec4f_t c7 = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4f_t c8 = { 0.0f, 1.0f, 1.0f, 1.0f };

	// CUBE VERTICES
	//======================================

	int i = 0;

	verts[i++].pos = p1;
	verts[i++].pos = p2;
	verts[i++].pos = p3;

	verts[i++].pos = p2;
	verts[i++].pos = p3;
	verts[i++].pos = p4;

	verts[i++].pos = p5;
	verts[i++].pos = p6;
	verts[i++].pos = p7;

	verts[i++].pos = p6;
	verts[i++].pos = p7;
	verts[i++].pos = p8;

	verts[i++].pos = p1;
	verts[i++].pos = p2;
	verts[i++].pos = p6;

	verts[i++].pos = p1;
	verts[i++].pos = p5;
	verts[i++].pos = p6;

	verts[i++].pos = p3;
	verts[i++].pos = p4;
	verts[i++].pos = p8;

	verts[i++].pos = p3;
	verts[i++].pos = p7;
	verts[i++].pos = p8;

	verts[i++].pos = p1;
	verts[i++].pos = p3;
	verts[i++].pos = p7;

	verts[i++].pos = p1;
	verts[i++].pos = p5;
	verts[i++].pos = p7;

	verts[i++].pos = p2;
	verts[i++].pos = p4;
	verts[i++].pos = p8;

	verts[i++].pos = p2;
	verts[i++].pos = p6;
	verts[i++].pos = p8;

	i = 0;

	verts[i++].color = c1;
	verts[i++].color = c2;
	verts[i++].color = c3;

	verts[i++].color = c2;
	verts[i++].color = c3;
	verts[i++].color = c4;

	verts[i++].color = c5;
	verts[i++].color = c6;
	verts[i++].color = c7;

	verts[i++].color = c6;
	verts[i++].color = c7;
	verts[i++].color = c8;

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

int init() {

	// Cube vertices
	struct tmpVert verts[6 * 2 * 3]; // 6 faces, 2 triangles per face, 3 vertices per triangle
	loadCube(verts);

	// Set pixel draw function
	SetFrameBufferCallFunction(SetFbPixel);

	// Create VBO
	CreateVertexBuffer(36, VERTEX_COORDS | COLOR, &vbo);

	// Bind vbo
	BindBuffer(vbo);

	// load into vbo
	LoadIntoVertexBuffer((char*) verts);

	// Unbind vbo
	UnbindBuffer();

	// Set projection matrix
	SetProjectionMaxtrix(CreateProjection_mat4f(3.1415f / 2.0f, 1.0f, 0.5f, 6.0f));

	// Set model matrix
	SetModelMatrix(Mul_mat4f_mat4f(CreateTranslationMatrix_mat4f(0, 0, 4.0f), Mul_mat4f_mat4f(CreateXrotation_mat4f(0.5f), CreateYrotation_mat4f(1.0f))));

	return 0;
}

int draw() {
	// Bind buffer
	BindBuffer(vbo);

	// Draw call
	Draw();

	// Unbind buffer
	UnbindBuffer(vbo);
	return 0;
}

int destroy() {
	DestroyVertexBuffer(vbo);
	return 0;
}
