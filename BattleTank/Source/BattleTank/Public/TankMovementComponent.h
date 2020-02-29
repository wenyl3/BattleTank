// Copyright Wenyl3

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for driving the tank tracks.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveForward(float _throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendMoveBackward(float _throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnRight(float _throw);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void IntendTurnLeft(float _throw);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankTrack *leftTrackToSet, UTankTrack *rightTrackToSet);

private:
	virtual void RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed) override;

	UTankTrack *LeftTrack = nullptr;
	UTankTrack *RightTrack = nullptr;
};
