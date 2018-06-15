// Copyright 2018 Adam Brząkała

#include "BasicSaveGame.h"
#include "FindSavesVisitor.h"

#include "../Debug/DebugToolbox.h"

TArray<FString> UBasicSaveGame::getAllSavegameSlots()
{
	FFindSavesVisitor savesVisitor;
	savesVisitor.FindSaves();
	return savesVisitor.GetAllFoundSlotNames();
}

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