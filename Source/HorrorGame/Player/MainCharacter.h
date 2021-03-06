// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "GameFramework/Character.h"

#include "Flashlight.h"
#include "Objects/InteractiveItem.h"
#include "Objects/ItemDescriptor.h"

#include "MainCharacter.generated.h"

constexpr float DefaultCharacterSpeed = 600;

UCLASS()
class HORRORGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) TSubclassOf<class AFlashlight> FlashlightBlueprint;
	UPROPERTY(EditAnywhere) USceneComponent *FlashlightSpawnLocation;

	UPROPERTY(VisibleAnywhere) UCameraComponent *EyeView;
	UPROPERTY(EditAnywhere) float sprintModificator;
	UPROPERTY(EditAnywhere) float maxPlayerRange;

private:
	AFlashlight *flashlight;
	AInteractiveItem *lastPointerTarget;
	TArray<FItemDescriptor> collectedItems;

public:	
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void addToEquipment(const FItemDescriptor &item);
	bool hasItemInEquipment(const FName &itemName);

protected:
	virtual void BeginPlay() override;

private:
	AActor *getPointerTarget();
	bool isActorInPlayerRange(AActor *target);

	inline bool userStartedPointingAtItem(const AInteractiveItem *item) const;
	inline bool userEndedPointingAtItem(const AInteractiveItem *item) const;

	void moveForward(float Value);
	void moveRight(float Value);

	void startJump();
	void stopJump();

	void startSprint();
	void stopSprint();

	void startCrouch();
	void stopCrouch();

	void interact();
	void toggleFlashlight();

	void printDebug();
};
