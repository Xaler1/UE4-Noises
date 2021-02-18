// Fill out your copyright notice in the Description page of Project Settings.

#include "Noise_SuiteBPLibrary.h"
#include "time.h"
#include "math.h"
#include "Randomiser.h"
#include "Cubic_Noise.h"

Cubic_Noise::Cubic_Noise()
{
}

Cubic_Noise::~Cubic_Noise()
{
}

Randomiser rnd;

float cubicInterpolate(float a, float b, float c, float d, float x) {
	return x * (x * (x * (-a + b - c + d) + 2 * a - 2 * b + c - d) - a + c) + b;
}

float OneD(float x) {
	float xL = floor(x);
	float X = x - xL;
	return cubicInterpolate(rnd.Random1(xL - 1, -1, 1),
					   rnd.Random1(xL, -1, 1, 1),
					   rnd.Random1(xL + 1, -1, 1),
					   rnd.Random1(xL + 2, -1, 1), X);
}

float TwoD(float x, float y) {
	float xL = floor(x);
	float yL = floor(y);
	float X = x - xL;
	float Y = y - yL;
	float ys[4];
	for (int yi = 0; yi < 4; yi++) {
		ys[yi] = cubicInterpolate(rnd.Random1(xL - 1, -1, 1, yL - 1 + yi),
							 rnd.Random1(xL, -1, 1, yL - 1 + yi),
							 rnd.Random1(xL + 1, -1, 1, yL - 1 + yi),
							 rnd.Random1(xL + 2, -1, 1, yL - 1 + yi), X);
	}
	return cubicInterpolate(ys[0], ys[1], ys[2], ys[3], Y);
}

float ThreeD(float x, float y, float z) {
	float xL = floor(x);
	float yL = floor(y);
	float zL = floor(z);
	float X = x - xL;
	float Y = y - yL;
	float Z = z - zL;
	float zs[4];
	float ys[4];
	for (int zi = 0; zi < 4; zi++) {
		for (int yi = 0; yi < 4; yi++) {
			ys[yi] = cubicInterpolate(rnd.Random1(xL - 1, -1, 1, yL - 1 + yi, zL - 1 + zi),
								 rnd.Random1(xL, -1, 1, yL - 1 + yi, zL - 1 + zi),
								 rnd.Random1(xL + 1, -1, 1, yL - 1 + yi, zL - 1 + zi),
								 rnd.Random1(xL + 2, -1, 1, yL - 1 + yi, zL - 1 + zi), X);
		}
		zs[zi] = cubicInterpolate(ys[0], ys[1], ys[2], ys[3], Y);
	}
	return  cubicInterpolate(zs[0], zs[1], zs[2], zs[3], Z);
}

float FourD(float x, float y, float z, float w) {
	float xL = floor(x);
	float yL = floor(y);
	float zL = floor(z);
	float wL = floor(w);
	float X = x - xL;
	float Y = y - yL;
	float Z = z - zL;
	float W = w - wL;
	float ws[4];
	float zs[4];
	float ys[4];
	for (int wi = 0; wi < 4; wi++) {
		for (int zi = 0; zi < 4; zi++) {
			for (int yi = 0; yi < 4; yi++) {
				ys[yi] = cubicInterpolate(rnd.Random1(xL - 1, -1, 1, yL - 1 + yi, zL - 1 + zi, wL - 1 + wi),
					rnd.Random1(xL, -1, 1, yL - 1 + yi, zL - 1 + zi, wL - 1 + wi),
					rnd.Random1(xL + 1, -1, 1, yL - 1 + yi, zL - 1 + zi, wL - 1 + wi),
					rnd.Random1(xL + 2, -1, 1, yL - 1 + yi, zL - 1 + zi, wL - 1 + wi), X);
			}
			zs[zi] = cubicInterpolate(ys[0], ys[1], ys[2], ys[3], Y);
		}
		ws[wi] = cubicInterpolate(zs[0], zs[1], zs[2], zs[3], Z);
	}
	return cubicInterpolate(ws[0], ws[1], ws[2], ws[3], W);
}

float UNoise_SuiteBPLibrary::OneD_Cubic_Noise(float x, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += OneD(x/scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::TwoD_Cubic_Noise(float x, float y, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += TwoD(x / scale, y / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::ThreeD_Cubic_Noise(float x, float y, float z, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += ThreeD(x / scale, y / scale, z / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::FourD_Cubic_Noise(float x, float y, float z, float w, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += FourD(x / scale, y / scale, z / scale, w / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}