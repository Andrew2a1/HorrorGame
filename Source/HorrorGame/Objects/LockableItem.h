// Copyright 2018 Adam Brzakala

#pragma once

#include "CoreMinimal.h"

#include "Player/MainCharacter.h"
#include "Objects/InteractiveItem.h"

#include "LockableItem.generated.h"

UCLASS()
class HORRORGAME_API ALockableItem : public AInteractiveItem
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "LockableItem") TArray<FName> requiredToUnlock;
	UPROPERTY(EditAnywhere, Category = "LockableItem") bool bIsLocked;

public:
	ALockableItem();
	bool isLocked() const;

protected:
	virtual void interactFunction(AActor *other) override;

	virtual void actionItemUnlocked(AActor *other) PURE_VIRTUAL(ALockableItem::actionItemUnlocked, );
	virtual void failedUnlock(AActor *other) PURE_VIRTUAL(ALockableItem::failedUnlock, );
	virtual void succeededUnlock(AActor *other) PURE_VIRTUAL(ALockableItem::succeededUnlock, );

private:
	void interact(AMainCharacter *player);
	void tryUnlock(AMainCharacter *player);
	
};
	