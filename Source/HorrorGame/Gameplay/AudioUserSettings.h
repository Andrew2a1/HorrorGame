// Copyright 2018 Adam Brzakala

#pragma once


#include "CoreMinimal.h"
#include "EngineMinimal.h"

#include "Kismet/GameplayStatics.h"
#include "ConfigCacheIni.h"

#include "AudioOptions.h"
#include "AudioUserSettings.generated.h"

UCLASS(BlueprintType)
class HORRORGAME_API UAudioUserSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AudioSettings")
		FVolumeSettings VolumeSettings;

private:
	UObject *WorldContextObj;

	USoundMix *BaseSoundMix;
	FSoundClasses SoundClasses;

public:
	UAudioUserSettings();
	UAudioUserSettings(USoundMix *BaseSoundMix, const FSoundClasses &SoundClasses);

	UFUNCTION(BlueprintCallable)
		void Init(USoundMix *BaseSoundMix, const FSoundClasses &SoundClasses);

	UFUNCTION(BlueprintCallable)
		void ChangeWorld(UObject *WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "AudioSettings")
		bool LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "AudioSettings")
		void SaveSettings() const;

	UFUNCTION(BlueprintCallable, Category = "AudioSettings")
		void ChangeMasterVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "AudioSettings")
		void ChangeMusicVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "AudioSettings")
		void ChangeEffectsVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "AudioSettings")
		void ChangeDialogueVolume(float NewVolume);

private:
	float GetAudioVolumeForKey(const TCHAR *Key) const;
	void SaveAudioVolumeForKey(const TCHAR *Key, float Volume) const;

	void SetVolumeForSoundClass(USoundClass *SoundClass, float Volume);
};
