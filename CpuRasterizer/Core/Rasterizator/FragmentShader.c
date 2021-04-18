#include "CPURasterizerLocal.h"

// Defines
#define SQUARE(A, B, C) (0.5f * ( (A.x - C.x)*(B.y - C.y) - (A.y - C.y)*(B.x - C.x) ))

// Local methods
//=================================================
vec4f_t traversal_interpolate_4f(vec4f_t a1, vec4f_t a2, vec4f_t a3, float z_1, float z_2, float z_3, float s1, float s2, float s3) {
	vec4f_t A_z = Add_vec4f(Add_vec4f(Mul_vec4f(a1, s1 * z_1), Mul_vec4f(a2, s2 * z_2)), Mul_vec4f(a3, s3 * z_3));
	float z_ = 1.0f/(s1 * z_1 + s2 * z_2 + s3 * z_3);
	return Mul_vec4f(A_z, z_);
}

vec3f_t traversal_interpolate3f(vec3f_t a1, vec3f_t a2, vec3f_t a3, float z_1, float z_2, float z_3, float s1, float s2, float s3) {
	vec3f_t A_z = Add_vec3f(Add_vec3f(Mul_vec3f(a1, s1 * z_1), Mul_vec3f(a2, s2 * z_2)), Mul_vec3f(a3, s3 * z_3));
	float z_ = 1.0f/(s1 * z_1 + s2 * z_2 + s3 * z_3);
	return Mul_vec3f(A_z, z_);
}

vec2f_t traversal_interpolate_2f(vec2f_t a1, vec2f_t a2, vec2f_t a3, float z_1, float z_2, float z_3, float s1, float s2, float s3) {
	vec2f_t A_z = Add_vec2f(Add_vec2f(Mul_vec2f(a1, s1 * z_1), Mul_vec2f(a2, s2 * z_2)), Mul_vec2f(a3, s3 * z_3));
	float z_ = 1.0f/(s1 * z_1 + s2 * z_2 + s3 * z_3);
	return Mul_vec2f(A_z, z_);
}

float traversal_interpolate_f(float a1, float a2, float a3, float z_1, float z_2, float z_3, float s1, float s2, float s3) {
	float A_z = a1 * s1 * z_1 + a2 * s2 * z_2 + a3 * s3 * z_3;
	float z_ = 1.0f/(s1 * z_1 + s2 * z_2 + s3 * z_3);
	return A_z * z_;
}

int FragmentStage(grcntx_p cnt, float * in) {
	NOT_NULL(cnt);
	NOT_NULL(in);

	float * v1 = in + 0 * SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE / 4;
	float * v2 = in + 1 * SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE / 4;
	float * v3 = in + 2 * SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE / 4;

	vec4f_p a4_p = (vec4f_t *)v1;
	vec4f_p b4_p = (vec4f_t *)v2;
	vec4f_p c4_p = (vec4f_t *)v3;

	vec4f_t a4 = *a4_p;
	vec4f_t b4 = *b4_p;
	vec4f_t c4 = *c4_p;

	// Z
	float za = 1.0f / a4.w;
	float zb = 1.0f / b4.w;
	float zc = 1.0f / c4.w;

	// Triangle vertecies
	vec3f_t a3 = FromHomogeneousCoordinates_vec4f(a4);
	vec3f_t b3 = FromHomogeneousCoordinates_vec4f(b4);
	vec3f_t c3 = FromHomogeneousCoordinates_vec4f(c4);

	// Triangle square
	float s_ = 1.0f / SQUARE(a3, b3, c3);

	// Color
	vec4f_t color = {0};

	// Clipping
	float minx = MIN3(a3.x, b3.x, c3.x);
	float maxx = MAX3(a3.x, b3.x, c3.x);
	float miny = MIN3(a3.y, b3.y, c3.y);
	float maxy = MAX3(a3.y, b3.y, c3.y);

	int MINX = minx * WIDTH / 2 - 1;
	int MAXX = maxx * WIDTH / 2 + 1;
	int MINY = miny * HEIGHT / 2 - 1;
	int MAXY = maxy * HEIGHT / 2 + 1;

	// Attribs
	float attribs[SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE / 4] = { 0 };

	for (int x = MINX; x < MAXX; x++) {
		for (int y = MINY; y < MAXY; y++) {
			memset(attribs, 0, sizeof(attribs));

			vec3f_t cur = {.x = (float)(x) / (float)(WIDTH/2), .y = (float)(y)/(float)(HEIGHT/2), .z = 0};

			// Scalars
			float s1 = SQUARE(c3, b3, cur) * s_;
			float s2 = SQUARE(a3, c3, cur) * s_;
			float s3 = SQUARE(a3, b3, cur) * s_;

			if (s1 < 0) {
				s1 = -s1;
			}
			if (s2 < 0) {
				s2 = -s2;
			}
			if (s3 < 0) {
				s3 = -s3;
			}

			if (
					(((cur.x - a3.x)*(b3.y-a3.y)-(cur.y-a3.y)*(b3.x-a3.x))*((c3.x - a3.x)*(b3.y-a3.y)-(c3.y-a3.y)*(b3.x-a3.x)) >= 0) &&
					(((cur.x - b3.x)*(c3.y-b3.y)-(cur.y-b3.y)*(c3.x-b3.x))*((a3.x - b3.x)*(c3.y-b3.y)-(a3.y-b3.y)*(c3.x-b3.x)) >= 0) &&
					(((cur.x - c3.x)*(a3.y-c3.y)-(cur.y-c3.y)*(a3.x-c3.x))*((b3.x - c3.x)*(a3.y-c3.y)-(b3.y-c3.y)*(a3.x-c3.x)) >= 0)) {

				// Interpolation
				for (int i = 0; i < SHADER_PROGRAM_MAX_VERTEX_BUFFER_SIZE / 4; i++) {
					float * curAtr = attribs + i;
					*curAtr = traversal_interpolate_f(v1[i], v2[i], v3[i], za, zb, zc, s1, s2, s3);
				}

				// DEPTH
				//--------------------------------------------------------------------
				cur.z = attribs[2];

				// Depth test
				if (GetDepth(x, y) >= cur.z) {
					SetDepth(x, y, cur.z);
				} else {
					continue;
				}
				//--------------------------------------------------------------------

				if (cnt->fragmentShader != NULL) {
					cnt->fragmentShader(attribs + 4, (float*)(&color));
				} else {
					vec4f_p col_p = (vec4f_p)(attribs + 4);
					vec2f_p txc_p = (vec2f_p)(attribs + 8);

					// Colors
					//--------------------------------------------------------------------
					color = *col_p;
					//--------------------------------------------------------------------

					// Texture
					//--------------------------------------------------------------------
					color = Add_vec4f(color, GetPixel_vec2f(cnt->texture, *txc_p));
					//--------------------------------------------------------------------
				}

				color = Mul_vec4f(color, 254.0f);

				cnt->frameBufferSetPixel(x, y, color.x, color.y, color.z);
			}
		}
	}

	return 0;
}
//=================================================
