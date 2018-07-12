#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "GameSaveData.h"
#include "FindSavesVisitor.h"
#include "GameSave.generated.h"

UCLASS(BlueprintType)
class UGameSave : public UObject
{
	GENERATED_BODY()

private:
	UGameSaveData *gameSaveData;

	FString filename;
	uint8 userIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "GameSave")
		static TArray<UGameSave*> getAllGameSaves();

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		static UGameSave* CreateGameSave(UObject *Outer, const FString &Filename);

public:
	UGameSave();
	UGameSave(const FString &FilePath, uint8 UserIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "GameSave") 
		void setFilename(const FString &FileName);

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		FString getFilename() const;

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		FDateTime getFileTimeStamp() const;

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		UGameSaveData *GetSaveData() const;
	
	UFUNCTION(BlueprintCallable, Category = "GameSave")
		bool fileExists() const;

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		bool SaveData();

	UFUNCTION(BlueprintCallable, Category = "GameSave") 
		bool LoadData();

private:
	FString getFullPath() const;
};

