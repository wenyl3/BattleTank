// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto controllerTank = GetControlledTank();
    if (!controllerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController not posessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController posessing: %s"), *(controllerTank->GetName()));
    }
}

void ATankPlayerController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);
    AimTowardsCrosshair();
}

ATank *ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank())
    {
        return;
    }

    FVector hitLocation;
    if (GetSightRayHitLocation(hitLocation))
    {
        //UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *hitLocation.ToString());
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const
{
    FVector2D screenLocation = GetScreenLocation();
    FVector lookDirection;
    if (GetLookDirection(screenLocation, lookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *lookDirection.ToString());
    }
    return true;
}

FVector2D ATankPlayerController::GetScreenLocation() const
{
    int32 viewportSizeX, viewportSizeY;
    GetViewportSize(viewportSizeX, viewportSizeY);
    return FVector2D(viewportSizeX * crosshairXLocation,
                     viewportSizeY * crosshairYLocation);
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &lookDirection) const
{
    FVector cameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        screenLocation.X,
        screenLocation.Y,
        cameraWorldLocation,
        lookDirection);
}