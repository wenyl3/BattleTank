// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    auto playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto controlledTank = Cast<ATank>(GetPawn());

    if (playerTank)
    {
        controlledTank->AimAt(playerTank->GetActorLocation());

        controlledTank->Fire();
    }
}
