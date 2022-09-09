// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainController.generated.h"

/**
 * 
 */
UCLASS()
class ROGUELIKE_API AMainController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainController();

protected:
	virtual void BeginPlay() override;

	uint32 bMoveToMouseCursor : 1;

	// PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// Rotate to moving location
	void RotatePawn(FVector DestToLook);

	// Navigate to player to the current touch location
	void MoveToMouseCursor();

	// Navigate player to the given world location
	void SetNewMoveDestination(const FVector DestLocation);

	// Input handlers for SetDestination action
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
};
