#pragma once

#include "CoreMinimal.h"
#include "FindSavesVisitor.h"
#include "SaveGameInfo.generated.h"

constexpr int DEFAULT_USER_INDEX = 0;

UCLASS(BlueprintType)
class USaveGameInfo : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static TArray<FString> GetAllGameSaveSlots();

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static bool RemoveGameSaveSlot(const FString &SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static FDateTime GetSaveGameCreationDate(const FString &SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static FString GetSaveGameFullPath(const FString &SlotName);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static bool SaveGame(const FString &SlotName, const UObject *WorldContextObj);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static bool LoadGame(const FString &SlotName, const UObject *WorldContextObj);

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
		static TArray<AActor*> GetAllSavableActors(const UObject *WorldContextObj);
};

