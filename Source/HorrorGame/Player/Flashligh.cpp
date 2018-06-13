// Copyright 2018 Adam Brząkała

#include "Flashlight.h"

AFlashlight::AFlashlight() :
	lightPower(DefaultLightIntensity),
	turnedOn(false)
{
	PrimaryActorTick.bCanEverTick = false;

	itemRoot = CreateDefaultSubobject<USceneComponent>(TEXT("ItemRoot"));
	RootComponent = itemRoot;

	FlashlightMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FlashlightMesh"));
	FlashlightMesh->SetupAttachment(itemRoot);

	light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	light->SetupAttachment(itemRoot);
	light->SetIntensity(0.0f);
}

void AFlashlight::BeginPlay()
{
	Super::BeginPlay();

	turnedOn = false;
	light->SetIntensity(0.0f);
}

void AFlashlight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlashlight::toggleLight()
{
	turnedOn = !turnedOn;
	setTurnedOn(turnedOn);
}

void AFlashlight::setTurnedOn(bool isTurnedOn)
{
	if (isTurnedOn)
		light->SetIntensity(lightPower);
	else
		light->SetIntensity(0.0f);
}