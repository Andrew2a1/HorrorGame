// Copyright 2018 Adam Brząkała

#include "AudioUserSettings.h"

UAudioUserSettings::UAudioUserSettings() :
	WorldContextObj(nullptr)
{
	
}

void UAudioUserSettings::Init(USoundMix *InBaseSoundMix,
	USoundClass *InMasterSoundClass,
	USoundClass *InMusicSoundClass,
	USoundClass *InEffectsSoundClass,
	USoundClass *InDialogueSoundClass)
{
	BaseSoundMix = InBaseSoundMix;
	MasterSoundClass = InMasterSoundClass;
	MusicSoundClass = InMusicSoundClass;
	EffectsSoundClass = InEffectsSoundClass;
	DialogueSoundClass = InDialogueSoundClass;
}

void UAudioUserSettings::ApplyForWorld(UObject *WorldContextObject)
{
	WorldContextObj = WorldContextObject;

	UGameplayStatics::SetBaseSoundMix(WorldContextObj, BaseSoundMix);
	ChangeMasterVolume(AudioOptions.MasterVolume);
}

bool UAudioUserSettings::LoadSettings()
{
	if (!GConfig) 
		return false;

	bool bIsValueValid;

	bIsValueValid = GConfig->GetFloat(
		AudioSectionName,
		MasterVolumeKey,
		AudioOptions.MasterVolume,
		GGameUserSettingsIni
	);

	if (!bIsValueValid) AudioOptions.MasterVolume = 0.75;

	bIsValueValid = GConfig->GetFloat(
		AudioSectionName,
		MusicVolumeKey,
		AudioOptions.MusicVolume,
		GGameUserSettingsIni
	);

	if (!bIsValueValid) AudioOptions.MusicVolume = 0.75;

	bIsValueValid = GConfig->GetFloat(
		AudioSectionName,
		EffectsVolumeKey,
		AudioOptions.EffectsVolume,
		GGameUserSettingsIni
	);

	if (!bIsValueValid) AudioOptions.EffectsVolume = 0.75;

	bIsValueValid = GConfig->GetFloat(
		AudioSectionName,
		DialogueVolumeKey,
		AudioOptions.DialogueVolume,
		GGameUserSettingsIni
	);

	if (!bIsValueValid) AudioOptions.DialogueVolume = 0.75;

	return true;
}

void UAudioUserSettings::SaveSettings() const
{
	if (!GConfig)
		return;

	GConfig->SetFloat(
		AudioSectionName,
		MasterVolumeKey,
		AudioOptions.MasterVolume,
		GGameUserSettingsIni
	);

	GConfig->SetFloat(
		AudioSectionName,
		MusicVolumeKey,
		AudioOptions.MusicVolume,
		GGameUserSettingsIni
	);

	GConfig->SetFloat(
		AudioSectionName,
		EffectsVolumeKey,
		AudioOptions.EffectsVolume,
		GGameUserSettingsIni
	);

	GConfig->SetFloat(
		AudioSectionName,
		DialogueVolumeKey,
		AudioOptions.DialogueVolume,
		GGameUserSettingsIni
	);

	GConfig->Flush(false, GGameUserSettingsIni);
}

void UAudioUserSettings::ChangeMasterVolume(float NewVolume)
{
	AudioOptions.MasterVolume = NewVolume;

	UGameplayStatics::SetSoundMixClassOverride(WorldContextObj,
		BaseSoundMix,
		MasterSoundClass,
		NewVolume,
		1.0f,
		0.4f);

	ChangeMusicVolume(AudioOptions.MusicVolume);
	ChangeEffectsVolume(AudioOptions.EffectsVolume);
	ChangeDialogueVolume(AudioOptions.DialogueVolume);
}

void UAudioUserSettings::ChangeMusicVolume(float NewVolume)
{
	AudioOptions.MusicVolume = NewVolume;

	UGameplayStatics::SetSoundMixClassOverride(WorldContextObj,
		BaseSoundMix,
		MusicSoundClass,
		NewVolume * AudioOptions.MasterVolume,
		1.0f,
		0.4f);
}

void UAudioUserSettings::ChangeEffectsVolume(float NewVolume)
{
	AudioOptions.EffectsVolume = NewVolume;

	UGameplayStatics::SetSoundMixClassOverride(WorldContextObj,
		BaseSoundMix,
		EffectsSoundClass,
		NewVolume * AudioOptions.MasterVolume,
		1.0f,
		0.4f);
}

void UAudioUserSettings::ChangeDialogueVolume(float NewVolume)
{
	AudioOptions.DialogueVolume = NewVolume;

	UGameplayStatics::SetSoundMixClassOverride(WorldContextObj,
		BaseSoundMix,
		DialogueSoundClass,
		NewVolume * AudioOptions.MasterVolume,
		1.0f,
		0.4f);
}
