// Copyright 2018 Adam Brzakala

#include "Pickup.h"

APickup::APickup()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APickup::BeginPlay()
{
	Super::BeginPlay();
}

void APickup::interactFunction(AActor *other)
{
	AMainCharacter *player = Cast<AMainCharacter>(other);

	if (player)
	{
		player->addToEquipment(itemDescription);
		Destroy();
	}
}
