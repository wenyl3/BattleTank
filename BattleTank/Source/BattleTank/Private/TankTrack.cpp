// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::TickComponent(
    float DeltaTime,
    enum ELevelTick TickType,
    FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
    auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto correctionForce = tankRoot->GetMass() * correctionAcceleration / 2;
    tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
    auto ForceApplied = GetForwardVector() * throttle * MaxTrackDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}