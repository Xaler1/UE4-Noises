// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Noise_SuiteBPLibrary.generated.h"
/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

UCLASS()
class UNoise_SuiteBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

		/*
			Voronoi Noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D F1 Voronoi noise", Keywords = "1D F1 one Noise_Suite voronoi noise",
			ToolTip = "Sample 1D F1 Voronoi noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Voronoi_Noise")
		static float OneDF1_Voronoi_Noise(float x, float scale = 1, float amplitude = 1, int dimensions = 1, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D F1-F2 Voronoi noise", Keywords = "1D F1 F2 one two Noise_Suite voronoi noise",
			ToolTip = "Sample 1D F1-F2 Voronoi noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Voronoi_Noise")
		static float OneDF1F2_Voronoi_Noise(float x, float scale = 1, float amplitude = 1, int dimensions = 1, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D F2 Voronoi noise", Keywords = "1D F2 one two Noise_Suite voronoi noise",
			ToolTip = "Sample 1D F2 Voronoi noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Voronoi_Noise")
		static float OneDF2_Voronoi_Noise(float x, float scale = 1, float amplitude = 1, int dimensions = 1, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D F1 Voronoi noise", Keywords = "2D F1 one two Noise_Suite voronoi noise",
			ToolTip = "Sample 2D F1 Voronoi noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Voronoi_Noise")
		static float TwoDF1_Voronoi_Noise(float x, float y, float scale = 1, float amplitude = 1, int dimensions = 2, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D F1-F2 Voronoi noise", Keywords = "2D F1 F2 one two Noise_Suite voronoi noise",
			ToolTip = "Sample 2D F1-F2 Voronoi noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Voronoi_Noise")
		static float TwoDF1F2_Voronoi_Noise(float x, float y, float scale = 1, float amplitude = 1, int dimensions = 2, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D F2 Voronoi noise", Keywords = "2D F2 two Noise_Suite voronoi noise",
			ToolTip = "Sample 2D F2 Voronoi noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Voronoi_Noise")
		static float TwoDF2_Voronoi_Noise(float x, float y, float scale = 1, float amplitude = 1, int dimensions = 2, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D F1 Voronoi noise", Keywords = "3D F1 one three Noise_Suite voronoi noise",
			ToolTip = "Sample 3D F1 Voronoi noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Voronoi_Noise")
		static float ThreeDF1_Voronoi_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int dimensions = 3, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D F1-F2 Voronoi noise", Keywords = "3D F1 F2 one two three Noise_Suite voronoi noise",
			ToolTip = "Sample 3D F1-F2 Voronoi noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Voronoi_Noise")
		static float ThreeDF1F2_Voronoi_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int dimensions = 3, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D F2 Voronoi noise", Keywords = "3D F2 two three Noise_Suite voronoi noise",
			ToolTip = "Sample 3D F2 Voronoi noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Voronoi_Noise")
		static float ThreeDF2_Voronoi_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int dimensions = 3, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D F1 Voronoi noise", Keywords = "4D F1 one four Noise_Suite voronoi noise",
			ToolTip = "Sample 4D F1 Voronoi noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Voronoi_Noise")
		static float FourDF1_Voronoi_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int dimensions = 4, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D F1-F2 Voronoi noise", Keywords = "4D F1 F2 one two four Noise_Suite voronoi noise",
			ToolTip = "Sample 4D F1-F2 Voronoi noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Voronoi_Noise")
		static float FourDF1F2_Voronoi_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int dimensions = 4, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D F2 Voronoi noise", Keywords = "4D F2 two four Noise_Suite voronoi noise",
			ToolTip = "Sample 4D F2 Voronoi noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Voronoi_Noise")
		static float FourDF2_Voronoi_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int dimensions = 4, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			Worley Noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D F1 Worley noise", Keywords = "1D F1 one Noise_Suite Worley noise",
			ToolTip = "Sample 1D F1 Worley noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Worley_Noise")
		static float OneDF1_Worley_Noise(float x, float scale = 1, float amplitude = 1, int dimensions = 1, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D F2-F1 Worley noise", Keywords = "1D F1 F2 one two Noise_Suite Worley noise",
			ToolTip = "Sample 1D F2-F1 Worley noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Worley_Noise")
		static float OneDF1F2_Worley_Noise(float x, float scale = 1, float amplitude = 1, int dimensions = 1, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D F2 Worley noise", Keywords = "1D F2 one two Noise_Suite Worley noise",
			ToolTip = "Sample 1D F2 Worley noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Worley_Noise")
		static float OneDF2_Worley_Noise(float x, float scale = 1, float amplitude = 1, int dimensions = 1, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D F1 Worley noise", Keywords = "2D F1 one two Noise_Suite Worley noise",
			ToolTip = "Sample 2D F1 Worley noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Worley_Noise")
		static float TwoDF1_Worley_Noise(float x, float y, float scale = 1, float amplitude = 1, int dimensions = 2, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D F2-F1 Worley noise", Keywords = "2D F1 F2 one two Noise_Suite Worley noise",
			ToolTip = "Sample 2D F2-F1 Worley noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Worley_Noise")
		static float TwoDF1F2_Worley_Noise(float x, float y, float scale = 1, float amplitude = 1, int dimensions = 2, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D F2 Worley noise", Keywords = "2D F2 two Noise_Suite Worley noise",
			ToolTip = "Sample 2D F2 Worley noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Worley_Noise")
		static float TwoDF2_Worley_Noise(float x, float y, float scale = 1, float amplitude = 1, int dimensions = 2, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D F1 Worley noise", Keywords = "3D F1 one three Noise_Suite Worley noise",
			ToolTip = "Sample 3D F1 Worley noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Worley_Noise")
		static float ThreeDF1_Worley_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int dimensions = 3, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D F2-F1 Worley noise", Keywords = "3D F1 F2 one two three Noise_Suite Worley noise",
			ToolTip = "Sample 3D F2-F1 Worley noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Worley_Noise")
		static float ThreeDF1F2_Worley_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int dimensions = 3, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D F2 Worley noise", Keywords = "3D F2 two three Noise_Suite Worley noise",
			ToolTip = "Sample 3D F2 Worley noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Worley_Noise")
		static float ThreeDF2_Worley_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int dimensions = 3, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D F1 Worley noise", Keywords = "4D F1 one four Noise_Suite Worley noise",
			ToolTip = "Sample 4D F1 Worley noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Worley_Noise")
		static float FourDF1_Worley_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int dimensions = 4, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D F2-F1 Worley noise", Keywords = "4D F1 F2 one two four Noise_Suite Worley noise",
			ToolTip = "Sample 4D F2-F1 Worley noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Worley_Noise")
		static float FourDF1F2_Worley_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int dimensions = 4, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D F2 Worley noise", Keywords = "4D F2 two four Noise_Suite Worley noise",
			ToolTip = "Sample 4D F2 Worley noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Worley_Noise")
		static float FourDF2_Worley_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int dimensions = 4, int distance_type = 0, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			Perlin noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Perlin Noise", Keywords = "One 1D Perlin_Noise perlin noise Perlin Noise",
			ToolTip = "Sample 1D perlin noise at the given X coordinate.", AdvancedDisplay = 3), Category = "Perlin_Noise")
		static float OneD_Perlin_Noise(const float x, const float scale = 1, const float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Perlin Noise", Keywords = "Two 2D Perlin_Noise perlin noise Perlin Noise",
			ToolTip = "Sample 2D perlin noise at the given X,Y coordinate.", AdvancedDisplay = 4), Category = "Perlin_Noise")
		static float TwoD_Perlin_Noise(const float x, const float y, const float scale = 1, const float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Perlin Noise", Keywords = "Three 3D Perlin_Noise perlin noise Perlin Noise",
			ToolTip = "Sample 3D perlin noise at the given X,Y,Z coordinate.", AdvancedDisplay = 5), Category = "Perlin_Noise")
		static float ThreeD_Perlin_Noise(const float x, const float y, const float z, const float scale = 1, const float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Perlin Noise", Keywords = "Four 4D Perlin_Noise perlin noise Perlin Noise",
			ToolTip = "Sample 4D perlin noise at the given X,Y,Z,W coordinate.", AdvancedDisplay = 6), Category = "Perlin_Noise")
		static float FourD_Perlin_Noise(const float x, const float y, const float z, const float w, const float scale = 1, const float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			Cubic noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Cubic noise", Keywords = "1D one Noise_Suite Cubic noise"), Category = "Cubic_Noise")
		static float OneD_Cubic_Noise(float x, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Cubic noise", Keywords = "2D two Noise_Suite Cubic noise"), Category = "Cubic_Noise")
		static float TwoD_Cubic_Noise(float x, float y, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Cubic noise", Keywords = "3D three Noise_Suite Cubic noise"), Category = "Cubic_Noise")
		static float ThreeD_Cubic_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Cubic noise", Keywords = "4D four Noise_Suite Cubic noise"), Category = "Cubic_Noise")
		static float FourD_Cubic_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			Value noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Value noise", Keywords = "1D one Noise_Suite Value noise"), Category = "Value_Noise")
		static float OneD_Value_Noise(float x, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Value noise", Keywords = "2D two Noise_Suite Value noise"), Category = "Value_Noise")
		static float TwoD_Value_Noise(float x, float y, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Value noise", Keywords = "3D three Noise_Suite Value noise"), Category = "Value_Noise")
		static float ThreeD_Value_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Value noise", Keywords = "4D four Noise_Suite Value noise"), Category = "Value_Noise")
		static float FourD_Value_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			Spot noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Spot noise", Keywords = "1D one Noise_Suite Spot noise"), Category = "Spot_Noise")
		static float OneD_Spot_Noise(float x, float scale = 1, float amplitude = 1, float frequency = 0.5, float min = 0.5, float max = 0.5, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Spot noise", Keywords = "2D two Noise_Suite Spot noise"), Category = "Spot_Noise")
		static float TwoD_Spot_Noise(float x, float y, float scale = 1, float amplitude = 1, float frequency = 0.5, float min = 0.5, float max = 0.5, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Spot noise", Keywords = "3D three Noise_Suite Spot noise"), Category = "Spot_Noise")
		static float ThreeD_Spot_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, float frequency = 0.5, float min = 0.5, float max = 0.5, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Spot noise", Keywords = "4D four Noise_Suite Spot noise"), Category = "Spot_Noise")
		static float FourD_Spot_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, float frequency = 0.5, float min = 0.5, float max = 0.5, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			OpenSimplex noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D OpenSimplex noise", Keywords = "1D one Noise_Suite simplex open noise"), Category = "OpenSimplex_Noise")
		static float OneD_Simplex_Noise(float x, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D OpenSimplex noise", Keywords = "2D two Noise_Suite simplex open noise"), Category = "OpenSimplex_Noise")
		static float TwoD_Simplex_Noise(float x, float y, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D OpenSimplex noise", Keywords = "3D three Noise_Suite simplex open noise"), Category = "OpenSimplex_Noise")
		static float ThreeD_Simplex_Noise(float x, float y, float z, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);
	
		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D OpenSimplex noise", Keywords = "4D four Noise_Suite simplex open noise"), Category = "OpenSimplex_Noise")
		static float FourD_Simplex_Noise(float x, float y, float z, float w, float scale = 1, float amplitude = 1, int fractal_level = 1, float scale_fade = 0.5, float amp_fade = 0.5);

		/*
			Gaussian noise
		*/

		UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Gaussian noise", Keywords = "1D one Suite gaussian noise"), Category = "Gaussian_Noise")
		static float OneD_Gaussian_Noise(float x, float amplitude = 1, float standard_deviation = 1);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Gaussian noise", Keywords = "1D two Suite gaussian noise"), Category = "Gaussian_Noise")
		static float TwoD_Gaussian_Noise(float x, float y, float amplitude = 1, float standard_deviation = 1);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Gaussian noise", Keywords = "3D three Suite gaussian noise"), Category = "Gaussian_Noise")
		static float ThreeD_Gaussian_Noise(float x, float y, float z, float amplitude = 1, float standard_deviation = 1);

		UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Gaussian noise", Keywords = "4D four Suite gaussian noise"), Category = "Gaussian_Noise")
		static float FourD_Gaussian_Noise(float x, float y, float z, float w, float amplitude = 1, float standard_deviation = 1);

		/*
			Noise set seed
		*/

		UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Noise seed", Keywords = "set noise seed suite"), Category = "Noise_Seed")
		static void SetNoiseSeed(float seed);

		/*
			Useful functions for myself
		*/

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), coefs[0]));
};
