// Fill out your copyright notice in the Description page of Project Settings.


#include "Noise_Utils.h"
#include "Randomiser.h"

extern Randomiser rnd;

float smoothInterpolate(float a, float b, float x) {
	float t = x * PI;
	float f = (1 - cos(t)) * 0.5;
	return a * (1 - f) + b * f;
}