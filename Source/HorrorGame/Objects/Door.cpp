// Copyright 2018 Adam Brząkała

#include "Door.h"

ADoor::ADoor() :
	isPlayerInDoorRange(false),
	opened(false)
{
	PrimaryActorTick.bCanEverTick = true;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->bAutoActivate = false;

	doorMesh = CreateDefaultSubobject<UStaticMesh>(TEXT("DoorMesh"));

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	/*triggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnTriggerBoxOverlapStart);
	triggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnTriggerBoxOverlapStart);*/
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADoor::Tick(float DeltaTime)
{
	constexpr float MAX_ANGLE_DELTA = 1;

	Super::Tick(DeltaTime);

	FRotator currentRotation = GetActorRotation();
	float openSpeed = openDoorAngle / openTime;
	float realAngle = openDoorAngle;

	if (direction == DoorOpenDirection::Inside)
	{
		openSpeed = -openSpeed;
		realAngle = -realAngle;
	}

	if (opened && FMath::Abs(realAngle - currentRotation.Yaw) > MAX_ANGLE_DELTA)
	{
		AddActorLocalRotation(FRotator(0, openSpeed * DeltaTime, 0));
	}
	else if (!opened && FMath::Abs(currentRotation.Yaw) < MAX_ANGLE_DELTA)
	{
		AddActorLocalRotation(FRotator(0, openSpeed * DeltaTime, 0));
	}
}

void ADoor::OnTriggerBoxOverlapStart(AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if (Cast<AMainCharacter>(OtherActor))
		isPlayerInDoorRange = true;
}

void ADoor::OnTriggerBoxOverlapEnd(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMainCharacter>(OtherActor))
		isPlayerInDoorRange = false;
}

void ADoor::OpenDoor(DoorOpenDirection openDirection)
{
	direction = openDirection;
	opened = true;
}

void ADoor::CloseDoor()
{
	opened = false;
}
