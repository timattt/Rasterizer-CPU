#include "../Rasterizator/GraphicalContextLocal.h"

int VertexShader(grcntx_p cnt) {
	NOT_NULL(cnt);
	NOT_NULL(cnt->vbo);
	ENSURE(cnt->vbo->mask & VERTEX_COORDS);

	// Flush depth buffer
	flushDepthBuffer();

	// matrices
	mat4f_t proj = cnt->projectionMatrix;
	mat4f_t model = cnt->modelMatrix;

	// vbo
	vbo_p curBuf = cnt->vbo;
	int vertSize = CalcVertexSizeByMask(curBuf->mask);

	// primitive
	vert primitive[3] = { 0 };
	int primitive_vertex_index = 0;

	for (int currentVertex = 0; currentVertex < curBuf->capacity; currentVertex++) {
		vec3f_p pos_p = {0};
		vec4f_t pos4 = {0};
		vec3f_t fb_pos = {0};
		vec4f_t fb_pos4 = {0};

		char * vertBegin = curBuf->buffer + currentVertex * vertSize;

		// Vertex: 12 bytes
		//-----------------------
		pos_p = (vec3f_p)(vertBegin);
		pos4 = ToHomogeneousCoordinates_vec3f(*pos_p);
		fb_pos4 = Mul_mat4f_vec4f(proj, Mul_mat4f_vec4f(model, pos4));
		fb_pos = FromHomogeneousCoordinates_vec4f(fb_pos4);

		primitive[primitive_vertex_index].pos = fb_pos;

		vertBegin += sizeof(vec3f_t);
		//-----------------------

		// Color: 16 bytes
		//-----------------------
		if (curBuf->mask & COLOR) {
			memcpy(&primitive[primitive_vertex_index].color, vertBegin, sizeof(vec4f_t));
			vertBegin += sizeof(vec4f_t);
		}
		//-----------------------

		// Texture coords: 8 bytes
		if (curBuf->mask & TEXTURE_COORDS) {
			memcpy(&primitive[primitive_vertex_index].txtr_pos, vertBegin, sizeof(vec2f_t));
			vertBegin += sizeof(vec2f_t);
		}

		primitive_vertex_index++;

		if (primitive_vertex_index == 3) {
			primitive_vertex_index = 0;
			FragmentShader(cnt, primitive);
			memset(primitive, 0, 3 * sizeof(vert));
		}

	}

	return 0;
}
