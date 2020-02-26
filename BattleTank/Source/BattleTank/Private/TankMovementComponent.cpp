// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(
    UTankTrack *leftTrackToSet,
    UTankTrack *rightTrackToSet)
{
    if (!leftTrackToSet || !rightTrackToSet)
    {
        return;
    }
    RightTrack = rightTrackToSet;
    LeftTrack = leftTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float _throw)
{
    LeftTrack->SetThrottle(_throw);
    RightTrack->SetThrottle(_throw);
}

void UTankMovementComponent::IntendMoveBackward(float _throw)
{
    LeftTrack->SetThrottle(-_throw);
    RightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnRight(float _throw)
{
    LeftTrack->SetThrottle(_throw);
    RightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnLeft(float _throw)
{
    LeftTrack->SetThrottle(-_throw);
    RightTrack->SetThrottle(_throw);
}
