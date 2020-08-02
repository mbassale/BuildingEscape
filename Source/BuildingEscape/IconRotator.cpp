// Copyright 2020. Marco Bassaletti. All rights reserved.

#include "IconRotator.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UIconRotator::UIconRotator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UIconRotator::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UIconRotator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator ActorRotation = GetOwner()->GetActorRotation();
	const float FinalRotation = ActorRotation.Yaw + 90.0f;
	ActorRotation.Yaw = FMath::FInterpConstantTo(ActorRotation.Yaw, FinalRotation, DeltaTime, RotationSpeed);
	GetOwner()->SetActorRotation(ActorRotation);
}

