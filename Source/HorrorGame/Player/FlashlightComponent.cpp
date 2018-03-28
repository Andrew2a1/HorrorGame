// Copyright 2018 Adam Brząkała

#include "FlashlightComponent.h"

UFlashlightComponent::UFlashlightComponent() :
	lightPower(DEFAULT_LIGHT_INTENSITY),
	turnedOn(false)
{
	PrimaryComponentTick.bCanEverTick = false;

	light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	light->SetupAttachment(this);
	light->SetOuterConeAngle(30);
	light->SetIntensity(0.0f);
}

void UFlashlightComponent::BeginPlay()
{
	Super::BeginPlay();
	turnedOn = false;
}

void UFlashlightComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UFlashlightComponent::toggleLight()
{
	turnedOn = !turnedOn;

	if (turnedOn)
		light->SetIntensity(lightPower);
	else
		light->SetIntensity(0.0f);
}