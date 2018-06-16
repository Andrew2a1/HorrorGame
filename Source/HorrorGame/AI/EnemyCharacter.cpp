// Copyright 2018 Adam Brzakala

#include "EnemyCharacter.h"
#include "EngineMinimal.h"
#include "../Player/MainCharacter.h"

#include "../Debug/DebugToolbox.h"

AEnemyCharacter::AEnemyCharacter() :
	bSeePlayer(false)
{
	PrimaryActorTick.bCanEverTick = false;

	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("AIPerception"));
	PawnSensor->OnSeePawn.AddDynamic(this, &AEnemyCharacter::OnSeePawn);
}

void AEnemyCharacter::OnSeePawn(APawn *OtherPawn)
{
	AMainCharacter *Player = Cast<AMainCharacter>(OtherPawn);

	if (Player)
	{
		bSeePlayer = true;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemyCharacter::OnEndSeePawn, PawnSensor->SensingInterval + ResetSeeDelay, false);
	}
}

void AEnemyCharacter::OnEndSeePawn()
{
	bSeePlayer = false;
}

bool AEnemyCharacter::SeesPlayer() const
{
	return bSeePlayer;
}