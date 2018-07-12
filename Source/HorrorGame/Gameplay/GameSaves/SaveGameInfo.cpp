#include "SaveGameInfo.h"

TArray<FString> USaveGameInfo::GetAllGameSaveSlots()
{
	FFindSavesVisitor visitor;
	visitor.FindSaves();
	return visitor.GetAllFoundSlotNames();
}

FDateTime USaveGameInfo::GetSaveGameCreationDate(const FString &SlotName)
{
	FString fullpath = USaveGameInfo::GetSaveGameFullPath(SlotName);
	return FPlatformFileManager::Get().GetPlatformFile().GetTimeStampLocal(*fullpath);
}

FString USaveGameInfo::GetSaveGameFullPath(const FString &SlotName)
{
	FString path = FPaths::Combine(FPaths::ProjectSavedDir(), SAVEGAMES_DIRECTORY, SlotName);
	return FPaths::SetExtension(path, SAVEGAME_EXTENSION);
}