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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamesaveData")
		FVector PlayerPosition;

public:
	static UGameSaveData *CreateGameSaveDataInstance();
};
