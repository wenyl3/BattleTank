// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!Barrel)
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
		launchSpeed,
		false, 0, 0,
		ESuggestProjVelocityTraceOption::DoNotTrace);
	if (bHaveAimSolution)
	{
		auto aimDirection = outLaunchVelocity.GetSafeNormal();
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found"), time);

		MoveBarrelTowards(aimDirection);
	}
	else
	{
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution not found"), time);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel *barrelToSet)
{

	this->Barrel = barrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector aimDirection)
{
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimAsRotator = aimDirection.Rotation();
	auto deltaRotator = aimAsRotator - barrelRotator;

	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *deltaRotator.ToString());

	Barrel->Elevate(5);
}