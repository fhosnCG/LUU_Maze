// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MazeDoor.generated.h"

class ATriggerVolume;

enum class EDoorState
{
	DS_None = 0,
	DS_Opened,
	DS_Closed,
	DS_Opening,
	DS_Closing,
};

UCLASS()
class LUU_MAZE_API AMazeDoor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMazeDoor();
	//AActor override
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	//~AActor override
protected:
	EDoorState DoorState = EDoorState::DS_None;

	UFUNCTION()
	void OnVolumeBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void OnVolumeEndOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void Open();
	void Close();

	void OnOpened();
	void OnClosed();

	float StartZ = 0.0f;
	float OpenZ = 0.0f;

	float CurrentZOffset = 0.0f;
	float OpenSpeed = 0.0f;
	float CloseSpeed = 0.0f;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<ATriggerVolume> TriggerVolme = nullptr;

	UPROPERTY(EditAnywhere)
	float OpenZOffset = 100.0f;

	UPROPERTY(EditAnywhere)
	float OpenTime = 1.0f;

	UPROPERTY(EditAnywhere)
	float CloseTime = 1.0f;
	//TWeakObjectPtr<>
};
