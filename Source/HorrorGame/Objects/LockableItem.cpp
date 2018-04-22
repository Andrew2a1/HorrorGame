// Copyright 2018 Adam Brząkała

#include "LockableItem.h"

ALockableItem::ALockableItem() :
	bIsLocked(true)
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
	{
		if (bIsLocked)
			tryUnlock(player);
		else
			actionItemUnlocked(other);
	}
}

void ALockableItem::tryUnlock(AMainCharacter *player)
{
	if (!bIsLocked) return;

	for (auto &item : requiredToUnlock)
		if (!player->hasItemInEquipment(item))
			return failedUnlock(player);

	bIsLocked = false;
	return succeededUnlock(player);
}