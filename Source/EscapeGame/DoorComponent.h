// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPEGAME_API UDoorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

			
private:
	void OpenDoor();
	void CloseDoor();
	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float OpenDoorAngle = 60.0f;

	UPROPERTY(EditAnywhere)
		float CloseDoorDelay = 1.0f;

	UPROPERTY(EditAnywhere)
		float TriggerPlateThreshold = 40.f;

	UWorld* World;
	AActor* Owner = nullptr;

	float LastDoorOpenTime;

	

};
