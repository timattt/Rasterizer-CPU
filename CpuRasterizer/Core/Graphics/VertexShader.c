#include "GraphicalContext.h"

int VertexShader(grcntx_t cnt) {

	vbo_p curBuf = cnt.vbo;
	mat4f_t proj = cnt.projectionMatrix;
	mat4f_t model = cnt.modelMatrix;
	int vertSize = CalcVertexSizeByMask(curBuf->mask);

	if (curBuf == NULL) {
		return -1;
	}
	if (!(curBuf->mask & VERTEX_COORDS)) {
		return -1;
	}

	vert prim[3] = { 0 };
	int vertex_in_primitive_number = 0;

	for (int currentVertex = 0; currentVertex < curBuf->capacity; currentVertex++) {
		vec3f_p pos_p = {0};
		vec4f_t pos4 = {0};
		vec3f_t fb_pos = {0};
		vec4f_t fb_pos4 = {0};

		char * vertBegin = curBuf->buffer + currentVertex * vertSize;

		// Vertex
		pos_p = (vec3f_p)(vertBegin);
		pos4 = toHomogeneousCoordinates(*pos_p);
		fb_pos4 = mul_mat_vec4f(proj, mul_mat_vec4f(model, pos4));
		fb_pos = fromHomogeneousCoordinates(fb_pos4);

		prim[vertex_in_primitive_number].pos = fb_pos;

		vertBegin += sizeof(vec3f_t);

		// Color
		if (curBuf->mask & COLOR) {
			memcpy(&prim[vertex_in_primitive_number].color, vertBegin, sizeof(vec4f_t));
			vertBegin += sizeof(vec4f_t);
		}

		vertex_in_primitive_number++;

		if (vertex_in_primitive_number == 3) {
			vertex_in_primitive_number = 0;
			FragmentShader(prim);
			memset(prim, 0, 3 * sizeof(vert));
		}

	}

	return 0;
}
