// Copyright 2018 Adam Brzakala

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "GameFramework/Actor.h"
#include "Sound/SoundCue.h"

#include "DoorSettings.h"
#include "LockableItem.h"

#include "Gameplay/GameSaves/SavableObject.h"
#include "Gameplay/GameSaves/GameSaveData.h"

#include "Door.generated.h"

UCLASS()
class HORRORGAME_API ADoor : public ALockableItem, public ISavableObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Door") USoundCue *openDoorSound;
	UPROPERTY(EditAnywhere, Category = "Door") USoundCue *closeDoorSound;
	UPROPERTY(EditAnywhere, Category = "Door") USoundCue *lockedDoorSound;

	UPROPERTY(EditAnywhere, Category = "Door") float openTime;
	UPROPERTY(EditAnywhere, Category = "Door") float openDoorAngle;
	
private:
	UAudioComponent *AudioComponent;
	DoorOpenDirection OpenDirection;

	float rotationAtStart;
	bool openRequested;
	bool movementRequested;

public:
	ADoor();

	void OpenDoor(DoorOpenDirection openDirection);
	void CloseDoor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveGame")
		bool LoadDataFromGameSave(const UGameSaveData *GameSaveData);
		virtual bool LoadDataFromGameSave_Implementation(const UGameSaveData *GameSaveData) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "SaveGame")
		bool SaveDataToGameSave(UGameSaveData *GameSaveData) const;
		virtual bool SaveDataToGameSave_Implementation(UGameSaveData *GameSaveData) const override;

protected:
	virtual void BeginPlay() override;

	virtual void actionItemUnlocked(AActor *other) override;
	virtual void failedUnlock(AActor *other) override;
	virtual void succeededUnlock(AActor *other) override;

private:
	void openRightDirection(AActor *other);
	void performDoorOpen(float DeltaTime);
	void rotate(float angle);
	void endDoorMovement();

	void playSoundIfValid(USoundCue *soundCue);

	float getTargetRotation() const;
	float getOpenSpeed() const;

	float getAngleBetweenVectors(const FVector &arg1, const FVector &arg2) const;
	float normalizeAngle(float angle) const;

	inline bool needRotationToOpen(float currentRotation, float targetRotation) const;
	inline bool needRotationToClose(float currentRotation) const;
};
