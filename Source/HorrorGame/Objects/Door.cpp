// Copyright 2018 Adam Brząkała

#include "Door.h"
#include "Debug/DebugToolbox.h"

ADoor::ADoor() :
	opened(false),
	movementRequested(false)
{
	PrimaryActorTick.bCanEverTick = true;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->bAutoActivate = false;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	rotationAtStart = normalizeAngle(GetActorRotation().Yaw);
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
	if (direction == DoorOpenDirection::Inside)
		return normalizeAngle(rotationAtStart - openDoorAngle);
	return normalizeAngle(rotationAtStart + openDoorAngle);
}

float ADoor::getOpenSpeed() const
{
	float openSpeed = openDoorAngle / openTime;

	if (direction == DoorOpenDirection::Inside)
		openSpeed = -openSpeed;

	return openSpeed;
}

inline bool ADoor::needRotationToOpen(float currentRotation, float targetRotation) const
{
	return opened && !FMath::IsNearlyEqual(currentRotation, targetRotation, MaxDoorRotationDelta);
}

inline bool ADoor::needRotationToClose(float currentRotation) const
{
	return !opened && !FMath::IsNearlyEqual(currentRotation, rotationAtStart, MaxDoorRotationDelta);
}

void ADoor::rotate(float angle)
{
	AddActorLocalRotation(FRotator(0, angle, 0));
}

void ADoor::endDoorMovement()
{
	movementRequested = false;

	if (opened == false)
		playSoundIfValid(closeDoorSound);
}

void ADoor::OpenDoor(DoorOpenDirection openDirection)
{
	playSoundIfValid(openDoorSound);

	direction = openDirection;
	opened = true;
	movementRequested = true;
}

void ADoor::CloseDoor()
{
	opened = false;
	movementRequested = true;
}

FDoorInformation ADoor::GetDoorState() const
{
	FDoorInformation info;

	info.DoorName = GetName();
	info.DoorRotation = GetActorRotation();
	info.Open = opened;
	info.RequestMovement = movementRequested;

	return info;
}

void ADoor::LoadDoorState(const FDoorInformation &DoorState)
{
	SetActorRotation(DoorState.DoorRotation, ETeleportType::TeleportPhysics);
	opened = DoorState.Open;
	movementRequested = DoorState.RequestMovement;
}

void ADoor::actionItemUnlocked(AActor *other)
{
	if (opened)
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
		audioComponent->SetSound(soundCue);
		audioComponent->Play();
	}
}

float ADoor::getAngleBetweenVectors(const FVector &arg1, const FVector &arg2) const
{
	const float radians = acosf(FVector::DotProduct(arg1, arg2));
	return FMath::RadiansToDegrees(radians);
}

float ADoor::normalizeAngle(float angle) const
{
	int fullCircles = angle / 360;
	angle -= fullCircles * 360;

	if (angle < 0)
		angle += 360;

	return angle;
}
