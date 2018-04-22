// Copyright 2018 Adam Brząkała

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

#include "EngineMinimal.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAI.generated.h"

UCLASS()
class HORRORGAME_API AEnemyAI : public AAIController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UPawnSensingComponent *PawnSensor;
	UPROPERTY(transient) UBlackboardComponent *blackboardComp;
	UPROPERTY(transient) UBehaviorTreeComponent *behaviorTree;

	uint8_t PlayerKeyID;

public:
	AEnemyAI();

	virtual void Possess(APawn *InPawn) override;
	UFUNCTION() void OnSeePawn(APawn *OtherPawn);
};
