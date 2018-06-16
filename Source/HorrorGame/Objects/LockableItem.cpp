// Copyright 2018 Adam Brzakala

#include "LockableItem.h"

ALockableItem::ALockableItem() :
	bIsLocked(false)
{

}

bool ALockableItem::isLocked() const
{
	return bIsLocked;
}

void ALockableItem::interactFunction(AActor *other)
{
	AMainCharacter *player = Cast<AMainCharacter>(other);

	if (player)
		interact(player);
}

void ALockableItem::interact(AMainCharacter *player)
{
	if (bIsLocked)
		tryUnlock(player);
	else
		actionItemUnlocked(player);
}

void ALockableItem::tryUnlock(AMainCharacter *player)
{
	if (!bIsLocked) return;

	for (auto &item : requiredToUnlock)
		if (!player->hasItemInEquipment(item))
			return failedUnlock(player);

	bIsLocked = false;
	succeededUnlock(player);
}