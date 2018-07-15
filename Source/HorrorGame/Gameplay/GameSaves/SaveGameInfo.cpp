#include "SaveGameInfo.h"
#include "Gameplay/MainGameInstance.h"
#include "Gameplay/GameSaves/SavableObject.h"

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

bool USaveGameInfo::SaveGame(const FString &SlotName, const UObject *WorldContextObj)
{
	UGameSaveData *gameSaveData = Cast<UGameSaveData>(UGameplayStatics::CreateSaveGameObject(UGameSaveData::StaticClass()));
	TArray<AActor*> savableActors = GetAllSavableActors(WorldContextObj);
	
	for (AActor *savableActor : savableActors)
	{
		ISavableObject *savable = Cast<ISavableObject>(savableActor);

		if (savable)
			savable->Execute_SaveDataToGameSave(savableActor, gameSaveData);
	}

	gameSaveData->LevelName = UGameplayStatics::GetCurrentLevelName(WorldContextObj);
	return UGameplayStatics::SaveGameToSlot(gameSaveData, SlotName, DEFAULT_USER_INDEX);
}

bool USaveGameInfo::LoadGame(const FString &SlotName, const UObject *WorldContextObj)
{
	UGameSaveData *gameSaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(SlotName, DEFAULT_USER_INDEX));
	UMainGameInstance *gameInstance = Cast<UMainGameInstance>(UGameplayStatics::GetGameInstance(WorldContextObj));

	UGameplayStatics::OpenLevel(WorldContextObj, FName(*gameSaveData->LevelName));
	
	TArray<AActor*> savableActors = GetAllSavableActors(gameInstance->WorldContextObject);
	for (AActor *savableActor : savableActors)
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