#include "GraphicalContext.h"

float depth_buf[WIDTH * HEIGHT];

#define DB(X, Y) depth_buf[(X + Y * HEIGHT)]
#define DB_CVV(X, Y) DB((X + WIDTH / 2), (HEIGHT / 2 - Y))

int FragmentShader(vert* primitive) {
	memset(depth_buf, 2.0f, WIDTH * HEIGHT);

	vec3f_t a = primitive[0].pos;
	vec3f_t b = primitive[1].pos;
	vec3f_t c = primitive[2].pos;

	double az = a.z;
	double bz = b.z;
	double cz = c.z;

	a.z = 0;
	b.z = 0;
	c.z = 0;

	double s = calcSquare(a, b, c);

	for (int x = 1 - WIDTH / 2; x < WIDTH / 2; x++) {
		for (int y = 1 - HEIGHT / 2; y < HEIGHT / 2; y++) {
			vec3f_t cur = {.x = (double)(x) / (double)(WIDTH/2), .y = (double)(y)/(double)(HEIGHT/2), .z = 0};

			double s1 = calcSquare(a, b, cur) / s;
			double s2 = calcSquare(b, c, cur) / s;
			double s3 = calcSquare(a, c, cur) / s;

			double z = s1 * az + s2 * bz + s3 * cz;

			if (
					(((cur.x - a.x)*(b.y-a.y)-(cur.y-a.y)*(b.x-a.x))*((c.x - a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)) >= 0) &&
					(((cur.x - b.x)*(c.y-b.y)-(cur.y-b.y)*(c.x-b.x))*((a.x - b.x)*(c.y-b.y)-(a.y-b.y)*(c.x-b.x)) >= 0) &&
					(((cur.x - c.x)*(a.y-c.y)-(cur.y-c.y)*(a.x-c.x))*((b.x - c.x)*(a.y-c.y)-(b.y-c.y)*(a.x-c.x)) >= 0)) {

				if (abs(z) > 1) {
					continue;
				}

				if (DB_CVV(x, y) > z) {
					DB_CVV(x, y) = z;
				} else {
					continue;
				}

				int r = 254.0f * (primitive[0].color.x * s1 + primitive[1].color.x * s2 + primitive[2].color.x * s3);
				int g = 254.0f * (primitive[0].color.y * s1 + primitive[1].color.y * s2 + primitive[2].color.y * s3);
				int b = 254.0f * (primitive[0].color.z * s1 + primitive[1].color.z * s2 + primitive[2].color.z * s3);

				SetFbPixel(x, y, r, g, b);
			}
		}
	}

	return 0;
}
