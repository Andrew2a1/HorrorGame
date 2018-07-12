#include "GameSave.h"
#include "Debug/DebugToolbox.h"

TArray<UGameSave*> UGameSave::getAllGameSaves()
{
	TArray<UGameSave*> result;
	FFindSavesVisitor visitor;
	visitor.FindSaves();

	for (const FString &filename : visitor.GetAllFoundSlotNames())
	{
		UGameSave *SavegameObject = NewObject<UGameSave>();
		SavegameObject->setFilename(filename);
		result.Add(SavegameObject);
	}

	return result;
}

UGameSave* UGameSave::CreateGameSave(UObject *Outer, const FString &Filename)
{
	UGameSave *gamesave = NewObject<UGameSave>(Outer);

	if(gamesave != nullptr)
		gamesave->setFilename(Filename);

	return gamesave;
}

UGameSave::UGameSave() :
	userIndex(0)
{
	UGameSaveData *gameSaveData = UGameSaveData::CreateGameSaveDataInstance();
}

UGameSave::UGameSave(const FString &FileName, uint8 UserIndex) :
	filename(FileName),
	userIndex(UserIndex)
{
	UGameSaveData *gameSaveData = UGameSaveData::CreateGameSaveDataInstance();
}

void UGameSave::setFilename(const FString &FileName)
{
	filename = FileName;
}

FString UGameSave::getFullPath() const
{
	FString path = FPaths::Combine(FPaths::ProjectSavedDir(), SAVEGAMES_DIRECTORY, filename);
	return FPaths::SetExtension(path, SAVEGAME_EXTENSION);
}

FString UGameSave::getFilename() const
{
	return filename;
}

FDateTime UGameSave::getFileTimeStamp() const
{
	return FPlatformFileManager::Get().GetPlatformFile().GetTimeStampLocal(*getFullPath());
}

UGameSaveData *UGameSave::GetSaveData() const
{
	return gameSaveData;
}

bool UGameSave::fileExists() const
{
	return FPaths::FileExists(getFullPath());
}

bool UGameSave::SaveData()
{
	return UGameplayStatics::SaveGameToSlot(gameSaveData, filename, userIndex);
}

bool UGameSave::LoadData()
{
	gameSaveData = Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(filename, userIndex));
	return static_cast<bool>(gameSaveData);
}
