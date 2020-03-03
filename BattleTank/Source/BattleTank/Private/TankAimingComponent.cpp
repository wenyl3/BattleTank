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
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::Initialise(UTankBarrel *barrelToSet, UTurret *turretToSet)
{
	Barrel = barrelToSet;
	Turret = turretToSet;
}

void UTankAimingComponent::TickComponent(
	float DeltaTime,
	enum ELevelTick TickType,
	FActorComponentTickFunction *ThisTickFunction)
{
	if (RoundsLeft <= 0)
	{
		FiringState = EFiringState::OUT_OF_AMMO;
	}
	else if ((GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTimeSeconds))
	{
		FiringState = EFiringState::RELOADING;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::AIMING;
	}
	else
	{
		FiringState = EFiringState::LOCKED;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}
	auto barrelForward = Barrel->GetForwardVector();
	return !barrelForward.Equals(aimDirection, 0.01);
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
	if (bHaveAimSolution)
	{
		aimDirection = outLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
	{
		return;
	}
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	if (FMath::Abs(deltaRotator.Yaw) < 180)
	{
		Turret->Rotate(deltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-deltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::LOCKED || FiringState == EFiringState::AIMING)
	{
		if (!ensure(Barrel))
		{
			return;
		}
		if (!ensure(ProjectileBlueprint))
		{
			return;
		}
		auto projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));

		projectile->Launch(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
		RoundsLeft--;
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int UTankAimingComponent::GetRoundsLeft() const
{
	return RoundsLeft;
}