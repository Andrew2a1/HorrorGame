#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "GameOptions.generated.h"

USTRUCT()
struct FSoundOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float MasterVolume;
	UPROPERTY(EditAnywhere) float MusicVolume;
	UPROPERTY(EditAnywhere) float EffectsVolume;
	UPROPERTY(EditAnywhere) float DialogueVolume;
};

USTRUCT()
struct FGameOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) FString PlayerName;
	UPROPERTY(EditAnywhere) FSoundOptions SoundOptions;
};

