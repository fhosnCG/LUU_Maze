// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MazePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class LUU_MAZE_API AMazePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

protected:
	virtual void SetupInputComponent() override;

	void LookYaw(float Val);
	void LookPitch(float Val);
	void MoveForward(float Val);
	void MoveRight(float Val);

	UPROPERTY(EditDefaultsOnly)
	float YawTurnRate = 90.0f;

	UPROPERTY(EditDefaultsOnly)
	float PitchTurnRate = 90.0f;
};
