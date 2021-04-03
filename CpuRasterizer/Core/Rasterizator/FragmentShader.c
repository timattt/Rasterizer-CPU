#include "../Rasterizator/GraphicalContextLocal.h"

// Local vars
float depth_buf[WIDTH * HEIGHT];

// Defines
#define SQUARE(A, B, C) (0.5f * ( (A.x - C.x)*(B.y - C.y) - (A.y - C.y)*(B.x - C.x) ))

// Local methods
//=================================================
void setDepth(int x, int y, float val) {
	depth_buf[((x + WIDTH / 2) + (HEIGHT / 2 - y) * HEIGHT)] = val;
}

float getDepth(int x, int y) {
	return depth_buf[((x + WIDTH / 2) + (HEIGHT / 2 - y) * HEIGHT)];
}

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
//=================================================

// Global methods
//=================================================
int flushDepthBuffer() {
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		depth_buf[i] = 20000.0f;
	}
	return 0;
}

int FragmentShader(grcntx_p cnt, vert* primitive) {
	NOT_NULL(cnt);
	NOT_NULL(primitive);

	// Z
	float za = 1.0f / primitive[0].pos.w;
	float zb = 1.0f / primitive[1].pos.w;
	float zc = 1.0f / primitive[2].pos.w;

	// Triangle vertecies
	vec3f_t a = FromHomogeneousCoordinates_vec4f(primitive[0].pos);
	vec3f_t b = FromHomogeneousCoordinates_vec4f(primitive[1].pos);
	vec3f_t c = FromHomogeneousCoordinates_vec4f(primitive[2].pos);

	// Texture pos
	vec2f_t at = primitive[0].txtr_pos;
	vec2f_t bt = primitive[1].txtr_pos;
	vec2f_t ct = primitive[2].txtr_pos;

	vec2f_t cur_tp = {0};
	vec4f_t txtr_col = {0};

	// Triangle square
	float s_ = 1.0f / SQUARE(a, b, c);

	// Color
	vec4f_t color = {0};

	// Clipping
	float minx = MIN3(a.x, b.x, c.x);
	float maxx = MAX3(a.x, b.x, c.x);
	float miny = MIN3(a.y, b.y, c.y);
	float maxy = MAX3(a.y, b.y, c.y);

	int MINX = minx * WIDTH / 2 - 1;
	int MAXX = maxx * WIDTH / 2 + 1;
	int MINY = miny * HEIGHT / 2 - 1;
	int MAXY = maxy * HEIGHT / 2 + 1;

	for (int x = MINX; x < MAXX; x++) {
		for (int y = MINY; y < MAXY; y++) {
			vec3f_t cur = {.x = (float)(x) / (float)(WIDTH/2), .y = (float)(y)/(float)(HEIGHT/2), .z = 0};

			// Scalars
			float s1 = SQUARE(c, b, cur) * s_;
			float s2 = SQUARE(a, c, cur) * s_;
			float s3 = SQUARE(a, b, cur) * s_;

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
					(((cur.x - a.x)*(b.y-a.y)-(cur.y-a.y)*(b.x-a.x))*((c.x - a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)) >= 0) &&
					(((cur.x - b.x)*(c.y-b.y)-(cur.y-b.y)*(c.x-b.x))*((a.x - b.x)*(c.y-b.y)-(a.y-b.y)*(c.x-b.x)) >= 0) &&
					(((cur.x - c.x)*(a.y-c.y)-(cur.y-c.y)*(a.x-c.x))*((b.x - c.x)*(a.y-c.y)-(b.y-c.y)*(a.x-c.x)) >= 0)) {

				// DEPTH
				//--------------------------------------------------------------------
				cur.z = traversal_interpolate_f(a.z, b.z, c.z, za, zb, zc, s1, s2, s3);

				// Depth test
				if (getDepth(x, y) >= cur.z) {
					setDepth(x, y, cur.z);
				} else {
					continue;
				}
				//--------------------------------------------------------------------

				// Colors
				//--------------------------------------------------------------------
				color = traversal_interpolate_4f(primitive[0].color, primitive[1].color, primitive[2].color,
						za, zb, zc, s1, s2, s3);
				//--------------------------------------------------------------------

				// Texture
				//--------------------------------------------------------------------
				if (cnt->texture != NULL && at.x >= -0.01f) {
					cur_tp = traversal_interpolate_2f(at, bt, ct, za, zb, zc, s1, s2, s3);
					GetPixel(cnt->texture, cur_tp, &txtr_col);
					color = txtr_col;//Add_vec4f(color, txtr_col);
				}
				//--------------------------------------------------------------------

				color = Mul_vec4f(color, 254.0f);

				cnt->frameBufferSetPixel(x, y, color.x, color.y, color.z);
			}
		}
	}

	return 0;
}
//=================================================
