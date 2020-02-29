// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(
    UTankTrack *leftTrackToSet,
    UTankTrack *rightTrackToSet)
{
    RightTrack = rightTrackToSet;
    LeftTrack = leftTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector &MoveVelocity, bool bForceMaxSpeed)
{
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto tankForfard = GetOwner()->GetActorForwardVector().GetSafeNormal();

    auto forwardThrow = FVector::DotProduct(tankForfard, AIForwardIntention);
    IntendMoveForward(forwardThrow);
}

void UTankMovementComponent::IntendMoveForward(float _throw)
{
    if (!LeftTrack || !RightTrack)
    {
        return;
    }
    LeftTrack->SetThrottle(_throw);
    RightTrack->SetThrottle(_throw);
}

void UTankMovementComponent::IntendMoveBackward(float _throw)
{
    if (!LeftTrack || !RightTrack)
    {
        return;
    }
    LeftTrack->SetThrottle(-_throw);
    RightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnRight(float _throw)
{
    if (!LeftTrack || !RightTrack)
    {
        return;
    }
    LeftTrack->SetThrottle(_throw);
    RightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnLeft(float _throw)
{
    if (!LeftTrack || !RightTrack)
    {
        return;
    }
    LeftTrack->SetThrottle(-_throw);
    RightTrack->SetThrottle(_throw);
}
