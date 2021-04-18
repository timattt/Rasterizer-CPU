#include "CPURasterizerLocal.h"

//=================================================
// Local functions
int fixedPipeLine(grcntx_p cnt, float * in, float * out) {
	NOT_NULL(in);
	NOT_NULL(out);
	NOT_NULL(cnt);

	// matrices
	mat4f_t proj = cnt->projectionMatrix;
	mat4f_t model = cnt->modelMatrix;

	vec3f_p pos_p = { 0 };
	vec4f_t pos4 = { 0 };
	vec4f_t fb_pos4 = { 0 };

	char *vertBegin = (char*) in;
	vert_t * prim = (vert_t*) out;

	// Vertex: 12 bytes
	//-----------------------
	pos_p = (vec3f_p) (vertBegin);
	pos4 = ToHomogeneousCoordinates_vec3f(*pos_p);
	fb_pos4 = Mul_mat4f_vec4f(proj, Mul_mat4f_vec4f(model, pos4));

	prim->pos = fb_pos4;

	vertBegin += sizeof(vec3f_t);
	//-----------------------

	// Color: 16 bytes
	//-----------------------
	if (cnt->vbo_mask & COLOR) {
		memcpy(&prim->color, vertBegin, sizeof(vec4f_t));
		vertBegin += sizeof(vec4f_t);
	}
	//-----------------------

	// Texture coords: 8 bytes
	if (cnt->vbo_mask & TEXTURE_COORDS) {
		memcpy(&prim->txtr_pos, vertBegin, sizeof(vec2f_t));
		vertBegin += sizeof(vec2f_t);
	}
	return 0;
}

//=================================================

// Global functions
//=================================================

int VertexStage(grcntx_p cnt, int total_prim) {
	NOT_NULL(cnt);
	NOT_NULL(cnt->vbo);
	ENSURE(cnt->vbo_mask & VERTEX_COORDS);

	// vbo
	int vertSize = CalcVertexSizeByMask(cnt->vbo_mask);

	// Transfer buffer
	char transfer[VERTICES_PER_PRIMITIVE * SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE] = { 0 };

	for (int currentVertex = 0; currentVertex < total_prim; currentVertex++) {
		char *in = cnt->vbo + currentVertex * vertSize;
		char *out = transfer + (currentVertex % VERTICES_PER_PRIMITIVE) * SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE;

		// SHADER PROGRAM
		if (currentContext.vertexShader != NULL) {
			currentContext.vertexShader((float*) in, (float*) out);
		} else {
			fixedPipeLine(cnt, (float*) in, (float*) out);
		}


		if ((currentVertex + 1) % VERTICES_PER_PRIMITIVE == 0) {
			FragmentStage(cnt, (float*) transfer);
			memset(transfer, 0, 3 * SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE);
		}
	}

	return 0;
}
//=================================================
