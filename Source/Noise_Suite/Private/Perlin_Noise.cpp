// Fill out your copyright notice in the Description page of Project Settings.

#include "Noise_SuiteBPLibrary.h"
#include "time.h"
#include "math.h"
#include "Randomiser.h"
#include "Perlin_Noise.h"
#include "Noise_Utils.h"

Perlin_Noise::Perlin_Noise()
{
}

Perlin_Noise::~Perlin_Noise()
{
}

extern Randomiser rnd;

float Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float dotGradient(int dimensions, int X, float x, int Y = 0, float y = 0, int Z = 0, float z = 0, int W = 0, float w = 0) {
	FVector4 random_vector = rnd.Random4(X, Y, Z, W, -1, 1);
	float dx = x - X;
	float dy = y - Y;
	float dz = z - Z;
	float dw = w - W;
	FVector4 point = FVector4(dx, dy, dz, dw);
	return point.X * random_vector.X + point.Y * random_vector.Y + point.Z * random_vector.Z + point.W * random_vector.W;
}

float OneD_Perlin(float x) {
	int xL = floor(x);
	int xU = xL + 1;

	float dx = x - xL;
	return smoothInterpolate(dotGradient(1, xL, x), dotGradient(1, xU, x), dx);
}

float TwoD_Perlin(float x, float y) {
	int xL = floor(x);
	int xU = xL + 1;
	int yL = floor(y);
	int yU = yL + 1;

	float dx = x - xL;
	float dy = y - yL;

	return smoothInterpolate(smoothInterpolate(dotGradient(2, xL, x, yL, y), dotGradient(2, xU, x, yL, y), dx),
		smoothInterpolate(dotGradient(2, xL, x, yU, y), dotGradient(2, xU, x, yU, y), dx), dy);
}

float ThreeD_Perlin(float x, float y, float z) {
	int xL = floor(x);
	int xU = xL + 1;
	int yL = floor(y);
	int yU = yL + 1;
	int zL = floor(z);
	int zU = zL + 1;

	float dx = x - xL;
	float dy = y - yL;
	float dz = z - zL;

	return smoothInterpolate(smoothInterpolate(smoothInterpolate(dotGradient(3, xL, x, yL, y, zL, z), dotGradient(3, xU, x, yL, y, zL, z), dx),
		smoothInterpolate(dotGradient(3, xL, x, yU, y, zL, z), dotGradient(3, xU, x, yU, y, zL, z), dx), dy),
		smoothInterpolate(smoothInterpolate(dotGradient(3, xL, x, yL, y, zU, z), dotGradient(3, xU, x, yL, y, zU, z), dx),
			smoothInterpolate(dotGradient(3, xL, x, yU, y, zU, z), dotGradient(3, xU, x, yU, y, zU, z), dx), dy), dz);
}

float FourD_Perlin(float x, float y, float z, float w) {
	int xL = floor(x);
	int xU = xL + 1;
	int yL = floor(y);
	int yU = yL + 1;
	int zL = floor(z);
	int zU = zL + 1;
	int wL = floor(w);
	int wU = wL + 1;

	float dx = x - xL;
	float dy = y - yL;
	float dz = z - zL;
	float dw = w - wL;

	return smoothInterpolate(smoothInterpolate(smoothInterpolate(smoothInterpolate(dotGradient(4, xL, x, yL, y, zL, z, wL, w), dotGradient(4, xU, x, yL, y, zL, z, wL, w), dx),
		smoothInterpolate(dotGradient(4, xL, x, yU, y, zL, z, wL, w), dotGradient(4, xU, x, yU, y, zL, z, wL, w), dx), dy),
		smoothInterpolate(smoothInterpolate(dotGradient(4, xL, x, yL, y, zU, z, wL, w), dotGradient(4, xU, x, yL, y, zU, z, wL, w), dx),
			smoothInterpolate(dotGradient(4, xL, x, yU, y, zU, z, wL, w), dotGradient(4, xU, x, yU, y, zU, z, wL, w), dx), dy), dz),
		smoothInterpolate(smoothInterpolate(smoothInterpolate(dotGradient(4, xL, x, yL, y, zL, z, wU, w), dotGradient(4, xU, x, yL, y, zL, z, wU, w), dx),
			smoothInterpolate(dotGradient(4, xL, x, yU, y, zL, z, wU, w), dotGradient(4, xU, x, yU, y, zL, z, wU, w), dx), dy),
			smoothInterpolate(smoothInterpolate(dotGradient(4, xL, x, yL, y, zU, z, wU, w), dotGradient(4, xU, x, yL, y, zU, z, wU, w), dx),
				smoothInterpolate(dotGradient(4, xL, x, yU, y, zU, z, wU, w), dotGradient(4, xU, x, yU, y, zU, z, wU, w), dx), dy), dz), dw);
}




float UNoise_SuiteBPLibrary::OneD_Perlin_Noise(float x, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	float total_amp = 0;
	float sim_amp = 1;
	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += OneD_Perlin(x / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value * 2.5;
}

float UNoise_SuiteBPLibrary::TwoD_Perlin_Noise(float x, float y, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	float total_amp = 0;
	float sim_amp = 1;
	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += TwoD_Perlin(x / scale, y / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%d"), value));
	return value * 2.5;
}

float UNoise_SuiteBPLibrary::ThreeD_Perlin_Noise(float x, float y, float z, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	float total_amp = 0;
	float sim_amp = 1;
	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += ThreeD_Perlin(x / scale, y / scale, z / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value * 2.5;
}

float UNoise_SuiteBPLibrary::FourD_Perlin_Noise(float x, float y, float z, float w, float scale, float amplitude, int fractal_level, float scale_fade, float amp_fade) {
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	float total_amp = 0;
	float sim_amp = 1;
	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += FourD_Perlin(x / scale, y / scale, z / scale, w / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value * 2.5;
}

FVector4 normaliseToDimensions(FVector4 vector, int dimensions) {
	vector.Z = vector.Z * floor(dimensions / 3.0);
	vector.W = vector.W * floor(dimensions / 4.0);
	if (dimensions < 2) {
		vector.Y = 0;
	}
	if (vector.Size() == 0) {
		return vector;
	}
	return vector * (1.0 / vector.Size());
}
