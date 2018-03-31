// Copyright 2018 Adam Brząkała

#pragma once

#include "Engine.h"
#include "../Player/MainCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

/*
if (propellerAudioCue->IsValidLowLevelFast()) {
propellerAudioComponent->SetSound(propellerAudioCue);
}

// Finally play the sound  (outside the constructor)
propellerAudioComponent->Play();

Vector3 directionToTarget = transform.position - enemy.position;
float angel = Vector3.Angel(transform.forward, directionToTarget);
if (Mathf.Abs(angel) > 90)
Debug.Log("target is behind me");
*/

/*
virtual void interact(AActor *actor) PURE_VIRTUAL(InteractiveItem::interact, );
};
*/

enum class DoorOpenDirection
{
	Inside,
	Outside
};

UCLASS()
class HORRORGAME_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere) UAudioComponent *audioComponent;
	UPROPERTY(EditAnywhere) USoundCue *openDoorSound;
	UPROPERTY(EditAnywhere) USoundCue *closeDoorSound;

	UPROPERTY(EditAnywhere) UStaticMesh *doorMesh;
	UPROPERTY(EditAnywhere) UBoxComponent *triggerBox;

	UPROPERTY(EditAnywhere) float openTime;
	UPROPERTY(EditAnywhere) float openDoorAngle;
	
private:
	DoorOpenDirection direction;
	bool isPlayerInDoorRange;
	bool opened;

public:	
	ADoor();
	virtual void Tick(float DeltaTime) override;

	void OnTriggerBoxOverlapStart(AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	void OnTriggerBoxOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void OpenDoor(DoorOpenDirection openDirection);
	void CloseDoor();

protected:
	virtual void BeginPlay() override;
};
