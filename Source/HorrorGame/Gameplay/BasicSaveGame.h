// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

#include "BasicSaveGame.generated.h"

UCLASS()
class HORRORGAME_API UBasicSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamesaveData")
		FPlayerInformation MainCharacterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamesaveData")
		TArray<FDoorInformation> DoorInformations;*/

public:
	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		static UBasicSaveGame *CreateInstance();

	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		static UBasicSaveGame *LoadGame(const FString &SlotName, int UserIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "GameSaves") 
		bool SaveGame(const FString &SlotName, int UserIndex = 0);
};
