// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;
class UTurret;

// Holds barrel's properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector, float);
	void SetBarrelReference(UTankBarrel *);
	void SetTurretReference(UTurret *);

private:
	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector);
};