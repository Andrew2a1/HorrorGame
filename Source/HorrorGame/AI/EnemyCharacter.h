// Copyright 2018 Adam Brząkała

#pragma once

#include "BehaviorTree/BehaviorTree.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class HORRORGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Behavior") UBehaviorTree *behaviorTree;

public:
	AEnemyCharacter();
};
