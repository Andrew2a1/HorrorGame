// Copyright 2018 Adam Brząkała

#include "BTService_CheckPlayerInSight.h"

#include "../Player/MainCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

UBTService_CheckPlayerInSight::UBTService_CheckPlayerInSight()
{
	bCreateNodeInstance = true;
}

void UBTService_CheckPlayerInSight::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
	AEnemyAI *EnemyController = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (EnemyController)
	{
		AMainCharacter *player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (player)
		{
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Object>(EnemyController->PlayerKeyID, player);
		}
	}
}
