// Copyright 2018 Adam Brząkała

#pragma once

#include "EngineMinimal.h"

#include "LockableItem.h"
#include "ItemDescriptor.h"
#include "DoorSettings.h"
#include "../Gameplay/BasicSaveGame.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Door.generated.h"

UCLASS()
class HORRORGAME_API ADoor : public ALockableItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Door") USoundCue *openDoorSound;
	UPROPERTY(EditAnywhere, Category = "Door") USoundCue *closeDoorSound;
	UPROPERTY(EditAnywhere, Category = "Door") USoundCue *lockedDoorSound;

	UPROPERTY(EditAnywhere, Category = "Door") float openTime;
	UPROPERTY(EditAnywhere, Category = "Door") float openDoorAngle;
	
private:
	UAudioComponent *audioComponent;
	DoorOpenDirection direction;

	float rotationAtStart;
	bool opened;
	bool requestMovement;

public:
	ADoor();
	virtual void Tick(float DeltaTime) override;

	void OpenDoor(DoorOpenDirection openDirection);
	void CloseDoor();

	FDoorInformation GetDoorState() const;
	void LoadDoorState(const FDoorInformation &DoorState);

protected:
	virtual void BeginPlay() override;

	virtual void actionItemUnlocked(AActor *other) override;
	virtual void failedUnlock(AActor *other) override;
	virtual void succeededUnlock(AActor *other) override;

private:
	void openRightDirection(AActor *other);
	void playSoundIfValid(USoundCue *soundCue);

	float wrapAngle(float angle);
	float getAngleBetweenVectors(const FVector &arg1, const FVector &arg2);
};
