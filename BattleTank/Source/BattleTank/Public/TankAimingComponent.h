// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	RELOADING,
	AIMING,
	LOCKED
};

// Forward declaration
class UTankBarrel;
class UTurret;

// Holds barrel's properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel *barrelToSet, UTurret *turretToSet);

	void AimAt(FVector, float);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::RELOADING;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();
	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;

	void MoveBarrelTowards(FVector);
};
