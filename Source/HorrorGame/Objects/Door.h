// Copyright 2018 Adam Brząkała

#pragma once

#include "EngineMinimal.h"
#include "InteractiveItem.h"
#include "../Player/MainCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

enum class DoorOpenDirection
{
	Inside,
	Outside
};

UCLASS()
class HORRORGAME_API ADoor : public AInteractiveItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere) UAudioComponent *audioComponent;
	UPROPERTY(EditAnywhere) USoundCue *openDoorSound;
	UPROPERTY(EditAnywhere) USoundCue *closeDoorSound;

	UPROPERTY(EditAnywhere) float openTime;
	UPROPERTY(EditAnywhere) float openDoorAngle;
	
private:
	DoorOpenDirection direction;
	float rotationAtStart;
	bool opened;

public:	
	ADoor();
	virtual void Tick(float DeltaTime) override;

	void OpenDoor(DoorOpenDirection openDirection);
	void CloseDoor();

protected:
	virtual void BeginPlay() override;
	virtual void interactFunction(AActor *other) override;

private:
	void openRightDirection(AActor *other);
	float wrapAngle(float angle);
	float getAngleBetweenVectors(const FVector &arg1, const FVector &arg2);
};
