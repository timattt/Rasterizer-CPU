#include "CPURasterizerLocal.h"

// Global variables
grcntx_t currentContext = {0};
int errcode = 0;
char errorMessage[ERROR_MESSAGE_LEN] = {0};

// Global functions
int FlushDepthBuffer() {
	NOT_NULL(currentContext.depthBuffer);

	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		currentContext.depthBuffer[i] = 20000.0f;
	}
	return 0;
}

int EnsureVBOComponent(int mask) {
	if ((mask ^ currentContext.vbo_mask) != 0) {
		return -1;
	}
	return 0;
}

// |1          |2    |4             |8     |...  |
// |Vert coords|Color|Texture coords|Normal|Other|
int CalcVertexSizeByMask() {
	int res = 0;
	if (currentContext.vbo_mask & VERTEX_COORDS) {
		res += 3 * sizeof(float);
	}
	if (currentContext.vbo_mask & COLOR) {
		res += 4 * sizeof(float);
	}
	if (currentContext.vbo_mask & TEXTURE_COORDS) {
		res += 2 * sizeof(float);
	}
	if (currentContext.vbo_mask & NORMAL) {
		res += 3 * sizeof(float);
	}
	res += (currentContext.vbo_mask >> DEFAULT_ATTRIBUTES_QUANTITY) * sizeof(float);
	return res;
}

int AdditionalVertexDataMask(int quant) {
	return quant << DEFAULT_ATTRIBUTES_QUANTITY;
}

int SetFrameBufferCallFunction(int (*frameBufferSetPixel)(int, int, int, int, int)) {
	NOT_NULL(frameBufferSetPixel);
	currentContext.frameBufferSetPixel = frameBufferSetPixel;
	return 0;
}

int CreateVertexBuffer(int total_verts, vbo_t * result) {
	NOT_NULL(result);
	ENSURE(total_verts > 0);
	AllocateGraphicalMemory(total_verts * CalcVertexSizeByMask(), result);
	return 0;
}

int DestroyVertexBuffer(vbo_t buf) {
	NOT_NULL(buf);

	FreeGraphicalMemory(buf);

	return 0;
}

int LoadIntoVertexBuffer(char * raw_buf, int cap) {
	NOT_NULL(raw_buf);
	NOT_NULL(currentContext.vbo);

	memcpy(currentContext.vbo, raw_buf, cap * CalcVertexSizeByMask());
	return 0;
}

int BindBuffer(vbo_t buf) {
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

int SetProjectionMatrix(mat4f_t proj) {
	currentContext.projectionMatrix = proj;
	return 0;
}

int Draw(int total_prims) {
	VertexStage(&currentContext, total_prims);
	return 0;
}

int SetTextureLoader(int (*textureLoader)(char*, struct Texture **)) {
	NOT_NULL(textureLoader);
	currentContext.textureLoader = textureLoader;
	return 0;
}

int InitContext() {
	ENSURE(currentContext.depthBuffer == NULL);
	ENSURE(currentContext.graphicalMemory == NULL);

	currentContext.depthBuffer = (float*)malloc(WIDTH * HEIGHT * sizeof(float));
	currentContext.graphicalMemory = (char*)malloc(MAX_GRAPHICAL_MEMORY_SIZE);
	currentContext.emptyMem = currentContext.graphicalMemory;

	ENSURE(currentContext.depthBuffer && currentContext.graphicalMemory);

	return 0;
}

int DestroyContext() {
	NOT_NULL(currentContext.depthBuffer);
	NOT_NULL(currentContext.graphicalMemory);

	free(currentContext.depthBuffer);
	free(currentContext.graphicalMemory);

	currentContext.depthBuffer = NULL;
	currentContext.graphicalMemory = NULL;
	return 0;
}

int SetVBOMask(int mask) {
	currentContext.vbo_mask = mask;
	return 0;
}

int SetDepth(int x, int y, float val) {
	NOT_NULL(currentContext.depthBuffer);
	currentContext.depthBuffer[((x + WIDTH / 2) + (HEIGHT / 2 - y) * HEIGHT)] = val;
	return 0;
}

float GetDepth(int x, int y) {
	NOT_NULL(currentContext.depthBuffer);
	ENSURE(x >= -WIDTH / 2 && y >= -HEIGHT / 2 && x < WIDTH / 2 && y < HEIGHT / 2);
	return currentContext.depthBuffer[((x + WIDTH / 2) + (HEIGHT / 2 - y) * HEIGHT)];
}

int PrintErrorMessage() {
	if (strlen(errorMessage) > 0) {
		printf("%s", errorMessage);
	} else {
		printf("No error is found!\n");
	}
	fflush(stdout);
	return 0;
}

int GetErrorMessage(char * dest) {
	NOT_NULL(dest);
	memset(dest, 0, ERROR_MESSAGE_LEN);
	if (strlen(errorMessage) > 0) {
		sprintf(dest, "%s", errorMessage);
	} else {
		sprintf(dest, "No error is found!\n");
	}
	return 0;
}

int AllocateGraphicalMemory(int sz, char ** dest) {
	NOT_NULL(dest);
	ENSURE(sz >= 0);

	ENSURE_M(currentContext.emptyMem + sz < currentContext.graphicalMemory + MAX_GRAPHICAL_MEMORY_SIZE, "Out of graphical memory!");

	(*dest) = currentContext.emptyMem;
	currentContext.emptyMem += sz;

	return 0;
}

int FreeGraphicalMemory(char * ptr) {
	// Memory may be freed here but I am too lazy to do normal memory allocation system.
	return 0;
}

int SetShaderProgram(int (*vertexShader)(float * in, float * out), int (*fragmentShader)(float * in, float out[4])) {
	NOT_NULL(vertexShader);
	NOT_NULL(fragmentShader);

	currentContext.vertexShader = vertexShader;
	currentContext.fragmentShader = fragmentShader;

	return 0;
}

int ResetShaderProgram() {
	currentContext.vertexShader = NULL;
	currentContext.fragmentShader = NULL;

	return 0;
}

mat4f_t GetProjectionMatrix() {
	return currentContext.projectionMatrix;
}
mat4f_t GetModelMatrix() {
	return currentContext.modelMatrix;
}
