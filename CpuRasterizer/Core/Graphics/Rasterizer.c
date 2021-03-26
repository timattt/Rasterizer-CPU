#include "GraphicalContext.h"

// Local variables
grcntx_t currentContext;

// Local functions
int CalcVertexSizeByMask(int mask) {
	int res = 0;
	if (mask & VERTEX_COORDS) {
		res += 3 * sizeof(float);
	}
	if (mask & COLOR) {
		res += 4 * sizeof(float);
	}
	return res;
}

// Global functions
vbo_p CreateVertexBuffer(int verts_number, int mask) {
	vbo_p res = malloc(sizeof(vbo_t));
	res->mask = mask;
	res->capacity = verts_number;
	res->buffer = malloc(verts_number * CalcVertexSizeByMask(mask));
	return res;
}

int DestroyVertexBuffer(vbo_p buf) {
	free(buf->buffer);
	free(buf);
	return 0;
}

int LoadIntoVertexBuffer(vbo_p buf, char * raw_buf) {
	memcpy(buf->buffer, raw_buf, CalcVertexSizeByMask(buf->mask) * buf->capacity);
	return 0;
}

int BindBuffer(vbo_p buf) {
	currentContext.vbo = buf;
	return 0;
}

int UnbindBuffer(vbo_p buf) {
	currentContext.vbo = NULL;
	return 0;
}

int SetModelMatrix(mat4f_t model) {
	currentContext.modelMatrix = model;
	return 0;
}

int SetProjectionMaxtrix(mat4f_t proj) {
	currentContext.projectionMatrix = proj;
	return 0;
}

int Draw() {
	VertexShader(currentContext);
	return 0;
}
