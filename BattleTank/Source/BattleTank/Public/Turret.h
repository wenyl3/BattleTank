// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * Class used to control the rotation of the turret.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Rotate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float maxDegreesPerSecond = 20.0;
};
