// Copyright 2018 Adam Brzakala

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

UCLASS()
class HORRORGAME_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
private:
	FString SaveGameSlot;
	bool bShouldLoad;

public:
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void RequestGameLoad(const FString &SaveSlot);

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		void ClearGameLoadRequest();

	UFUNCTION(BlueprintCallable, Category = "Gameplay")
		bool IsGameLoadRequested() const;
};
