// Copyright 2018 Adam Brzakala

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

UCLASS()
class HORRORGAME_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(transient) UBlackboardComponent *blackboardComp;
	UPROPERTY(transient) UBehaviorTreeComponent *behaviorTree;

	uint8_t PlayerKeyID;

public:
	AEnemyAI();

	virtual void Possess(APawn *InPawn) override;
};
