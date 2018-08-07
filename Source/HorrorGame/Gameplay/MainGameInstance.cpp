// Copyright 2018 Adam Brzakala

#include "MainGameInstance.h"

FString UMainGameInstance::GetSaveGameName() const
{
	return SaveGameSlot;
}

void UMainGameInstance::RequestGameLoad(const FString &SaveSlot)
{
	SaveGameSlot = SaveSlot;
	bShouldLoad = true;
}

void UMainGameInstance::ClearGameLoadRequest()
{
	bShouldLoad = false;
}

bool UMainGameInstance::IsGameLoadRequested() const
{
	return bShouldLoad;
}
