// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "EngineGlobals.h"
#include "Engine/Engine.h"

#include "AudioOptions.h"
#include "ConfigCacheIni.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "AudioUserSettings.generated.h"

constexpr TCHAR* AudioSectionName = TEXT("Audio");
constexpr TCHAR* MasterVolumeKey = TEXT("MasterVolume");
constexpr TCHAR* MusicVolumeKey = TEXT("MusicVolume");
constexpr TCHAR* EffectsVolumeKey = TEXT("EffectsVolume");
constexpr TCHAR* DialogueVolumeKey = TEXT("DialogueVolume");

UCLASS(BlueprintType)
class HORRORGAME_API UAudioUserSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AudioOptions")
		FAudioOptions AudioOptions;

private:
	UObject *WorldContextObj;

	USoundMix *BaseSoundMix;
	USoundClass *MasterSoundClass;
	USoundClass *MusicSoundClass;
	USoundClass *EffectsSoundClass;
	USoundClass *DialogueSoundClass;

public:
	UAudioUserSettings();

	UFUNCTION(BlueprintCallable) void Init(USoundMix *InBaseSoundMix,
		USoundClass *InMasterSoundClass,
		USoundClass *InMusicSoundClass,
		USoundClass *InEffectsSoundClass,
		USoundClass *InDialogueSoundClass);

	UFUNCTION(BlueprintCallable) void ApplyForWorld(UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AudioSettings") bool LoadSettings();
	UFUNCTION(BlueprintCallable, Category = "AudioSettings") void SaveSettings() const;

	UFUNCTION(BlueprintCallable, Category = "AudioSettings") void ChangeMasterVolume(float NewVolume);
	UFUNCTION(BlueprintCallable, Category = "AudioSettings") void ChangeMusicVolume(float NewVolume);
	UFUNCTION(BlueprintCallable, Category = "AudioSettings") void ChangeEffectsVolume(float NewVolume);
	UFUNCTION(BlueprintCallable, Category = "AudioSettings") void ChangeDialogueVolume(float NewVolume);
};
