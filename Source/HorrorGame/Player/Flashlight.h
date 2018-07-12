// Copyright 2018 Adam Brzakala

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "Components/SceneComponent.h"
#include "Flashlight.generated.h"

constexpr int DEFAULT_LIGHT_INTENSITY = 5000;

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

	void toggleLight();
	void setTurnedOn(bool isTurnedOn);

	inline bool isTurnedOn() const;
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
