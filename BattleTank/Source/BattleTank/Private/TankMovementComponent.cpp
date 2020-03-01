// Copyright Wenyl3

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

    auto rightThrow = FVector::CrossProduct(tankForfard, AIForwardIntention).Z;
    IntendTurnRight(rightThrow);
}

void UTankMovementComponent::IntendMoveForward(float _throw)
{
    if (!ensure(LeftTrack && RightTrack))
    {
        return;
    }
    LeftTrack->SetThrottle(_throw);
    RightTrack->SetThrottle(_throw);
}

void UTankMovementComponent::IntendMoveBackward(float _throw)
{
    if (!ensure(LeftTrack && RightTrack))
    {
        return;
    }
    LeftTrack->SetThrottle(-_throw);
    RightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnRight(float _throw)
{
    if (!ensure(LeftTrack && RightTrack))
    {
        return;
    }
    LeftTrack->SetThrottle(_throw);
    RightTrack->SetThrottle(-_throw);
}

void UTankMovementComponent::IntendTurnLeft(float _throw)
{
    if (!ensure(LeftTrack && RightTrack))
    {
        return;
    }
    LeftTrack->SetThrottle(-_throw);
    RightTrack->SetThrottle(_throw);
}
