// Fill out your copyright notice in the Description page of Project Settings.


#include "Noise_SuiteBPLibrary.h"
#include "time.h"
#include "math.h"
#include "Randomiser.h"
#include "stdlib.h"
#include "Voronoi_Noise.h"




Voronoi_Noise::Voronoi_Noise() {
}

Voronoi_Noise::~Voronoi_Noise() {
}

/*
	Generic Voronoi Noise
*/

extern Randomiser rnd;
float point_values[81];
float distances[81];
float result[81];
void sortPoints();

static int Vcompare(const void * a, const void * b) {
	double diff = distances[*(int*)a] - distances[*(int*)b];
	return  (0 < diff) - (diff < 0);
}

float F1_Voronoi_Noise(float x, int dimensions, int distance_type, float y = 0, float z = 0, float w = 0) {
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
	float value = 0;
	float distance;
	FVector4 distance_vec;
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
						distance_vec = (rnd_point - FVector4(x, y, z, w));
						GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), distance_vec.X));
						distance = abs(distance_vec.X) + abs(distance_vec.Y) + abs(distance_vec.Z) + abs(distance_vec.W);
					}
					if (distance < min_dist) {
						value = rnd.Random1(X, -1, 1, Y, Z, W);
						min_dist = (rnd_point - FVector4(x, y, z, w)).Size();
					}
				}
			}
		}
	}
	return value;
}

float F1F2_Voronoi_Noise(float x, int dimensions, int distance_type, float y = 0, float z = 0, float w = 0) {
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

	std::fill_n(point_values, 81, 0);
	std::fill_n(distances, 81, 1000);
	int size = (xU - xL + 1) * (yU - yL + 1) * (zU - zL + 1) * (wU - wL + 1);
	int current_point = 0;
	for (int W = wL; W <= wU; W++) {
		for (int Z = zL; Z <= zU; Z++) {
			for (int Y = yL; Y <= yU; Y++) {
				for (int X = xL; X <= xU; X++) {
					if (distance_type == 0) {
						distances[current_point] = (rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W) - FVector4(x, y, z, w)).Size();
					}
					else {
						FVector4 distance_vec = (rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W) - FVector4(x, y, z, w));
						distances[current_point] = abs(distance_vec.X) + abs(distance_vec.Y) + abs(distance_vec.Z) + abs(distance_vec.W);
					}
					point_values[current_point] = rnd.Random1(X, 0, 1, Y, Z, W);
					current_point++;
				}
			}
		}
	}

	sortPoints();

	return (result[0] - result[1]);
}

float F2_Voronoi_Noise(float x, int dimensions, int distance_type, float y = 0, float z = 0, float w = 0) {
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

	std::fill_n(point_values, 81, 0);
	std::fill_n(distances, 81, 1000);
	int size = (xU - xL + 1) * (yU - yL + 1) * (zU - zL + 1) * (wU - wL + 1);
	int current_point = 0;
	for (int W = wL; W <= wU; W++) {
		for (int Z = zL; Z <= zU; Z++) {
			for (int Y = yL; Y <= yU; Y++) {
				for (int X = xL; X <= xU; X++) {
					if (distance_type == 0) {
						distances[current_point] = (rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W) - FVector4(x, y, z, w)).Size();
					}
					else {
						FVector4 distance_vec = (rnd.Random4(X, Y, Z, W, 0, 1) + FVector4(X, Y, Z, W) - FVector4(x, y, z, w));
						distances[current_point] = abs(distance_vec.X) + abs(distance_vec.Y) + abs(distance_vec.Z) + abs(distance_vec.W);
					}
					point_values[current_point] = rnd.Random1(X, -1, 1, Y, Z, W);
					current_point++;
				}
			}
		}
	}

	sortPoints();

	return result[1];
}

void sortPoints() {
	int perm[81], i;
	for (i = 0; i < 81; i++) {
		perm[i] = i;
	}
	qsort(perm, 81, sizeof(int), Vcompare);
	for (i = 0; i < 81; i++) {
		result[i] = point_values[perm[i]];
	}
}

float getNoise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade, float(*function)(float, int, int, float, float, float)) {
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
		value += function(x / scale, dimensions, distance_type, y / scale, z / scale, w / scale) * amplitude;
		scale *= scale_fade;
		amplitude *= amp_fade;
	}
	return value;
}

/*
	1D Voronoi Noise
*/


float UNoise_SuiteBPLibrary::OneDF1_Voronoi_Noise(float x, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, 0, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::OneDF1F2_Voronoi_Noise(float x, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, 0, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::OneDF2_Voronoi_Noise(float x, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, 0, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Voronoi_Noise);
}


/*
	2D Voronoi Noise
*/


float UNoise_SuiteBPLibrary::TwoDF1_Voronoi_Noise(float x, float y, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::TwoDF1F2_Voronoi_Noise(float x, float y, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::TwoDF2_Voronoi_Noise(float x, float y, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, 0, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Voronoi_Noise);
}


/*
	3D Voronoi Noise
*/


float UNoise_SuiteBPLibrary::ThreeDF1_Voronoi_Noise(float x, float y, float z, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::ThreeDF1F2_Voronoi_Noise(float x, float y, float z, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::ThreeDF2_Voronoi_Noise(float x, float y, float z, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, 0, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Voronoi_Noise);
}


/*
	4D Voronoi Noise
*/


float UNoise_SuiteBPLibrary::FourDF1_Voronoi_Noise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, w, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::FourDF1F2_Voronoi_Noise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, w, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F1F2_Voronoi_Noise);
}

float UNoise_SuiteBPLibrary::FourDF2_Voronoi_Noise(float x, float y, float z, float w, float scale, float amplitude, int dimensions, int distance_type, int fractal_level, float scale_fade, float amp_fade) {
	return getNoise(x, y, z, w, scale, amplitude, dimensions, distance_type, fractal_level, scale_fade, amp_fade, &F2_Voronoi_Noise);
}

