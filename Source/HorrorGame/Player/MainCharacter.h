// Copyright 2018 Adam Brz¹ka³a

#pragma once

#include "EngineMinimal.h"
#include "Flashlight.h"
#include "../Objects/InteractiveItem.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

constexpr float BASIC_CHARACTER_SPEED = 600;

UCLASS()
class HORRORGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) TSubclassOf<class AFlashlight> FlashlightBlueprint;
	UPROPERTY(VisibleAnywhere) AFlashlight *flashlight;

	UPROPERTY(VisibleAnywhere) UCameraComponent *EyeView;
	UPROPERTY(EditAnywhere) float sprintModificator;
	UPROPERTY(EditAnywhere) float MaxPlayerRange;

private:
	AInteractiveItem *prevPointerTarget;

public:	
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	AActor *mouseTraceHitResult();
	bool isActorInPlayerRange(AActor *target);

	UFUNCTION() void moveForward(float Value);
	UFUNCTION() void moveRight(float Value);

	UFUNCTION() void startJump();
	UFUNCTION() void stopJump();

	UFUNCTION() void startSprint();
	UFUNCTION() void stopSprint();

	/*UFUNCTION() void startCrouch();
	UFUNCTION() void stopCrouch();*/

	UFUNCTION() void interact();
	UFUNCTION() void toggleFlashlight();
};
