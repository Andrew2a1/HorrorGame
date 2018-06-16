// Copyright 2018 Adam Brzakala

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
	ChangeMasterVolume(VolumeSettings.Master);
}

bool UAudioUserSettings::LoadSettings()
{
	if (!GConfig) 
		return false;

	VolumeSettings.Master = GetAudioVolumeForKey(MasterVolumeKey);
	VolumeSettings.Music = GetAudioVolumeForKey(MusicVolumeKey);
	VolumeSettings.Effects = GetAudioVolumeForKey(EffectsVolumeKey);
	VolumeSettings.Dialogue = GetAudioVolumeForKey(DialogueVolumeKey);

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

	SaveAudioVolumeForKey(MasterVolumeKey, VolumeSettings.Master);
	SaveAudioVolumeForKey(MusicVolumeKey, VolumeSettings.Music);
	SaveAudioVolumeForKey(EffectsVolumeKey, VolumeSettings.Effects);
	SaveAudioVolumeForKey(DialogueVolumeKey, VolumeSettings.Dialogue);

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
	VolumeSettings.Master = NewVolume;
	SetVolumeForSoundClass(SoundClasses.Master, NewVolume);

	ChangeMusicVolume(VolumeSettings.Music);
	ChangeEffectsVolume(VolumeSettings.Effects);
	ChangeDialogueVolume(VolumeSettings.Dialogue);
}

void UAudioUserSettings::ChangeMusicVolume(float NewVolume)
{
	VolumeSettings.Music = NewVolume;
	SetVolumeForSoundClass(SoundClasses.Music, NewVolume * VolumeSettings.Master);
}

void UAudioUserSettings::ChangeEffectsVolume(float NewVolume)
{
	VolumeSettings.Effects = NewVolume;
	SetVolumeForSoundClass(SoundClasses.Effects, NewVolume * VolumeSettings.Master);
}

void UAudioUserSettings::ChangeDialogueVolume(float NewVolume)
{
	VolumeSettings.Dialogue = NewVolume;
	SetVolumeForSoundClass(SoundClasses.Dialogue, NewVolume * VolumeSettings.Master);
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
