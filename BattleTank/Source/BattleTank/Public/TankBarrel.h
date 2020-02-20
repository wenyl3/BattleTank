// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDegreesPerSecond = 10.0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxElevationDegrees = 25.0;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float minElevationDegrees = -3.0;
};
