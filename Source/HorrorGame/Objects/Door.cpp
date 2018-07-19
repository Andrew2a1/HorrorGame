// Copyright 2018 Adam Brzakala

#include "Door.h"
#include "Debug/DebugToolbox.h"

ADoor::ADoor() :
	openTime(DEFAULT_OPEN_DOOR_TIME),
	openDoorAngle(DEFAULT_OPEN_DOOR_ROTATION),
	openRequested(false),
	movementRequested(false)
{
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(itemRoot);
	AudioComponent->bAutoActivate = false;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	rotationAtStart = normalizeAngle(GetActorRotation().Yaw);
}

bool ADoor::LoadDataFromGameSave_Implementation(const UGameSaveData *GameSaveData)
{
	if (GameSaveData == nullptr)
		return false;

	for (const FDoorSaveData &doorData : GameSaveData->DoorsData)
	{
		if (doorData.DoorID == GetName())
		{
			SetActorRotation(doorData.DoorRotation, ETeleportType::TeleportPhysics);
			OpenDirection = doorData.OpenDirection;
			openRequested = doorData.openRequested;
			movementRequested = doorData.movementRequested;
		}
	}

	return true;
}

bool ADoor::SaveDataToGameSave_Implementation(UGameSaveData *GameSaveData) const
{
	if (GameSaveData == nullptr)
		return false;

	FDoorSaveData doorData;
	doorData.DoorID = GetName();
	doorData.DoorRotation = GetActorRotation();
	doorData.OpenDirection = OpenDirection;
	doorData.openRequested = openRequested;
	doorData.movementRequested = movementRequested;
	GameSaveData->DoorsData.Add(doorData);

	return true;
}

void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	

	if (movementRequested)
		performDoorOpen(DeltaTime);
}

void ADoor::performDoorOpen(float DeltaTime)
{
	float targetAngle = getTargetRotation();
	float currentRotation = normalizeAngle(GetActorRotation().Yaw);
	float openSpeed = getOpenSpeed();

	if (needRotationToOpen(currentRotation, targetAngle))
		rotate(openSpeed * DeltaTime);
	else if (needRotationToClose(currentRotation))
		rotate(-openSpeed * DeltaTime);
	else
		endDoorMovement();
}

float ADoor::getTargetRotation() const
{
	if (OpenDirection == DoorOpenDirection::Inside)
		return normalizeAngle(rotationAtStart - openDoorAngle);
	return normalizeAngle(rotationAtStart + openDoorAngle);
}

float ADoor::normalizeAngle(float angle) const
{
	int fullCircles = angle / 360;
	angle -= fullCircles * 360;

	if (angle < 0)
		angle += 360;

	return angle;
}

float ADoor::getOpenSpeed() const
{
	float openSpeed = openDoorAngle / openTime;

	if (OpenDirection == DoorOpenDirection::Inside)
		openSpeed = -openSpeed;

	return openSpeed;
}

inline bool ADoor::needRotationToOpen(float currentRotation, float targetRotation) const
{
	return openRequested && !FMath::IsNearlyEqual(currentRotation, targetRotation, MAX_DOOR_ROTATION_DELTA);
}

inline bool ADoor::needRotationToClose(float currentRotation) const
{
	return !openRequested && !FMath::IsNearlyEqual(currentRotation, rotationAtStart, MAX_DOOR_ROTATION_DELTA);
}

void ADoor::rotate(float angle)
{
	AddActorLocalRotation(FRotator(0, angle, 0));
}

void ADoor::endDoorMovement()
{
	movementRequested = false;

	if (!openRequested)
		playSoundIfValid(closeDoorSound);
}

void ADoor::OpenDoor(DoorOpenDirection openDirection)
{
	playSoundIfValid(openDoorSound);

	OpenDirection = openDirection;
	openRequested = true;
	movementRequested = true;
}

void ADoor::CloseDoor()
{
	openRequested = false;
	movementRequested = true;
}

void ADoor::actionItemUnlocked(AActor *other)
{
	if (openRequested)
		CloseDoor();
	else
		openRightDirection(other);
}

void ADoor::failedUnlock(AActor *other)
{
	playSoundIfValid(lockedDoorSound);
	PRINT(TEXT("You don't have needed items"));
}

void ADoor::succeededUnlock(AActor *other)
{
	PRINT(TEXT("Door unlocked!"));
	actionItemUnlocked(other);
}

void ADoor::openRightDirection(AActor *other)
{
	float angle = getAngleBetweenVectors(other->GetActorForwardVector(), GetActorForwardVector());

	if (FMath::IsWithin(angle, 0.0f, 90.0f))
		OpenDoor(DoorOpenDirection::Outside);
	else
		OpenDoor(DoorOpenDirection::Inside);
}

void ADoor::playSoundIfValid(USoundCue *soundCue)
{
	if (soundCue && soundCue->IsValidLowLevelFast())
	{
		AudioComponent->SetSound(soundCue);
		AudioComponent->Play();
	}
}

float ADoor::getAngleBetweenVectors(const FVector &arg1, const FVector &arg2) const
{
	const float radians = acosf(FVector::DotProduct(arg1, arg2));
	return FMath::RadiansToDegrees(radians);
}
