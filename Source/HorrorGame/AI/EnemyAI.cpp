// Copyright 2018 Adam Brząkała

#include "EnemyAI.h"
#include "EnemyCharacter.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

AEnemyAI::AEnemyAI()
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	behaviorTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent >(TEXT("AIPerception"));

	PawnSensor->OnSeePawn.AddDynamic(this, &AEnemyAI::OnSeePawn);
}

void AEnemyAI::Possess(APawn *InPawn)
{
	Super::Possess(InPawn);

	AEnemyCharacter *enemy = Cast<AEnemyCharacter>(InPawn);

	if (enemy && enemy->behaviorTree)
	{
		blackboardComp->InitializeBlackboard(*enemy->behaviorTree->BlackboardAsset);
		PlayerKeyID = blackboardComp->GetKeyID("Target");
		behaviorTree->StartTree(*enemy->behaviorTree);
	}
}

void AEnemyAI::OnSeePawn(APawn *OtherPawn)
{
	FString message = TEXT("Saw Actor ") + OtherPawn->GetName();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, message);
}