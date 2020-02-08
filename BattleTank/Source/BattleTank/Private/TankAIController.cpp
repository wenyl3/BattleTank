// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    auto controllerTank = GetControlledTank();
    if (!controllerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController not posessing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController posessing: %s"), *(controllerTank->GetName()));
    }

    auto playerTank = GetPlayerTank();
    if (!playerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController can't find player tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AIController found player: %s"), *(playerTank->GetName()));
    }
}

ATank *ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const
{
    auto playerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!playerPawn)
    {
        return nullptr;
    }
    return Cast<ATank>(playerPawn);
}