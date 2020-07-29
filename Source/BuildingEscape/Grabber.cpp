// Fill out your copyright notice in the Description page of Project Settings.

#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Grabber.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber Begin Play."));
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle) 
	{
		UE_LOG(LogTemp, Error, TEXT("No physics handle: %s"), *(GetOwner()->GetName()));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) 
	{
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Pressed"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grabber Released"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0, 0, 5.f);

	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	if (GetWorld()->LineTraceSingleByObjectType(
		HitResult,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams))
	{
		AActor* ActorHit = HitResult.GetActor();
		if (ActorHit)
		{
			UE_LOG(LogTemp, Warning, TEXT("Selecting: %s"), *(ActorHit->GetName()));
			if (PhysicsHandle)
			{
				
			}
		}
	}
}

