// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "AudioOptions.generated.h"

USTRUCT(BlueprintType)
struct HORRORGAME_API FAudioOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MasterVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float EffectsVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MusicVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DialogueVolume;

	FAudioOptions() :
		MasterVolume(0.75f),
		EffectsVolume(0.75f),
		MusicVolume(0.75f),
		DialogueVolume(0.75f)
	{
		
	}
};
