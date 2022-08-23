// Fill out your copyright notice in the Description page of Project Settings.


#include "MazePlayerController.h"

void AMazePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("LookYaw"), this, &AMazePlayerController::LookYaw);
	InputComponent->BindAxis(TEXT("LookPitch"), this, &AMazePlayerController::LookPitch);
	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMazePlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMazePlayerController::MoveRight);

	UE_LOG(LogTemp, Warning, TEXT("%s"), ANSI_TO_TCHAR(__func__));

	//set these up to actions
	//InputComponent->BindAxis(*MoveForwardAxisName, this, &AArchVisCharacter::MoveForward);
	//InputComponent->BindAxis(*MoveRightAxisName, this, &AArchVisCharacter::MoveRight);
}

void AMazePlayerController::LookYaw(float Val)
{
	if (Val != 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s Val: %f"), ANSI_TO_TCHAR(__func__));
		AddYawInput(Val * YawTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMazePlayerController::LookPitch(float Val)
{
	if (Val != 0.f)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s Val: %f"), ANSI_TO_TCHAR(__func__), Val);
		AddPitchInput(Val * PitchTurnRate * GetWorld()->GetDeltaSeconds());
	}
}

void AMazePlayerController::MoveForward(float Val)
{
	if (!GetPawn())
	{
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s Val: %f"), ANSI_TO_TCHAR(__func__));
	if (Val != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		// transform to world space and add it
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::X), Val);
	}
}

void AMazePlayerController::MoveRight(float Val)
{
	if (!GetPawn())
	{
		return;
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s Val: %f"), ANSI_TO_TCHAR(__func__));
	if (Val != 0.f)
	{
		FRotator const ControlSpaceRot = GetControlRotation();
		// transform to world space and add it
		GetPawn()->AddMovementInput(FRotationMatrix(ControlSpaceRot).GetScaledAxis(EAxis::Y), Val);
	}
}
