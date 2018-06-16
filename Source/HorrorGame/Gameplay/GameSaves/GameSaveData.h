// Copyright 2018 Adam Brzakala

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"

#include "GameSaveData.generated.h"

UCLASS(BlueprintType)
class HORRORGAME_API UGameSaveData : public USaveGame
{
	GENERATED_BODY()
	
public:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamesaveData")
		FPlayerInformation MainCharacterInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamesaveData")
		TArray<FDoorInformation> DoorInformations;*/

public:
	/*UFUNCTION(BlueprintCallable, Category = "GameSaves")
		static TArray<FGamesave> getAllGamesaves();*/

	UFUNCTION(BlueprintCallable, Category = "GameSaves")
		static UGameSaveData *CreateGameSaveDataInstance();
};
