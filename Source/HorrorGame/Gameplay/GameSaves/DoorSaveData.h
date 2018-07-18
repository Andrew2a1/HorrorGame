#pragma once

#include "CoreMinimal.h"
#include "Objects/DoorSettings.h"
#include "DoorSaveData.generated.h"

USTRUCT(BlueprintType)
struct FDoorSaveData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FString DoorID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) FRotator DoorRotation;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) DoorOpenDirection OpenDirection;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool openRequested;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) bool movementRequested;
};