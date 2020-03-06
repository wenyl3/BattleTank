// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
    Super::BeginPlay();
    OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
    auto slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
    auto DeltaTime = GetWorld()->GetDeltaSeconds();
    auto correctionAcceleration = -slippageSpeed / DeltaTime * GetRightVector();
    auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto correctionForce = tankRoot->GetMass() * correctionAcceleration / 2;
    tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
    CurrentThrottle = FMath::Clamp<float>(CurrentThrottle += throttle, -1, +1);
}

void UTankTrack::DriveTrack()
{
    auto ForceApplied = GetForwardVector() * CurrentThrottle * MaxTrackDrivingForce;
    auto ForceLocation = GetComponentLocation();
    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(
    UPrimitiveComponent *HitComponent,
    AActor *OtherActor,
    UPrimitiveComponent *OtherComponent,
    FVector NormalImpulse,
    const FHitResult &Hit)
{
    DriveTrack();
    ApplySidewaysForce();
    CurrentThrottle = 0;
}
