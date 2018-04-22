// Copyright 2018 Adam Brząkała

#include "BTTask_MoveToPlayer.h"

#include "../Player/MainCharacter.h"
#include "EnemyCharacter.h"
#include "EnemyAI.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

#include "EngineMinimal.h"

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAI *enemyPC = Cast<AEnemyAI>(OwnerComp.GetAIOwner());

	if (enemyPC)
	{
		AMainCharacter *player = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (player)
		{
			enemyPC->MoveToActor(player, 5.0f, true, true, true, 0, true);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}