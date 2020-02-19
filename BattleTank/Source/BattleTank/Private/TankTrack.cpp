// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
    auto name = GetName();
    UE_LOG(LogTemp, Warning, TEXT("[%s] Track throttle rate: %f"), *name, throttle);

    auto ForceApplied = GetForwardVector() * throttle * MaxTrackDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}