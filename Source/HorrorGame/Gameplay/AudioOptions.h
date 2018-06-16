// Copyright 2018 Adam Brzakala

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *Master;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *Music;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *Effects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) USoundClass *Dialogue;
};

USTRUCT(BlueprintType)
struct HORRORGAME_API FVolumeSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Master;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Effects;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Music;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float Dialogue;

	FVolumeSettings() :
		Master(0.75f),
		Effects(0.75f),
		Music(0.75f),
		Dialogue(0.75f)
	{
		
	}
};
