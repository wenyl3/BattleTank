// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float) override;

private:
	ATank *GetControlledTank() const;
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector &) const;
	bool GetLookDirection(FVector2D, FVector &) const;
	FVector2D GetScreenLocation() const;
	bool GetLookVectorHitLocation(FVector, FVector &) const;

	UPROPERTY(EditAnywhere)
	float crosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float crosshairYLocation = 0.33333;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000;
};
