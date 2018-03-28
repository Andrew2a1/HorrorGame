// Copyright 2018 Adam Brząkała

#pragma once

#include "Engine.h"

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "FlashlightComponent.generated.h"

constexpr int DEFAULT_LIGHT_INTENSITY = 5000;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HORRORGAME_API UFlashlightComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere) USpotLightComponent *light;
	UPROPERTY(EditAnywhere) float lightPower;

private:
	bool turnedOn;

public:	
	UFlashlightComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void toggleLight();

protected:
	virtual void BeginPlay() override;

};
