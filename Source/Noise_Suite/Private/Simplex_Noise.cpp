// Fill out your copyright notice in the Description page of Project Settings.


#include "Simplex_Noise.h"
#include "Noise_Utils.h"
#include "Noise_SuiteBPLibrary.h"
#include "Randomiser.h"
#include "math.h"
#include "stdlib.h"
#include "SimplexInfo.h"


typedef struct LatticePoint2D LatticePoint2D;
typedef struct LatticePoint4D LatticePoint4D;

SimplexInfo smin;
extern Randomiser rnd;



float Two_Simplex(float x, float y) {
	float offset = (x + y) * SQUISH_2D;
	x += offset;
	y += offset;

	int xL = floor(x);
	int yL = floor(y);
	float xi = x - xL;
	float yi = y - yL;
	offset = (xi + yi) * STRETCH_2D;
	float offsetx = xi + offset;
	float offsety = yi + offset;

	int a = (int)(xi + yi);
	int index =
		(a << 2) |
		(int)(xi - yi / 2 + 1 - a / 2.0) << 3 |
		(int)(yi - xi / 2 + 1 - a / 2.0) << 4;
	float value = 0;

	for (int i = 0; i < 4; i++) {
		LatticePoint2D point = smin.POINTS_2D[index + i];
		float dx = offsetx + point.dx;
		float dy = offsety + point.dy;
		float attn = 2.0/3.0 - pow(dx, 2) - pow(dy, 2);
		if (attn > 0) {
			FVector2D random_vector = rnd.Random2(xL + point.X, yL + point.Y, -1, 1);
			float gradient = random_vector.X * dx + random_vector.Y * dy;
			value += pow(attn, 4) * gradient;
		}
	}

	return value;
}


float Three_Simplex(float x, float y, float z) {
	float offset = (2.0 / 3.0) * (x + y + z);
	x = offset - x;
	y = offset - y;
	z = offset - z;
	int xL = floor(x);
	int yL = floor(y);
	int zL = floor(z);
	float xi = x - xL;
	float yi = y - yL;
	float zi = z - zL;

	int xht = (int)(xi + 0.5), yht = (int)(yi + 0.5), zht = (int)(zi + 0.5);
	int index = (xht << 0) | (yht << 1) | (zht << 2);

	float value = 0;
	LatticePoint3D *point = smin.POINTS_3D[index];
	while (point != nullptr) {
		float dx = xi + point->dx;
		float dy = yi + point->dy;
		float dz = zi + point->dz;
		float attn = 0.75 - dx * dx - dy * dy - dz * dz;
		if (attn < 0)
		{
			point = point->NextOnFailure;
		}
		else
		{
			FVector random_vector = rnd.Random3(xL + point->X, yL + point->Y, zL + point->Z, -1, 1);
			float gradient = random_vector.X * dx + random_vector.Y * dy + random_vector.Z * dz;

			value += pow(attn, 4) * gradient;
			point = point->NextOnSuccess;
		}
	}
	return value;
}

float Four_Simplex(float x, float y, float z, float w) {
	float offset = (x + y + z + w) * SQUISH_4D;
	x += offset;
	y += offset;
	z += offset;
	w += offset;
	int xL = floor(x);
	int yL = floor(y);
	int zL = floor(z);
	int wL = floor(w);
	float offsetx = x - xL;
	float offsety = y - yL;
	float offsetz = z - zL;
	float offsetw = w - wL;

	offset = (offsetx + offsety + offsetz + offsetw) * STRETCH_4D;
	float xi = offsetx + offset;
	float yi = offsety + offset;
	float zi = offsetz + offset;
	float wi = offsetw + offset;

	int index = (((int)floor(x * 4) & 3) << 0)
		| (((int)floor(y * 4) & 3) << 2)
		| (((int)floor(z * 4) & 3) << 4)
		| (((int)floor(w * 4) & 3) << 6);

	float value = 0;
	for (int i = 0; i < smin.lengths[index]; i++) {
		LatticePoint4D point = smin.POINTS_4D[index][i];
		float dx = xi + point.dx;
		float dy = yi + point.dy;
		float dz = zi + point.dz;
		float dw = wi + point.dw;
		float attn = 0.8 - dx * dx - dy * dy - dz * dz - dw * dw;

		if (attn > 0) {
			FVector4 random_vector = rnd.Random4(xL + point.X, yL + point.Y, zL + point.Z, wL + point.W, -1, 1);
			float gradient = random_vector.X * dx + random_vector.Y * dy + random_vector.Z * dz + random_vector.W * dw;
			
			value += pow(attn, 4) * gradient;
		}
	}

	return value;
}

float UNoise_SuiteBPLibrary::OneD_Simplex_Noise(float x, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Two_Simplex(x / scale, 0) * amplitude * 18;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::TwoD_Simplex_Noise(float x, float y, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Two_Simplex(x / scale, y / scale) * amplitude * 18;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::ThreeD_Simplex_Noise(float x, float y, float z, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Three_Simplex(x / scale, y / scale, z / scale) * amplitude * 15;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::FourD_Simplex_Noise(float x, float y, float z, float w, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Four_Simplex(x / scale, y / scale, z / scale, w / scale) * amplitude * 12;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}