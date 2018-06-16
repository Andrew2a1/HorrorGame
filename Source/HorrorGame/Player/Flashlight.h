// Copyright 2018 Adam Brzakala

#pragma once

#include "Engine.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Flashlight.generated.h"

constexpr int DefaultLightIntensity = 5000;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORGAME_API AFlashlight : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) USceneComponent *itemRoot;
	UPROPERTY(EditAnywhere) UStaticMeshComponent *FlashlightMesh;
	UPROPERTY(EditAnywhere) USpotLightComponent *light;

	UPROPERTY(EditAnywhere) float lightPower;

private:
	bool turnedOn;

public:	
	AFlashlight();
	virtual void Tick(float DeltaTime) override;

	void toggleLight();
	void setTurnedOn(bool isTurnedOn);

	inline bool isTurnedOn() const {
		return turnedOn;
	}

protected:
	virtual void BeginPlay() override;
};
