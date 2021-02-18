// Fill out your copyright notice in the Description page of Project Settings.


#include "Spot_Noise.h"
#include "Randomiser.h"
#include "math.h"
#include "Noise_SuiteBPLibrary.h"

extern Randomiser rnd;

float One_Spot(float x, float threshold, float min, float max) {
	for (int xR = floor(x) - 1; xR <= floor(x) + 2; xR++) {
		float value = rnd.Random1(xR, 0, 1);
		FVector2D offset = rnd.Random1(xR, -1, 1);
		float distance = abs(x - (xR + offset.X));
		if (value > threshold) {
			float scaled_remainder = (value - threshold) / (1 - threshold);
			float radius = min + (max - min) * scaled_remainder;
			if (distance < radius) {
				return 1;
			}
		}
	}
	return -1;
}

float Two_Spot(float x, float y, float threshold, float min, float max) {
	for (int yR = floor(y) - 1; yR <= floor(y) + 2; yR++) {
		for (int xR = floor(x) - 1; xR <= floor(x) + 2; xR++) {
			float value = rnd.Random1(xR, 0, 1, yR);
			FVector2D offset = rnd.Random2(xR, yR, -1, 1);
			float distance = sqrt(pow(abs(x - (xR + offset.X)), 2) + pow(abs(y - (yR + offset.Y)), 2));
			if (value > threshold) {
				float scaled_remainder = (value - threshold) / (1 - threshold);
				float radius = min + (max - min) * scaled_remainder;
				if (distance < radius) {
					return 1;
				}
			}
		}
	}
	return -1;
}

float Three_Spot(float x, float y, float z, float threshold, float min, float max) {
	for (int zR = floor(z) - 1; zR <= floor(z) + 2; zR++) {
		for (int yR = floor(y) - 1; yR <= floor(y) + 2; yR++) {
			for (int xR = floor(x) - 1; xR <= floor(x) + 2; xR++) {
				float value = rnd.Random1(xR, 0, 1, yR, zR);
				FVector offset = rnd.Random3(xR, yR, zR, -1, 1);
				float distance = sqrt(pow(abs(x - (xR + offset.X)), 2) + pow(abs(y - (yR + offset.Y)), 2) + pow(abs(z - (zR + offset.Z)), 2));
				if (value > threshold) {
					float scaled_remainder = (value - threshold) / (1 - threshold);
					float radius = min + (max - min) * scaled_remainder;
					if (distance < radius) {
						return 1;
					}
				}
			}
		}
	}
	return -1;
}

float Four_Spot(float x, float y, float z, float w, float threshold, float min, float max) {
	for (int wR = floor(w) - 1; wR <= floor(w) + 2; wR++) {
		for (int zR = floor(z) - 1; zR <= floor(z) + 2; zR++) {
			for (int yR = floor(y) - 1; yR <= floor(y) + 2; yR++) {
				for (int xR = floor(x) - 1; xR <= floor(x) + 2; xR++) {
					float value = rnd.Random1(xR, 0, 1, yR, zR, wR);
					FVector4 offset = rnd.Random4(xR, yR, zR, wR, -1, 1);
					float distance = sqrt(pow(abs(x - (xR + offset.X)), 2) + pow(abs(y - (yR + offset.Y)), 2) + pow(abs(z - (zR + offset.Z)), 2) + pow(abs(w - (wR + offset.W)), 2));
					if (value > threshold) {
						float scaled_remainder = (value - threshold) / (1 - threshold);
						float radius = min + (max - min) * scaled_remainder;
						if (distance < radius) {
							return 1;
						}
					}
				}
			}
		}
	}
	return -1;
}



float UNoise_SuiteBPLibrary::OneD_Spot_Noise(float x, float scale, float amplitude, float frequency, float min, float max, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	frequency = (frequency <= 1) ? frequency : 1;
	frequency = (frequency >= 0) ? frequency : 0;
	min = (min <= 2) ? min * 2 : 2;
	min = (min >= 0) ? min : 0;
	max = (max <= 2) ? max * 2 : 2;
	max = (max >= 0) ? max : 0;
	min = (min <= max) ? min : max;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += One_Spot(x / scale, 1 - frequency, min, max) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::TwoD_Spot_Noise(float x, float y, float scale, float amplitude, float frequency, float min, float max, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	frequency = (frequency <= 1) ? frequency : 1;
	frequency = (frequency >= 0) ? frequency : 0;
	min = (min <= 2) ? min * 2 : 2;
	min = (min >= 0) ? min : 0;
	max = (max <= 2) ? max * 2 : 2;
	max = (max >= 0) ? max : 0;
	min = (min <= max) ? min : max;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Two_Spot(x / scale, y / scale, 1 - frequency, min, max) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::ThreeD_Spot_Noise(float x, float y, float z, float scale, float amplitude, float frequency, float min, float max, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	frequency = (frequency <= 1) ? frequency : 1;
	frequency = (frequency >= 0) ? frequency : 0;
	min = (min <= 2) ? min * 2 : 2;
	min = (min >= 0) ? min : 0;
	max = (max <= 2) ? max * 2 : 2;
	max = (max >= 0) ? max : 0;
	min = (min <= max) ? min : max;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Three_Spot(x / scale, y / scale, z / scale, 1 - frequency, min, max) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

float UNoise_SuiteBPLibrary::FourD_Spot_Noise(float x, float y, float z, float w, float scale, float amplitude, float frequency, float min, float max, int fractal_level, float scale_fade, float amp_fade) {
	float total_amp = 0;
	float sim_amp = 1;
	scale = (scale != 0) ? scale : 1;
	fractal_level = (fractal_level >= 1) ? fractal_level : 1;
	frequency = (frequency <= 1) ? frequency : 1;
	frequency = (frequency >= 0) ? frequency : 0;
	min = (min <= 2) ? min * 2 : 2;
	min = (min >= 0) ? min : 0;
	max = (max <= 2) ? max * 2 : 2;
	max = (max >= 0) ? max : 0;
	min = (min <= max) ? min : max;

	for (int i = 1; i <= fractal_level; i++) {
		total_amp += sim_amp;
		sim_amp *= amp_fade;
	}
	amplitude /= total_amp;
	float value = 0;
	for (int i = 1; i <= fractal_level; i++) {
		value += Four_Spot(x / scale, y / scale, z / scale, w / scale, 1 - frequency, min, max) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}
