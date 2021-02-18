// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class NOISE_SUITE_API Randomiser
{
public:
	Randomiser();
	~Randomiser();
	FVector4 Random4(int X, int Y, int Z, int W, float min, float max);
	FVector Random3(int X, int Y, int Z, float min, float max);
	FVector2D Random2(int X, int Y, float min, float max);
	float Random1(int X, float min, float max, int Y = 1, int Z = 1, int W = 1);
};
