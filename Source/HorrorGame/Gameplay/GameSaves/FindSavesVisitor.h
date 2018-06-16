// Copyright 2018 Adam Brzakala

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "Containers/Array.h"

constexpr TCHAR* SavegamesDirectory = TEXT("SaveGames");
constexpr TCHAR* SavegameExtension = TEXT("sav");

class FFindSavesVisitor : public IPlatformFile::FDirectoryVisitor
{
private:
	TArray<FString> FoundSaveFilePaths;

public:
	void FindSaves();

	TArray<FString> GetAllFoundFilePaths() const;
	TArray<FString> GetAllFoundSlotNames() const;

private:
	virtual bool Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory);
	bool isSavegameFile(const TCHAR* Filename) const;
};
