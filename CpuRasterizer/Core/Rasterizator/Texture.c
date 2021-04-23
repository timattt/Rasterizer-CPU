#include "CPURasterizerLocal.h"

int LoadTexture(char * path, txtr_p * dest) {
	NOT_NULL(path);
	NOT_NULL(dest);
	NOT_NULL(currentContext.textureLoader);

	currentContext.textureLoader(path, dest);

	return 0;
}

int BindTexture(txtr_p txt) {
	NOT_NULL(txt);
	currentContext.texture = txt;
	return 0;
}

txtr_p GetBindedTexture() {
	return currentContext.texture;
}

int UnbindTexture() {
	currentContext.texture = NULL;
	return 0;
}

int CreateTexture(int width, int height, char * pixs, txtr_p * dest) {
	NOT_NULL(dest);

	AllocateGraphicalMemory(sizeof(txtr_t), (char**)dest);

	(*dest)->width = width;
	(*dest)->height = height;
	(*dest)->pixels = NULL;

	AllocateGraphicalMemory(width * height * BYTES_PER_PIXEL, &((*dest)->pixels));

	memcpy((*dest)->pixels, pixs, width * height * BYTES_PER_PIXEL);

	return 0;
}

int DestroyTexture(txtr_p txt) {
	NOT_NULL(txt);

	FreeGraphicalMemory(txt->pixels);

	return 0;
}

float process(char c) {
	int v = c;
	v += 256;
	if (v > 256) {
		v %= 256;
	}
	return (float)(v) / 256.0f;
}

vec4f_t GetPixel_vec2f(txtr_p txtr, vec2f_t pos) {
	if (txtr == NULL || pos.x < -0.01) {
		vec4f_t bad = {0};
		return bad;
	}

	vec4f_t dest = { 0 };

	int x = pos.x * txtr->width;
	int y = pos.y * txtr->height;

	char * ptr = txtr->pixels + 4 * (y * txtr->width + x);

	dest.x = process(ptr[2]);
	dest.y = process(ptr[1]);
	dest.z = process(ptr[0]);
	dest.w = process(ptr[3]);

	return dest;
}
