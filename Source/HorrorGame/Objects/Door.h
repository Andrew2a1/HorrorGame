// Copyright 2018 Adam Brzakala

#pragma once

#include "DoorSettings.h"
#include "LockableItem.h"

#include "CoreMinimal.h"
#include "EngineMinimal.h"
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
	bool openRequested;
	bool movementRequested;

public:
	ADoor();
	virtual void Tick(float DeltaTime) override;

	void OpenDoor(DoorOpenDirection openDirection);
	void CloseDoor();

protected:
	virtual void BeginPlay() override;

	virtual void actionItemUnlocked(AActor *other) override;
	virtual void failedUnlock(AActor *other) override;
	virtual void succeededUnlock(AActor *other) override;

private:
	void performDoorOpen(float DeltaTime);

	float getTargetRotation() const;
	float getOpenSpeed() const;
	
	inline bool needRotationToOpen(float currentRotation, float targetRotation) const;
	inline bool needRotationToClose(float currentRotation) const;
	
	void rotate(float angle);
	void endDoorMovement();

	void openRightDirection(AActor *other);
	void playSoundIfValid(USoundCue *soundCue);

	float getAngleBetweenVectors(const FVector &arg1, const FVector &arg2) const;
	float normalizeAngle(float angle) const;
};
