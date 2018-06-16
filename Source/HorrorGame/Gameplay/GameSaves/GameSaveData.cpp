// Copyright 2018 Adam Brząkała

#include "GameSaveData.h"
#include "FindSavesVisitor.h"

UGameSaveData *UGameSaveData::CreateGameSaveDataInstance()
{
	return Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
}