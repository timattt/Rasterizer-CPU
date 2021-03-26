#include "../Graphics/GraphicalContext.h"

vbo_p vbo = { 0 };
vert verts[6 * 2 * 3];

// Matrices
mat4f_t rot = {0};
mat4f_t model = {0};
mat4f_t proj = {0};

int init() {
	vec3f_t p1 = { 1.0f, 1.0f, 1.0f };
	vec3f_t p2 = { 1.0f, 1.0f, -1.0f };
	vec3f_t p3 = { 1.0f, -1.0f, 1.0f };
	vec3f_t p4 = { 1.0f, -1.0f, -1.0f };
	vec3f_t p5 = { -1.0f, 1.0f, 1.0f };
	vec3f_t p6 = { -1.0f, 1.0f, -1.0f };
	vec3f_t p7 = { -1.0f, -1.0f, 1.0f };
	vec3f_t p8 = { -1.0f, -1.0f, -1.0f };

	vec4f_t c1 = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4f_t c2 = { 1.0f, 1.0f, 0.0f, 1.0f };
	vec4f_t c3 = { 0.0f, 0.0f, 0.0f, 1.0f };
	vec4f_t c4 = { 1.0f, 0.0f, 1.0f, 1.0f };
	vec4f_t c5 = { 1.0f, 0.0f, 0.0f, 1.0f };
	vec4f_t c6 = { 1.0f, 1.0f, 0.0f, 1.0f };
	vec4f_t c7 = { 1.0f, 1.0f, 1.0f, 1.0f };
	vec4f_t c8 = { 0.0f, 1.0f, 0.0f, 1.0f };

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

	for (int i = 0; i < 6 * 2 * 3; i++) {
		verts[i].color.x = (float) (rand() % 255) / 255.0f;
		verts[i].color.y = (float) (rand() % 255) / 255.0f;
		verts[i].color.z = (float) (rand() % 255) / 255.0f;
	}

	vbo = CreateVertexBuffer(36, VERTEX_COORDS | COLOR);
	LoadIntoVertexBuffer(vbo, (char*) verts);

	SetProjectionMaxtrix(proj = createProjection(3.1415f / 2.0f, 1.0f, 1.0f, 6.0f));
	SetModelMatrix(model = mul_mat_mat4f(createTranslationMatrix(0, 0, 2.0f), createXrotation(1.0f)));

	rot = createXrotation(3.1415f / 2);

	return 0;
}

int loop() {
	BindBuffer(vbo);

	Draw();

	UnbindBuffer(vbo);
	return 0;
}

int destroy() {
	DestroyVertexBuffer(vbo);
	return 0;
}
