#pragma once

#include "CoreMinimal.h"
#include "FindSavesVisitor.h"
#include "SaveGameInfo.generated.h"

UCLASS(BlueprintType)
class USaveGameInfo : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static TArray<FString> GetAllGameSaveSlots();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static FDateTime GetSaveGameCreationDate(const FString &SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static FString GetSaveGameFullPath(const FString &SlotName);
};

