// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Turret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
{
	if (!ensure(Barrel))
	{
		return;
	}
	FVector outLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		outLaunchVelocity,
		StartLocation,
		hitLocation,
		LaunchSpeed,
		false, 0, 0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if (ensure(bHaveAimSolution))
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::Initialise(UTankBarrel *barrelToSet, UTurret *turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!(ensure(Barrel) && ensure(Turret)))
	{
		return;
	}
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->Rotate(deltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint))
	{
		return;
	}

	if ((GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeSeconds))
	{
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}
