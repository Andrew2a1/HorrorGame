// Copyright 2018 Adam Brzakala

#pragma once

#include "BehaviorTree/BehaviorTree.h"
#include "Perception/PawnSensingComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class HORRORGAME_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Behavior") UBehaviorTree *behaviorTree;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly) UPawnSensingComponent *PawnSensor;
	UPROPERTY(EditAnywhere, Category = "Pawn Sensing", meta = (ClampMin = "0.0")) 
		float ResetSeeDelay;

private:
	FTimerHandle TimerHandle;
	bool bSeePlayer;

public:
	AEnemyCharacter();

	UFUNCTION() void OnSeePawn(APawn *OtherPawn);
	UFUNCTION() void OnEndSeePawn();

	UFUNCTION() bool SeesPlayer() const;
};
