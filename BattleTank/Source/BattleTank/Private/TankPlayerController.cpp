// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
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
        GetControlledTank()->AimAt(hitLocation);
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &outHitLocation) const
{
    FVector2D screenLocation = GetScreenLocation();
    FVector lookDirection;
    if (GetLookDirection(screenLocation, lookDirection))
    {
        GetLookVectorHitLocation(lookDirection, outHitLocation);
    }

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector &outHitLcoation) const
{
    FHitResult hitResult;
    auto startLocation = PlayerCameraManager->GetCameraLocation();
    auto endLocation = startLocation + lookDirection * lineTraceRange;
    if (GetWorld()->LineTraceSingleByChannel(
            hitResult,
            startLocation,
            endLocation,
            ECollisionChannel::ECC_Visibility))
    {
        outHitLcoation = hitResult.Location;
        return true;
    }
    outHitLcoation = FVector(0.0);
    return false;
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