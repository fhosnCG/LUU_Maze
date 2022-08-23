// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeDoor.h"
#include "Engine/TriggerVolume.h"
#include "../MazeCharacter.h"

AMazeDoor::AMazeDoor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMazeDoor::BeginPlay()
{
	Super::BeginPlay();

	StartZ = GetActorLocation().Z;
	OpenZ = GetActorLocation().Z + OpenZOffset;
	OpenSpeed = OpenZOffset / OpenTime;
	CloseSpeed = OpenZOffset / CloseTime;

	if (TriggerVolme)
	{
		TriggerVolme->OnActorBeginOverlap.AddDynamic(this, &AMazeDoor::OnVolumeBeginOverlap);
		TriggerVolme->OnActorEndOverlap.AddDynamic(this, &AMazeDoor::OnVolumeEndOverlap);
	}
}

void AMazeDoor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (DoorState == EDoorState::DS_Opening)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation.Z += DeltaSeconds * OpenSpeed;
		CurrentLocation.Z = FMath::Min(CurrentLocation.Z, OpenZ);
		SetActorLocation(CurrentLocation);
		if (FMath::IsNearlyEqual(CurrentLocation.Z, OpenZ))
		{
			OnOpened();
		}
	}
	else if(DoorState == EDoorState::DS_Closing)
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation.Z -= DeltaSeconds * CloseSpeed;
		CurrentLocation.Z = FMath::Max(CurrentLocation.Z, StartZ);
		SetActorLocation(CurrentLocation);
		if (FMath::IsNearlyEqual(CurrentLocation.Z, StartZ))
		{
			OnClosed();
		}
	}
	
}

void AMazeDoor::Open()
{
	DoorState = EDoorState::DS_Opening;
}

void AMazeDoor::Close()
{
	DoorState = EDoorState::DS_Closing;
}

void AMazeDoor::OnOpened()
{
	DoorState = EDoorState::DS_Opened;
}

void AMazeDoor::OnClosed()
{
	DoorState = EDoorState::DS_Closed;
}

void AMazeDoor::OnVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Val: %s"), ANSI_TO_TCHAR(__func__), *OtherActor->GetName());
	
	//early out if the door is already opened or opening
	if (DoorState == EDoorState::DS_Opened || DoorState == EDoorState::DS_Opening)
	{
		return;
	}
	
	//ignore non player characters
	if (!OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		return;
	}

	//door needs to open
	Open();
}

void AMazeDoor::OnVolumeEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Val: %s"), ANSI_TO_TCHAR(__func__), *OtherActor->GetName());

	//early out if the door is already opened or opening
	if (DoorState == EDoorState::DS_Closed || DoorState == EDoorState::DS_Closing)
	{
		return;
	}

	//ignore non player characters
	if (!OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		return;
	}

	//door needs to open
	Close();
}