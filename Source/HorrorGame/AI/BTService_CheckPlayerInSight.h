// Copyright 2018 Adam Brząkała

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckPlayerInSight.generated.h"

UCLASS()
class HORRORGAME_API UBTService_CheckPlayerInSight : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CheckPlayerInSight();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp,
							uint8* NodeMemory,
							float DeltaSeconds) override;
	
};
