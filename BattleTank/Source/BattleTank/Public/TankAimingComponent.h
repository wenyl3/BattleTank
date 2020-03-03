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
	LOCKED,
	OUT_OF_AMMO
};

// Forward declaration
class UTankBarrel;
class UTurret;
class AProjectile;

// Holds barrel's properties
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel *barrelToSet, UTurret *turretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;

	void AimAt(FVector);
	EFiringState GetFiringState() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::RELOADING;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UTankBarrel *Barrel = nullptr;
	UTurret *Turret = nullptr;
	double LastFireTime = 0;
	FVector aimDirection;
	int RoundsLeft = 3;

	// Sets default values for this component's properties
	UTankAimingComponent();
	void MoveBarrelTowards(FVector);
	virtual void BeginPlay() override;
	virtual void TickComponent(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction *ThisTickFunction) override;
	bool IsBarrelMoving();
};
