// Copyright 2018 Adam Brzakala

#pragma once

#include "GameSaveData.h"
#include "SavableObject.generated.h"

UINTERFACE(BlueprintType)
class HORRORGAME_API USavableObject : public UInterface
{
	GENERATED_BODY()

public:
	USavableObject(const class FObjectInitializer& ObjectInitializer);
};

class HORRORGAME_API ISavableObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SaveGame")
		bool LoadDataFromGameSave(const UGameSaveData *GameSaveData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "SaveGame")
		bool SaveDataToGameSave(UGameSaveData *GameSaveData) const;
};