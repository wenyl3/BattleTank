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

ATank *ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}