// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"
#include "AudioOptions.generated.h"

constexpr float DefaultSoundPitch = 1.0f;
constexpr float DefaultSoundFadeInTime = 0.4f;

constexpr TCHAR* AudioSectionName = TEXT("Audio");
constexpr TCHAR* MasterVolumeKey = TEXT("MasterVolume");
constexpr TCHAR* MusicVolumeKey = TEXT("MusicVolume");
constexpr TCHAR* EffectsVolumeKey = TEXT("EffectsVolume");
constexpr TCHAR* DialogueVolumeKey = TEXT("DialogueVolume");

USTRUCT(BlueprintType)
struct HORRORGAME_API FSoundClasses
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *MasterSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *MusicSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *EffectsSoundClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *DialogueSoundClass;
};

USTRUCT(BlueprintType)
struct HORRORGAME_API FVolumeSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MasterVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float EffectsVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MusicVolume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float DialogueVolume;

	FVolumeSettings() :
		MasterVolume(0.75f),
		EffectsVolume(0.75f),
		MusicVolume(0.75f),
		DialogueVolume(0.75f)
	{
		
	}
};
