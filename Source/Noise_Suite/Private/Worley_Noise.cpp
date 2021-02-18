// Fill out your copyright notice in the Description page of Project Settings.


#include "Worley_Noise.h"
#include "time.h"
#include "math.h"
#include "Randomiser.h"
#include "stdlib.h"
#include "Noise_SuiteBPLibrary.h"


Worley_Noise::Worley_Noise()
{
}

Worley_Noise::~Worley_Noise()
{
}


extern Randomiser rnd;
extern float distances[81];

static int Wcompare(const void* a, const void* b) {
	const float* x = (float*)a;
	const float* y = (float*)b;

	if (*x > *y)
		return 1;
	else if (*x < *y)
		return -1;
	return 0;
}

/*
	Generic Worley Noise
*/

float F1_Worley_Noise(float x, int dimensions, int distance_type, float y = 0, float z = 0, float w = 0) {
	if (dimensions < 1) {
		dimensions = 1;
	}
	else if (dimensions > 4) {
		dimensions = 4;
	}

	int Y_factor = 1;
	int Z_factor = floor(dimensions / 3.0);
	int W_factor = floor(dimensions / 4.0);
	if (dimensions == 1) {
		Y_factor = 0;
	}

	int xL = floor(x) - 1;
	int yL = floor(y) * Y_factor - 1 * Y_factor;
	int zL = floor(z) * Z_factor - 1 * Z_factor;
	int wL = floor(w) * W_factor - 1 * W_factor;
	int xU = xL + 2;
	int yU = yL + 2 * Y_factor;
	int zU = zL + 2 * Z_factor;
	int wU = wL + 2 * W_factor;

	float min_dist = 10000000;
	float distance;
	for (int W = wL; W <= wU; W++) {
		for (int Z = zL; Z <= zU; Z++) {
			for (int Y = yL; Y <= yU; Y++) {
				for (int X = xL; X <= xU; X++) {
					FVector4 rnd_point = rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W);
					rnd_point.Y *= Y_factor;
					rnd_point.Z *= Z_factor;
					rnd_point.W *= W_factor;
					if (distance_type == 0) {
						distance = (rnd_point - FVector4(x, y, z, w)).Size();
					}
					else {
						FVector4 distance_vec = rnd_point - FVector4(x, y, z, w);
						distance =  abs(distance_vec.X) + abs(distance_vec.Y) + abs(distance_vec.Z) + abs(distance_vec.W);
					}
					if (distance < min_dist) {
						min_dist = distance;
					}
				}
			}
		}
	}
	if (distance_type == 0) {
		return (min_dist * (2/sqrt(dimensions)) - 1);
	}
	else {
		return (min_dist * (2/dimensions) - 1);
	}
	
}

float F1F2_Worley_Noise(float x, int dimensions, int distance_type, float y = 0, float z = 0, float w = 0) {
	if (dimensions < 1) {
		dimensions = 1;
	}
	else if (dimensions > 4) {
		dimensions = 4;
	}

	int Y_factor = 1;
	int Z_factor = floor(dimensions / 3.0);
	int W_factor = floor(dimensions / 4.0);
	if (dimensions == 1) {
		Y_factor = 0;
	}

	int xL = floor(x) - 1;
	int yL = floor(y) * Y_factor - 1 * Y_factor;
	int zL = floor(z) * Z_factor - 1 * Z_factor;
	int wL = floor(w) * W_factor - 1 * W_factor;
	int xU = xL + 2;
	int yU = yL + 2 * Y_factor;
	int zU = zL + 2 * Z_factor;
	int wU = wL + 2 * W_factor;

	std::fill_n(distances, 81, 1000);
	int size = (xU - xL + 1) * (yU - yL + 1) * (zU - zL + 1) * (wU - wL + 1);
	int current_point = 0;
	for (int W = wL; W <= wU; W++) {
		for (int Z = zL; Z <= zU; Z++) {
			for (int Y = yL; Y <= yU; Y++) {
				for (int X = xL; X <= xU; X++) {
					FVector4 rnd_point = rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W);
					rnd_point.Y *= Y_factor;
					rnd_point.Z *= Z_factor;
					rnd_point.W *= W_factor;
					if (distance_type == 0) {
						distances[current_point] = (rnd_point - FVector4(x, y, z, w)).Size();
					}
					else {
						FVector4 distance_vec = rnd_point - FVector4(x, y, z, w);
						distances[current_point] = abs(distance_vec.X) + abs(distance_vec.Y) + abs(distance_vec.Z) + abs(distance_vec.W);
					}
					current_point++;
				}
			}
		}
	}

	qsort(distances, 81, sizeof(float), Wcompare);

	if (distance_type == 0) {
		return ((distances[1] - distances[0]) * (4.0 / 3.0 / sqrt(dimensions)) - 1);
	}
	else {
		return ((distances[1] - distances[0]) * (4.0 / 3.0 / dimensions) - 1);
	}
	
}

float F2_Worley_Noise(float x, int dimensions, int distance_type, float y = 0, float z = 0, float w = 0) {
	if (dimensions < 1) {
		dimensions = 1;
	}
	else if (dimensions > 4) {
		dimensions = 4;
	}

	int Y_factor = 1;
	int Z_factor = floor(dimensions / 3.0);
	int W_factor = floor(dimensions / 4.0);
	if (dimensions == 1) {
		Y_factor = 0;
	}

	int xL = floor(x) - 1;
	int yL = floor(y) * Y_factor - 1 * Y_factor;
	int zL = floor(z) * Z_factor - 1 * Z_factor;
	int wL = floor(w) * W_factor - 1 * W_factor;
	int xU = xL + 2;
	int yU = yL + 2 * Y_factor;
	int zU = zL + 2 * Z_factor;
	int wU = wL + 2 * W_factor;

	std::fill_n(distances, 81, 1000);
	int size = (xU - xL + 1) * (yU - yL + 1) * (zU - zL + 1) * (wU - wL + 1);
	int current_point = 0;
	for (int W = wL; W <= wU; W++) {
		for (int Z = zL; Z <= zU; Z++) {
			for (int Y = yL; Y <= yU; Y++) {
				for (int X = xL; X <= xU; X++) {
					FVector4 rnd_point = rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W);
					rnd_point.Y *= Y_factor;
					rnd_point.Z *= Z_factor;
					rnd_point.W *= W_factor;
					if (distance_type == 0) {
						distances[current_point] = (rnd_point - FVector4(x, y, z, w)).Size();
					}
					else {
						FVector4 distance_vec = (rnd_point - FVector4(x, y, z, w));
						distances[current_point] = abs(distance_vec.X) + abs(distance_vec.Y) + abs(distance_vec.Z) + abs(distance_vec.W);
					}
					current_point++;
				}
			}
		}
	}

	qsort(distances, 81, sizeof(float), Wcompare);
	if (distance_type == 0) {
		return (distances[1] * (4.0 / 3.0 / sqrt(dimensions)) - 1);
	}
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), distances[1] * (4.0f / 3.0f / dimensions) - 1));
		return (distances[1] * (4.0f / 3.0f / dimensions) - 1) ;
	}
	
}


extern float getNoise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade, float(*function)(float, int, int, float, float, float));


/*
	1D Worley Noise
*/


float UNoise_SuiteBPLibrary::OneDF1_Worley_Noise(float x, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, 0, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Worley_Noise);
}

float UNoise_SuiteBPLibrary::OneDF1F2_Worley_Noise(float x, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, 0, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Worley_Noise);
}

float UNoise_SuiteBPLibrary::OneDF2_Worley_Noise(float x, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, 0, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Worley_Noise);
}


/*
	2D Worley Noise
*/


float UNoise_SuiteBPLibrary::TwoDF1_Worley_Noise(float x, float y, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, 0 , 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Worley_Noise);
}

float UNoise_SuiteBPLibrary::TwoDF1F2_Worley_Noise(float x, float y, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Worley_Noise);
}

float UNoise_SuiteBPLibrary::TwoDF2_Worley_Noise(float x, float y, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Worley_Noise);
}


/*
	3D Worley Noise
*/


float UNoise_SuiteBPLibrary::ThreeDF1_Worley_Noise(float x, float y, float z, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Worley_Noise);
}

float UNoise_SuiteBPLibrary::ThreeDF1F2_Worley_Noise(float x, float y, float z, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Worley_Noise);
}

float UNoise_SuiteBPLibrary::ThreeDF2_Worley_Noise(float x, float y, float z, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Worley_Noise);
}


/*
	4D Worley Noise
*/


float UNoise_SuiteBPLibrary::FourDF1_Worley_Noise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, w, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Worley_Noise);
}

float UNoise_SuiteBPLibrary::FourDF1F2_Worley_Noise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, w, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Worley_Noise);
}

float UNoise_SuiteBPLibrary::FourDF2_Worley_Noise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, w, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Worley_Noise);
}

