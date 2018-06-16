// Copyright 2018 Adam Brzakala

#include "EnemyAI.h"
#include "EnemyCharacter.h"
#include "Player/MainCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AEnemyAI::AEnemyAI()
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	behaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
}

void AEnemyAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);
	
	AEnemyCharacter *enemy = Cast<AEnemyCharacter>(InPawn);

	if (enemy && enemy->behaviorTree)
	{
		blackboardComp->InitializeBlackboard(*enemy->behaviorTree->BlackboardAsset);
		behaviorTree->StartTree(*enemy->behaviorTree);
	}
}