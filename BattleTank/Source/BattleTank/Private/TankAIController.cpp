// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime)
{
    Super::Tick(deltaTime);

    auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto controlledTank = GetPawn();

    if (!ensure(playerTank && controlledTank))
    {
        return;
    }
    MoveToActor(playerTank, AcceptanceRadius);
    auto AimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(playerTank->GetActorLocation());

    if (AimingComponent->GetFiringState() == EFiringState::LOCKED)
    {
        AimingComponent->Fire();
    }
}
