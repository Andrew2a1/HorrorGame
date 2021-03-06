// Copyright 2018 Adam Brząkała

#include "BasicSaveGame.h"
#include "EngineUtils.h"

#include "../Debug/DebugToolbox.h"

UBasicSaveGame *UBasicSaveGame::CreateInstance()
{
	return Cast<UBasicSaveGame>(UGameplayStatics::CreateSaveGameObject(UBasicSaveGame::StaticClass()));
}

UBasicSaveGame *UBasicSaveGame::LoadGame(const FString &SlotName, int UserIndex)
{
	if (SlotName.IsEmpty())
		return nullptr;

	UBasicSaveGame *Savegame = Cast<UBasicSaveGame>(UGameplayStatics::CreateSaveGameObject(UBasicSaveGame::StaticClass()));
	Savegame = Cast<UBasicSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

	return Savegame;
}

bool UBasicSaveGame::SaveGame(const FString &SlotName, int UserIndex)
{
	if (SlotName.IsEmpty())
		return false;
	return UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
}