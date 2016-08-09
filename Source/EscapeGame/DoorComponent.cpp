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

	if (!PressurePlate)
		UE_LOG(LogTemp, Error, TEXT("NullPtr error: %s missig pressure plate"), *(GetOwner()->GetName()))
}


// Called every frame
void UDoorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	if (GetTotalMassOfActorsOnPlate() > TriggerPlateThreshold)
	{
		OpenRequest.Broadcast();
	}
	else
	{
		CloseRequest.Broadcast();
	}
}

float UDoorComponent::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;

	if (!PressurePlate) return TotalMass;
	PressurePlate->GetOverlappingActors(OverlappingActors);

	for (const auto& Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

