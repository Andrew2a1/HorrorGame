// Copyright 2018 Adam Brzakala

#include "GameSaveData.h"
#include "Kismet/GameplayStatics.h"

UGameSaveData *UGameSaveData::CreateGameSaveDataInstance()
{
	return Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
}