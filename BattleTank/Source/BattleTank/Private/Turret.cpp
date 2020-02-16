// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"


void UTurret::Rotate(float relativeSpeed)
{
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
    auto rotationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto rotation = RelativeRotation.Yaw + rotationChange;

    SetRelativeRotation(FRotator(0, rotation, 0));

    UE_LOG(LogTemp, Warning, TEXT("Rotate called at speed: %f"), relativeSpeed);
}