// Fill out your copyright notice in the Description page of Project Settings.


#include "Value_Noise.h"
#include "Noise_Utils.h"
#include "Noise_SuiteBPLibrary.h"
#include "Randomiser.h"

extern Randomiser rnd;

float One_Value(float x) {
	int xL = floor(x);
	int xU = xL + 1;
	float X = x - xL;
	return smoothInterpolate(rnd.Random1(xL, -1, 1), rnd.Random1(xU, -1, 1), X);
}

float Two_Value(float x, float y) {
	int xL = floor(x);
	int yL = floor(y);
	int xU = xL + 1;
	int yU = yL + 1;
	float X = x - xL;
	float Y = y - yL;
	return smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL), rnd.Random1(xU, -1, 1, yL), X),
							 smoothInterpolate(rnd.Random1(xL, -1, 1, yU), rnd.Random1(xU, -1, 1, yU), X), Y);
}

float Three_Value(float x, float y, float z) {
	int xL = floor(x);
	int yL = floor(y);
	int zL = floor(z);
	int xU = xL + 1;
	int yU = yL + 1;
	int zU = zL + 1;
	float X = x - xL;
	float Y = y - yL;
	float Z = z - zL;

	return smoothInterpolate(smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL, zL), rnd.Random1(xU, -1, 1, yL, zL), X),
											   smoothInterpolate(rnd.Random1(xL, -1, 1, yU, zL), rnd.Random1(xU, -1, 1, yU, zL), X), Y),
							 smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL, zU), rnd.Random1(xU, -1, 1, yL, zU), X),
											   smoothInterpolate(rnd.Random1(xL, -1, 1, yU, zU), rnd.Random1(xU, -1, 1, yU, zU), X), Y), Z);
}

float Four_Value(float x, float y, float z, float w) {
	int xL = floor(x);
	int yL = floor(y);
	int zL = floor(z);
	int wL = floor(w);
	int xU = xL + 1;
	int yU = yL + 1;
	int zU = zL + 1;
	int wU = wL + 1;
	float X = x - xL;
	float Y = y - yL;
	float Z = z - zL;
	float W = w - wL;

	return smoothInterpolate(smoothInterpolate(smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL, zL, wL), rnd.Random1(xU, -1, 1, yL, zL, wL), X),
																 smoothInterpolate(rnd.Random1(xL, -1, 1, yU, zL, wL), rnd.Random1(xU, -1, 1, yU, zL, wL), X), Y),
											   smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL, zU, wL), rnd.Random1(xU, -1, 1, yL, zU, wL), X),
																 smoothInterpolate(rnd.Random1(xL, -1, 1, yU, zU, wL), rnd.Random1(xU, -1, 1, yU, zU, wL), X), Y), Z),
							 smoothInterpolate(smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL, zL, wU), rnd.Random1(xU, -1, 1, yL, zL, wU), X),
																 smoothInterpolate(rnd.Random1(xL, -1, 1, yU, zL, wU), rnd.Random1(xU, -1, 1, yU, zL, wU), X), Y),
											   smoothInterpolate(smoothInterpolate(rnd.Random1(xL, -1, 1, yL, zU, wU), rnd.Random1(xU, -1, 1, yL, zU, wU), X),
																 smoothInterpolate(rnd.Random1(xL, -1, 1, yU, zU, wU), rnd.Random1(xU, -1, 1, yU, zU, wU), X), Y), Z), W);
}


float UNoise_SuiteBPLibrary::OneD_Value_Noise(float x, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += One_Value(x / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::TwoD_Value_Noise(float x, float y, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += Two_Value(x / scale, y / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::ThreeD_Value_Noise(float x, float y, float z, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += Three_Value(x / scale, y / scale, z / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::FourD_Value_Noise(float x, float y, float z, float w, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
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
		value += Four_Value(x / scale, y / scale, z / scale, w / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}