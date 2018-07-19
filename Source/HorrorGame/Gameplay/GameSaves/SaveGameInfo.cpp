#include "SaveGameInfo.h"

#include "Gameplay/MainGameInstance.h"
#include "Gameplay/GameSaves/SavableObject.h"
#include "Engine/LevelStreaming.h"

TArray<FString> USaveGameInfo::GetAllGameSaveSlots()
{
	FFindSavesVisitor visitor;
	visitor.FindSaves();
	return visitor.GetAllFoundSlotNames();
}

bool USaveGameInfo::RemoveGameSaveSlot(const FString &SlotName)
{
	FString fullname = GetSaveGameFullPath(SlotName);
	return FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*fullname);
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

#include "Debug/DebugToolbox.h"

bool USaveGameInfo::SaveGame(const FString &SlotName, const UObject *WorldContextObj)
{
	UGameSaveData *gameSaveData = UGameSaveData::CreateGameSaveDataInstance();

	for (AActor *savableActor : GetAllSavableActors(WorldContextObj))
	{
		ISavableObject *savable = Cast<ISavableObject>(savableActor);
		if (savable)
			savable->Execute_SaveDataToGameSave(savableActor, gameSaveData);
	}

	return UGameplayStatics::SaveGameToSlot(gameSaveData, SlotName, DEFAULT_USER_INDEX);
}

bool USaveGameInfo::LoadGame(const FString &SlotName, const UObject *WorldContextObj)
{
	UGameSaveData *gameSaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, DEFAULT_USER_INDEX));

	for (AActor *savableActor : GetAllSavableActors(WorldContextObj))
	{
		ISavableObject *savable = Cast<ISavableObject>(savableActor);
		if (savable)
			savable->Execute_LoadDataFromGameSave(savableActor, gameSaveData);
	}

	return true;
}

TArray<AActor*> USaveGameInfo::GetAllSavableActors(const UObject *WorldContextObj)
{
	TArray<AActor*> savableActors;
	UGameplayStatics::GetAllActorsWithInterface(WorldContextObj, USavableObject::StaticClass(), savableActors);
	return savableActors;
}