// Fill out your copyright notice in the Description page of Project Settings.

#include "EscapeGame.h"
#include "DoorComponent.h"


// Sets default values for this component's properties
UDoorComponent::UDoorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	World = GetWorld();
	Owner = GetOwner();
	ActorThatOpens = World->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = World->GetTimeSeconds();
	}

	if ((World->GetTimeSeconds() - LastDoorOpenTime) > CloseDoorDelay)
	{
		CloseDoor();
	}
}

//Opens the Door
void UDoorComponent::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenDoorAngle, 0.0f));
}

//Closes the Door
void UDoorComponent::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
}

