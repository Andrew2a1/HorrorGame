// Copyright 2018 Adam Brzakala

#include "MainGameInstance.h"

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
