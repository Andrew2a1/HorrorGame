// Copyright 2018 Adam Brząkała

#include "AudioUserSettings.h"

UAudioUserSettings::UAudioUserSettings() :
	UAudioUserSettings(nullptr, FSoundClasses())
{

}

UAudioUserSettings::UAudioUserSettings(USoundMix *BaseSoundMix, const FSoundClasses &SoundClasses)
{
	Init(BaseSoundMix, SoundClasses);
}

void UAudioUserSettings::Init(USoundMix *BaseSoundMix, const FSoundClasses &SoundClasses)
{
	WorldContextObj = nullptr;

	this->BaseSoundMix = BaseSoundMix;
	this->SoundClasses = SoundClasses;
}

void UAudioUserSettings::ChangeWorld(UObject *WorldContextObject)
{
	WorldContextObj = WorldContextObject;

	UGameplayStatics::SetBaseSoundMix(WorldContextObj, BaseSoundMix);
	ChangeMasterVolume(VolumeSettings.MasterVolume);
}

bool UAudioUserSettings::LoadSettings()
{
	if (!GConfig) 
		return false;

	VolumeSettings.MasterVolume = GetAudioVolumeForKey(MasterVolumeKey);
	VolumeSettings.MusicVolume = GetAudioVolumeForKey(MusicVolumeKey);
	VolumeSettings.EffectsVolume = GetAudioVolumeForKey(EffectsVolumeKey);
	VolumeSettings.DialogueVolume = GetAudioVolumeForKey(DialogueVolumeKey);

	return true;
}

float UAudioUserSettings::GetAudioVolumeForKey(const TCHAR *Key) const
{
	float result;

	if (!GConfig->GetFloat(AudioSectionName, Key, result, GGameUserSettingsIni))
		return 0;

	return result;
}

void UAudioUserSettings::SaveSettings() const
{
	if (!GConfig)
		return;

	SaveAudioVolumeForKey(MasterVolumeKey, VolumeSettings.MasterVolume);
	SaveAudioVolumeForKey(MusicVolumeKey, VolumeSettings.MusicVolume);
	SaveAudioVolumeForKey(EffectsVolumeKey, VolumeSettings.EffectsVolume);
	SaveAudioVolumeForKey(DialogueVolumeKey, VolumeSettings.DialogueVolume);

	GConfig->Flush(false, GGameUserSettingsIni);
}

void UAudioUserSettings::SaveAudioVolumeForKey(const TCHAR *Key, float Volume) const
{
	GConfig->SetFloat(
		AudioSectionName,
		Key,
		Volume,
		GGameUserSettingsIni
	);
}

void UAudioUserSettings::ChangeMasterVolume(float NewVolume)
{
	VolumeSettings.MasterVolume = NewVolume;
	SetVolumeForSoundClass(SoundClasses.MasterSoundClass, NewVolume);

	ChangeMusicVolume(VolumeSettings.MusicVolume);
	ChangeEffectsVolume(VolumeSettings.EffectsVolume);
	ChangeDialogueVolume(VolumeSettings.DialogueVolume);
}

void UAudioUserSettings::ChangeMusicVolume(float NewVolume)
{
	VolumeSettings.MusicVolume = NewVolume;
	SetVolumeForSoundClass(SoundClasses.MusicSoundClass, NewVolume * VolumeSettings.MasterVolume);
}

void UAudioUserSettings::ChangeEffectsVolume(float NewVolume)
{
	VolumeSettings.EffectsVolume = NewVolume;
	SetVolumeForSoundClass(SoundClasses.EffectsSoundClass, NewVolume * VolumeSettings.MasterVolume);
}

void UAudioUserSettings::ChangeDialogueVolume(float NewVolume)
{
	VolumeSettings.DialogueVolume = NewVolume;
	SetVolumeForSoundClass(SoundClasses.DialogueSoundClass, NewVolume * VolumeSettings.MasterVolume);
}

void UAudioUserSettings::SetVolumeForSoundClass(USoundClass *SoundClass, float Volume)
{
	UGameplayStatics::SetSoundMixClassOverride(WorldContextObj,
		BaseSoundMix,
		SoundClass,
		Volume,
		DefaultSoundPitch,
		DefaultSoundFadeInTime);
}
