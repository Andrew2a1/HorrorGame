// Copyright 2018 Adam Brząkała

#include "BasicSaveGame.h"
#include "EngineUtils.h"

#include "../Objects/Door.h"
#include "../Player/MainCharacter.h"

UBasicSaveGame *UBasicSaveGame::CreateInstance()
{
	return Cast<UBasicSaveGame>(UGameplayStatics::CreateSaveGameObject(UBasicSaveGame::StaticClass()));
}

UBasicSaveGame *UBasicSaveGame::LoadGame(const FString &SlotName, int UserIndex)
{
	if (SlotName.IsEmpty())
		return nullptr;
	return Cast<UBasicSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
}

bool UBasicSaveGame::SaveGame(const FString &SlotName, int UserIndex)
{
	if (SlotName.IsEmpty())
		return false;
	return UGameplayStatics::SaveGameToSlot(this, SlotName, UserIndex);
}

void UBasicSaveGame::FillSavegameWithData(UWorld *World)
{
	DoorInformations.Empty();

	for (TActorIterator<ADoor> ActorItr(World); ActorItr; ++ActorItr)
	{
		ADoor *Component = *ActorItr;
		DoorInformations.Add(Component->GetDoorState());
	}

	for (TActorIterator<AMainCharacter> ActorItr(World); ActorItr; ++ActorItr)
	{
		AMainCharacter *Player = *ActorItr;
		MainCharacterInfo = Player->GetPlayerState();
	}
}

void UBasicSaveGame::LoadDataToActors(UWorld *World) const
{
	for (TActorIterator<ADoor> ActorItr(World); ActorItr; ++ActorItr)
	{
		for (const FDoorInformation &DoorInfo : DoorInformations)
		{
			if (DoorInfo.DoorName == (*ActorItr)->GetName())
			{
				(*ActorItr)->LoadDoorState(DoorInfo);
			}
		}	
	}

	for (TActorIterator<AMainCharacter> ActorItr(World); ActorItr; ++ActorItr)
	{
		AMainCharacter *Player = *ActorItr;
		Player->LoadPlayerState(MainCharacterInfo);
	}
}