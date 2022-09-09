// Fill out your copyright notice in the Description page of Project Settings.

#include "MainController.h"

#include "Characters/BaseCharacter.h"

#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"

AMainController::AMainController()
{
}

void AMainController::BeginPlay()
{
	bShowMouseCursor = true;
}

void AMainController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMainController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AMainController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AMainController::OnSetDestinationReleased);
}

void AMainController::RotatePawn(FVector DestToLook)
{
	ACharacter* MyCharacter = GetCharacter();
	FVector ToTarget = DestToLook - MyCharacter->GetActorLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	SetControlRotation(LookAtRotation);
}

void AMainController::MoveToMouseCursor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMainController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			RotatePawn(DestLocation);
		}
	}
}

void AMainController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMainController::OnSetDestinationReleased()
{
	bMoveToMouseCursor = false;
}
