// Fill out your copyright notice in the Description page of Project Settings.


#include "Noise_Suite.h"
#include "Noise_SuiteBPLibrary.h"
#include "Randomiser.h"
#include "time.h"
float coefs[11];

Randomiser::Randomiser()
{
	srand(time(NULL));
	for (int i = 0; i < 11; i++) {
		coefs[i] = rand() * 1000;
	}
}

Randomiser::~Randomiser()
{
}


FVector4 Randomiser::Random4(int X, int Y, int Z, int W, float min, float max) {
	float seed = coefs[0] * sin(coefs[1] * X + coefs[2] * Y + coefs[3] * Z + coefs[4] * W + coefs[5]) * cos(coefs[6] * X + coefs[7] * Y + coefs[8] * Z + coefs[9] * W + coefs[10]);
	srand(seed);
	float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	float w = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	FVector4 random_vector = FVector4(x, y, z, w);
	return random_vector / random_vector.Size();
}

FVector Randomiser::Random3(int X, int Y, int Z, float min, float max) {
	float seed = coefs[0] * sin(coefs[1] * X + coefs[2] * Y + coefs[3] * Z + coefs[5]) * cos(coefs[6] * X + coefs[7] * Y + coefs[8] * Z + coefs[10]);
	srand(seed);
	float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	float z = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	FVector random_vector = FVector(x, y, z);
	return random_vector / random_vector.Size();
}

FVector2D Randomiser::Random2(int X, int Y, float min, float max) {
	float seed = coefs[0] * sin(coefs[1] * X + coefs[2] * Y + coefs[5]) * cos(coefs[6] * X + coefs[7] * Y + coefs[10]);
	srand(seed);
	float x = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	float y = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
	FVector2D random_vector = FVector2D(x, y);
	return random_vector / random_vector.Size();
}

float Randomiser::Random1(int X, float min, float max, int Y, int Z, int W) {
	float seed = coefs[0] * sin(coefs[1] * X + coefs[2] * Y + coefs[3] * Z + coefs[4] * W + coefs[5]) * cos(coefs[6] * X + coefs[7] * Y + coefs[8] * Z + coefs[9] * W + coefs[10]);
	srand(seed);
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min))) + min;
}

void UNoise_SuiteBPLibrary::SetNoiseSeed(float seed) {
	srand(seed);
	for (int i = 0; i < 11; i++) {
		coefs[i] = rand() * 1000;
	}
}