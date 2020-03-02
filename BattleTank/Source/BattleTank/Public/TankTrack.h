// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Class used to set maximum driving force and to apply forces to the tank.
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float throttle);

	UPROPERTY(EditDefaultsOnly)
	float MaxTrackDrivingForce = 36000000; // Assume 36t tank and 1g acceleration

private:
	UTankTrack();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent,
			   AActor *OtherActor,
			   UPrimitiveComponent *OtherComponent,
			   FVector NormalImpulse,
			   const FHitResult &Hit);

	void ApplySidewaysForce();
	void DriveTrack();

	float CurrentThrottle = 0;
};
