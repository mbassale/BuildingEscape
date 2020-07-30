// Copyright 2020. Marco Bassaletti <bassaletti@gmail.com>

#include "OpenDoor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

#define INTERPOLATION_TOLERANCE 0.05

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	OpenAngle = InitialYaw + OpenAngle;
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (this->PressurePlate && GetTotalMassOfActors() > OpenMass) 
	{
		OpenDoor(DeltaTime);
		DoorLastOpened = GetWorld()->GetTimeSeconds();
	}
	else if ((GetWorld()->GetTimeSeconds() - DoorLastOpened) > CloseDelay) 
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (FMath::Abs(CurrentRotation.Yaw - OpenAngle) > INTERPOLATION_TOLERANCE) 
	{
		CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, OpenAngle, DeltaTime, OpenSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);

		if (AudioComponent && !AudioPlayed)
		{
			AudioComponent->Play();
			AudioPlayed = true;
		}
	} 
	else if (AudioPlayed)
	{
		AudioPlayed = false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	FRotator CurrentRotation = GetOwner()->GetActorRotation();
	if (FMath::Abs(CurrentRotation.Yaw - InitialYaw) > INTERPOLATION_TOLERANCE)
	{
		CurrentRotation.Yaw = FMath::FInterpConstantTo(CurrentRotation.Yaw, InitialYaw, DeltaTime, CloseSpeed);
		GetOwner()->SetActorRotation(CurrentRotation);

		if (AudioComponent && !AudioPlayed)
		{
			AudioComponent->Play();
			AudioPlayed = true;
		}
	}
	else if (AudioPlayed)
	{
		AudioPlayed = false;
	}
}

float UOpenDoor::GetTotalMassOfActors() const
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	if (this->PressurePlate)
	{
		this->PressurePlate->GetOverlappingActors(OverlappingActors);
		for (AActor* Actor : OverlappingActors)
		{
			TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}
	return TotalMass;
}