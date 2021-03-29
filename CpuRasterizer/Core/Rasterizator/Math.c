#include "../Rasterizator/GraphicalContextLocal.h"

vec4f_t Mul_mat4f_vec4f(mat4f_t mat, vec4f_t vec) {
	vec4f_t res = { 0 };
	for (int i = 0; i < 4; i++) {
		((float*) (&res))[i] = mat.mat[i][0] * vec.x + mat.mat[i][1] * vec.y
				+ mat.mat[i][2] * vec.z + mat.mat[i][3] * vec.w;
	}
	return res;
}

mat4f_t CreateYrotation_mat4f(float angle) {
	mat4f_t res = {0};

	float cos_ = cos(angle);
	float sin_ = sin(angle);

	res.mat[0][0] = cos_;
	res.mat[1][1] = 1;
	res.mat[2][2] = cos_;

	res.mat[2][0] = -sin_;
	res.mat[0][2] = sin_;

	res.mat[3][3] = 1;

	return res;
}

mat4f_t CreateXrotation_mat4f(float angle) {
	mat4f_t res = {0};

	float cos_ = cos(angle);
	float sin_ = sin(angle);

	res.mat[0][0] = 1;
	res.mat[1][1] = cos_;
	res.mat[2][2] = cos_;

	res.mat[2][1] = sin_;
	res.mat[1][2] = -sin_;
	res.mat[3][3] = 1;

	return res;
}

mat4f_t Mul_mat4f_mat4f(mat4f_t a, mat4f_t b) {
	mat4f_t res = {0};

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			res.mat[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				res.mat[i][j] += (a.mat[i][k] * b.mat[k][j]);
			}
		}
	}

	return res;
}

vec3f_t FromHomogeneousCoordinates_vec4f(vec4f_t vec) {
	vec3f_t res = { 0 };
	res.x = vec.x / vec.w;
	res.y = vec.y / vec.w;
	res.z = vec.z / vec.w;
	return res;
}

mat4f_t CreateTranslationMatrix_mat4f(float dx, float dy, float dz) {
	mat4f_t res = {0};
	res.mat[0][0] = 1;
	res.mat[1][1] = 1;
	res.mat[2][2] = 1;
	res.mat[3][3] = 1;
	res.mat[0][3] = dx;
	res.mat[1][3] = dy;
	res.mat[2][3] = dz;
	return res;
}

vec4f_t ToHomogeneousCoordinates_vec3f(vec3f_t vec) {
	vec4f_t res = { 0 };
	res.x = vec.x;
	res.y = vec.y;
	res.z = vec.z;
	res.w = 1;
	return res;
}

mat4f_t CreateProjection_mat4f(float fow, float aspect, float n, float f) {
	mat4f_t res = {0};
	res.mat[0][0] = (cos(fow / 2) / sin(fow/2)) / aspect;
	res.mat[1][1] = (cos(fow / 2) / sin(fow/2));
	res.mat[2][2] = (f + n) / (f - n);
	res.mat[3][2] = -2*f*n/(f-n);
	res.mat[2][3] = 1;
	return res;
}

float Dot_vec3f(vec3f_t a, vec3f_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

int Print_mat4f(mat4f_t mat) {
	for (int x = 0; x < 4; x++) {
		printf("[%0.1f  %0.1f  %0.1f  %0.1f]\n", mat.mat[x][0], mat.mat[x][1], mat.mat[x][2], mat.mat[x][3]);
	}
	return 0;
}

float Abs_vec3f(vec3f_t a) {
	return sqrt(Dot_vec3f(a, a));
}

vec3f_t Cross_vec3f(vec3f_t a, vec3f_t b) {
	vec3f_t res = {0};

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;

	return res;
}

vec3f_t Add_vec3f(vec3f_t a, vec3f_t b) {
	vec3f_t res = {0};
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return res;
}

vec3f_t Sub_vec3f(vec3f_t a, vec3f_t b) {
	vec3f_t res = {0};

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;

	return res;
}

vec3f_t Neg_vec3f(vec3f_t a) {
	vec3f_t res = {0};
	res.x = -a.x;
	res.y = -a.y;
	res.z = -a.z;
	return res;
}

float Square_vec3f(vec3f_t a, vec3f_t b, vec3f_t c) {
	float res = 0;

	vec3f_t p = Sub_vec3f(a, c);
	vec3f_t q = Sub_vec3f(b, c);

	vec3f_t n = Cross_vec3f(p, q);
	res = Abs_vec3f(n) / 2.0f;

	return res;
}

vec2f_t Add_vec2f(vec2f_t a, vec2f_t b) {
	vec2f_t v = {0};
	v.x = a.x + b.x;
	v.y = a.y + b.y;
	return v;
}

vec2f_t Mul_vec2f(vec2f_t a, float f) {
	vec2f_t v = {0};
	v.x = a.x * f;
	v.y = a.y * f;
	return v;
}

vec3f_t Mul_vec3f(vec3f_t a, float f) {
	vec3f_t res = {0};
	res.x = a.x * f;
	res.y = a.y * f;
	res.z = a.z * f;
	return res;
}

vec4f_t Add_vec4f(vec4f_t a, vec4f_t b) {
	vec4f_t res = {0};
	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	res.w = a.w + b.w;
	return res;
}

vec4f_t Mul_vec4f(vec4f_t a, float f) {
	vec4f_t res = {0};
	res.x = a.x * f;
	res.y = a.y * f;
	res.z = a.z * f;
	res.w = a.w * f;
	return res;
}
