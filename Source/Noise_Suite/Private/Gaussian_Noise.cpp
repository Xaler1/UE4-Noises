// Fill out your copyright notice in the Description page of Project Settings.


#include "Gaussian_Noise.h"
#include "Noise_Utils.h"
#include "Noise_SuiteBPLibrary.h"
#include "Randomiser.h"

extern Randomiser rnd;

float Gaussian(float x, float dev) {
	return 1.0 / (dev * sqrt(2 * PI)) * exp(-1 * pow(x, 2) / (2 * pow(dev, 2)));
}

float UNoise_SuiteBPLibrary::OneD_Gaussian_Noise(float x, float amplitude, float standard_deviation) {
	return Gaussian(rnd.Random1(x, -1, 1), standard_deviation) * amplitude;
}

float UNoise_SuiteBPLibrary::TwoD_Gaussian_Noise(float x, float y, float amplitude, float standard_deviation) {
	return Gaussian(rnd.Random1(x, -1, 1, y), standard_deviation) * amplitude;
}

float UNoise_SuiteBPLibrary::ThreeD_Gaussian_Noise(float x, float y, float z, float amplitude, float standard_deviation) {
	return Gaussian(rnd.Random1(x, -1, 1, y, z), standard_deviation) * amplitude;
}

float UNoise_SuiteBPLibrary::FourD_Gaussian_Noise(float x, float y, float z, float w, float amplitude, float standard_deviation) {
	return Gaussian(rnd.Random1(x, -1, 1, y, z, w), standard_deviation) * amplitude;
}

