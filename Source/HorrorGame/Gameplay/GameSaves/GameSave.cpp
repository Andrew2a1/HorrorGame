#include "GameSave.h"

TArray<UGameSave*> UGameSave::getAllGameSaves()
{
	TArray<UGameSave*> result;
	FFindSavesVisitor visitor;
	visitor.FindSaves();

	for (const FString &filepath : visitor.GetAllFoundFilePaths())
	{
		UGameSave *SavegameObject = NewObject<UGameSave>();
		SavegameObject->setFilePath(filepath);
		result.Add(SavegameObject);
	}

	return result;
}

UGameSave::UGameSave() :
	userIndex(0)
{

}

UGameSave::UGameSave(const FString &FilePath, uint8 UserIndex) :
	filepath(FilePath),
	userIndex(UserIndex)
{

}

void UGameSave::setFilePath(const FString &FilePath)
{
	filepath = FilePath;
}

void UGameSave::setFilePathFromFilename(const FString &Filename)
{
	filepath = FPaths::Combine(FPaths::ProjectSavedDir(), SavegamesDirectory, Filename);
	filepath = FPaths::SetExtension(filepath, SavegameExtension);
}

FString UGameSave::getFilePath() const
{
	return filepath;
}

FString UGameSave::getBaseFilename() const
{
	return FPaths::GetBaseFilename(filepath);
}

FDateTime UGameSave::getFileTimeStamp() const
{
	return FPlatformFileManager::Get().GetPlatformFile().GetTimeStampLocal(*filepath);
}

bool UGameSave::fileExists() const
{
	return FPaths::FileExists(filepath);
}

bool UGameSave::SaveData(UGameSaveData *gameSaveData) const
{
	return UGameplayStatics::SaveGameToSlot(gameSaveData, getBaseFilename(), userIndex);
}

UGameSaveData *UGameSave::LoadData() const
{
	return Cast<UGameSaveData>(UGameplayStatics::LoadGameFromSlot(getBaseFilename(), userIndex));
}
