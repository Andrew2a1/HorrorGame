#include "FindSavesVisitor.h"

#include "Paths.h"
#include "PlatformFile.h"
#include "PlatformFilemanager.h"

bool FFindSavesVisitor::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
	if (!bIsDirectory && isSavegameFile(FilenameOrDirectory))
		FoundSaveFilePaths.Add(FilenameOrDirectory);
	return true;
}

void FFindSavesVisitor::FindSaves()
{
	const FString SavesFolder = FPaths::Combine(FPaths::ProjectSavedDir(), SAVEGAMES_DIRECTORY);
	FPlatformFileManager::Get().GetPlatformFile().IterateDirectory(*SavesFolder, *this);
}

TArray<FString> FFindSavesVisitor::GetAllFoundFilePaths() const
{
	return FoundSaveFilePaths;
}

TArray<FString> FFindSavesVisitor::GetAllFoundSlotNames() const
{
	TArray<FString> SlotNames;

	for (const FString &FilePath : FoundSaveFilePaths)
	{
		FString BaseFilename = FPaths::GetBaseFilename(FilePath);
		SlotNames.Add(BaseFilename);
	}

	return SlotNames;
}

bool FFindSavesVisitor::isSavegameFile(const TCHAR* Filename) const
{
	return FPaths::GetExtension(Filename).Equals(SAVEGAME_EXTENSION);
}
