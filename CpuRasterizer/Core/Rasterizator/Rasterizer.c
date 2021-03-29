#include "../Rasterizator/GraphicalContextLocal.h"

// Global variables
grcntx_t currentContext;
int errcode = 0;

// Global functions
int CalcVertexSizeByMask(int mask) {
	int res = 0;
	if (mask & VERTEX_COORDS) {
		res += 3 * sizeof(float);
	}
	if (mask & COLOR) {
		res += 4 * sizeof(float);
	}
	if (mask & TEXTURE_COORDS) {
		res += 2 * sizeof(float);
	}
	return res;
}

int SetFrameBufferCallFunction(int (*frameBufferSetPixel)(int, int, int, int, int)) {
	NOT_NULL(frameBufferSetPixel);
	currentContext.frameBufferSetPixel = frameBufferSetPixel;
	return 0;
}

int CreateVertexBuffer(int verts_number, int mask, vbo_p * result) {
	NOT_NULL(result);
	ENSURE(verts_number > 0);

	(*result) = malloc(sizeof(vbo_t));
	(*result)->mask = mask;
	(*result)->capacity = verts_number;
	(*result)->buffer = malloc(verts_number * CalcVertexSizeByMask(mask));
	return 0;
}

int DestroyVertexBuffer(vbo_p buf) {
	NOT_NULL(buf);

	free(buf->buffer);
	free(buf);
	return 0;
}

int LoadIntoVertexBuffer(char * raw_buf) {
	NOT_NULL(raw_buf);

	memcpy(currentContext.vbo->buffer, raw_buf, CalcVertexSizeByMask(currentContext.vbo->mask) * currentContext.vbo->capacity);
	return 0;
}

int BindBuffer(vbo_p buf) {
	NOT_NULL(buf);

	currentContext.vbo = buf;
	return 0;
}

int UnbindBuffer() {
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
	VertexShader(&currentContext);
	return 0;
}

int SetTextureLoader(int (*textureLoader)(char*, struct Texture **)) {
	NOT_NULL(textureLoader);
	currentContext.textureLoader = textureLoader;
	return 0;
}
