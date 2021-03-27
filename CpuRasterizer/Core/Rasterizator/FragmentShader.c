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

	// Triangle vertecies
	vec3f_t a = primitive[0].pos;
	vec3f_t b = primitive[1].pos;
	vec3f_t c = primitive[2].pos;

	// Triangle plane
	vec3f_t p = Sub_vec3f(a, b);
	vec3f_t q = Sub_vec3f(c, b);

	vec3f_t n = Cross_vec3f(p, q);

	float A = n.x;
	float B = n.y;
	float C = n.z;
	float D = -(A * a.x + B * a.y + C * a.z);

	// Projecting
	a.z = 0;
	b.z = 0;
	c.z = 0;

	// Triangle square
	float s_ = 1.0f / SQUARE(a, b, c);

	for (int x = 1 - WIDTH / 2; x < WIDTH / 2; x++) {
		for (int y = 1 - HEIGHT / 2; y < HEIGHT / 2; y++) {
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

			// To find interpolated depth we have to project cur onto primitive plane
			cur.z = (-D - A * cur.x - B * cur.y) / C;

			if (
					(((cur.x - a.x)*(b.y-a.y)-(cur.y-a.y)*(b.x-a.x))*((c.x - a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)) >= 0) &&
					(((cur.x - b.x)*(c.y-b.y)-(cur.y-b.y)*(c.x-b.x))*((a.x - b.x)*(c.y-b.y)-(a.y-b.y)*(c.x-b.x)) >= 0) &&
					(((cur.x - c.x)*(a.y-c.y)-(cur.y-c.y)*(a.x-c.x))*((b.x - c.x)*(a.y-c.y)-(b.y-c.y)*(a.x-c.x)) >= 0)) {

				// CVV box test
				if (abs(cur.z) > 1) {
					continue;
				}

				// Depth test
				if (getDepth(x, y) >= cur.z) {
					setDepth(x, y, cur.z);
				} else {
					continue;
				}

				// Colors
				int r = 254.0f * (primitive[0].color.x * s1 + primitive[1].color.x * s2 + primitive[2].color.x * s3);
				int g = 254.0f * (primitive[0].color.y * s1 + primitive[1].color.y * s2 + primitive[2].color.y * s3);
				int b = 254.0f * (primitive[0].color.z * s1 + primitive[1].color.z * s2 + primitive[2].color.z * s3);

				cnt->frameBufferSetPixel(x, y, r, g, b);
			}
		}
	}

	return 0;
}
//=================================================
