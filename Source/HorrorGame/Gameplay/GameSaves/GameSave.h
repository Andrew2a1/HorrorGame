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
	FString filepath;
	uint8 userIndex;

public:
	UFUNCTION(BlueprintCallable, Category = "GameSave")
		static TArray<UGameSave*> getAllGameSaves();

public:
	UGameSave();
	UGameSave(const FString &FilePath, uint8 UserIndex = 0);

	UFUNCTION(BlueprintCallable, Category = "GameSave") 
		void setFilePath(const FString &FilePath);

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		void setFilePathFromFilename(const FString &Filename);

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		FString getFilePath() const;

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		FString getBaseFilename() const;

	UFUNCTION(BlueprintCallable, Category = "GameSave")
		FDateTime getFileTimeStamp() const;
	
	UFUNCTION(BlueprintCallable, Category = "GameSave")
		bool fileExists() const;

	UFUNCTION(BlueprintCallable, Category = "GameSave") 
		bool SaveData(UGameSaveData *gameSaveData) const;

	UFUNCTION(BlueprintCallable, Category = "GameSave") 
		UGameSaveData *LoadData() const;
};

