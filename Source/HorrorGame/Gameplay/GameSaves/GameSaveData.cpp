// Copyright 2018 Adam Brzakala

#include "GameSaveData.h"

UGameSaveData *UGameSaveData::CreateGameSaveDataInstance()
{
	return Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
}