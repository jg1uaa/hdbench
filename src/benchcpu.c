#include "proto.h"
#include "variable.h"

gint32 bench_integer(void)
{
	gint	i;
	gint32	result = 0;
	volatile gint32	x;
	volatile static gint32	a = 256;
	volatile static gint32	b = 128;

	while (1) {
		for (i = 0; i < 300; i++) {
			x = a * b;
			x = a * b;
			x = a / b;
			x = a / b;
			x = a + b;
			x = a + b;
			x = a - b;
			x = a - b;
		}

		result++;
		if (done_flag) return result;
	}
}

gint32 bench_float(void)
{
	gint	i;
	gint32	result = 0;
	volatile gfloat	x;
	volatile static gfloat	a = 256.0;
	volatile static gfloat	b = 128.0;

	while (1) {
		for (i = 0; i < 300; i++) {
			x = a * b;
			x = a * b;
			x = a / b;
			x = a / b;
			x = a + b;
			x = a + b;
			x = a - b;
			x = a - b;
		}

		result++;
		if (done_flag) return result;
	}
}

gint32 bench_memory(gchar *src, gchar *dest)
{
	gint	i, j;
	gint32	*s, *d;
	gint32	result = 0;

	while (1) {
		// src, dest must be 4-byte aligned
		s = (gint32 *)src;
		d = (gint32 *)dest;

		for (i = 0; i < 64; i++) {
			for (j = 0; j < 8192; j++) {	// 2MB/4/64
				*d++ = *s++;
			}

			result++;
			if (done_flag) return result;
		}
	}
}
