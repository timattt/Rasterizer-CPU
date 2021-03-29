#include "../GUITest/TestWindow.h"

// To draw
vbo_p vbo = NULL;
mat4f_t model = {0};
mat4f_t small_rot = {0};
txtr_p txtr = {0};

struct tmpVert {
	vec3f_t pos;
	vec4f_t color;
	vec2f_t tpos;
};

void loadCube(struct tmpVert * verts) {
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

	// Set texture loader
	SetTextureLoader(loadTexture);

	// Texture
	LoadTexture((char*)(L"Texture.bmp"), &txtr);

	// Create VBO
	CreateVertexBuffer(36, VERTEX_COORDS | COLOR | TEXTURE_COORDS, &vbo);

	// Bind vbo
	BindBuffer(vbo);

	// load into vbo
	LoadIntoVertexBuffer((char*) verts);

	// Unbind vbo
	UnbindBuffer();

	// Set projection matrix
	SetProjectionMaxtrix(CreateProjection_mat4f(3.1415f / 2.0f, 1.0f, 0.5f, 6.0f));

	// Set model matrix
	SetModelMatrix(model = CreateTranslationMatrix_mat4f(0, 0, 4.0f));

	small_rot = Mul_mat4f_mat4f(CreateXrotation_mat4f(0.07f), CreateYrotation_mat4f(0.09f));

	return 0;
}

int draw() {
	SetModelMatrix(model =
			Mul_mat4f_mat4f(model, small_rot));

	// Bind buffer
	BindBuffer(vbo);

	// Bind texture
	BindTexture(txtr);

	// Draw call
	Draw();

	// Unbin texture
	UnbindTexture();

	// Unbind buffer
	UnbindBuffer(vbo);

	return 0;
}

int destroy() {
	DestroyVertexBuffer(vbo);
	return 0;
}
