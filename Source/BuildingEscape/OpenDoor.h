// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UENUM()
enum EDoorType {
	DOOR_TYPE_ROTATING	UMETA(DisplayName = "Rotating Door"),
	DOOR_TYPE_SLIDE		UMETA(DisplayName = "Sliding Door"),
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float GetTotalMassOfActors() const;

private:
	UPROPERTY(EditAnywhere, Category = EDoorType)
	TEnumAsByte<EDoorType> DoorType = DOOR_TYPE_ROTATING;

	UPROPERTY(EditAnywhere)
	float VerticalOffset = 100.0f;

	float InitialVerticalPosition;
	float FinalVerticalPosition;

	float InitialYaw;

	float CurrentYaw;

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.f;

	UPROPERTY(EditAnywhere)
	float OpenSpeed = 45.f;

	UPROPERTY(EditAnywhere)
	float CloseSpeed = 60.f;

	UPROPERTY(EditAnywhere)
	float CloseDelay = 2.f;

	UPROPERTY(EditAnywhere)
	float OpenMass = 50.0f;
		
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
	bool AudioPlayed = false;

	float DoorLastOpened = 0.f;
};
