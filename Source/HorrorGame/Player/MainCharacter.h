// Copyright 2018 Adam Brz¹ka³a

#pragma once

#include "Engine.h"
#include "Flashlight.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

constexpr float BASIC_CHARACTER_SPEED = 600;

UCLASS()
class HORRORGAME_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere) UCameraComponent *EyeView;
	UPROPERTY(VisibleAnywhere) AFlashlight *flashlight;
	UPROPERTY(EditAnywhere) float sprintModificator;

public:	
	AMainCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION() void moveForward(float Value);
	UFUNCTION() void moveRight(float Value);

	UFUNCTION() void startJump();
	UFUNCTION() void stopJump();

	UFUNCTION() void startSprint();
	UFUNCTION() void stopSprint();

	UFUNCTION() void startCrouch();
	UFUNCTION() void stopCrouch();

	UFUNCTION() void toggleFlashlight();
};
