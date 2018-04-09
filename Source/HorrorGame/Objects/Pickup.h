// Copyright 2018 Adam Brząkała

#pragma once

#include "../Player/MainCharacter.h"
#include "InteractiveItem.h"
#include "ItemDescriptor.h"

#include "CoreMinimal.h"
#include "Pickup.generated.h"

UCLASS()
class HORRORGAME_API APickup : public AInteractiveItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Description")
		FItemDescriptor itemDescription;

public:
	APickup();

protected:
	virtual void BeginPlay() override;
	virtual void interactFunction(AActor *other) override;
};
