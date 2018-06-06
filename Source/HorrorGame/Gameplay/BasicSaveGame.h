// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

#include "../Objects/ItemDescriptor.h"
#include "../Objects/DoorSettings.h"

#include "BasicSaveGame.generated.h"

USTRUCT()
struct FPlayerInformation
{
	GENERATED_BODY()

public:
	FVector PlayerLocation;
	FRotator PlayerRotation;

	TArray<FItemDescriptor> collectedItems;
	bool isFlashlightTurnedOn;
};

USTRUCT()
struct FDoorInformation
{
	GENERATED_BODY()

public:
	FString DoorName;
	FRotator DoorRotation;

	DoorOpenDirection OpenDirection;
	bool Open;
	bool RequestMovement;
};

UCLASS()
class HORRORGAME_API UBasicSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "GamesaveData")
		FPlayerInformation MainCharacterInfo;

	UPROPERTY(VisibleAnywhere, Category = "GamesaveData")
		TArray<FDoorInformation> DoorInformations;

public:
	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		static UBasicSaveGame *CreateInstance();

	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		static UBasicSaveGame *LoadGame(const FString &SlotName, int UserIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "GameSaves") 
		bool SaveGame(const FString &SlotName, int UserIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		void FillSavegameWithData(UWorld *World);

	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		void LoadDataToActors(UWorld *World) const;

};
