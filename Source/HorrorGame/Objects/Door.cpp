// Copyright 2018 Adam Brząkała

#include "Door.h"

ADoor::ADoor() :
	opened(false)
{
	PrimaryActorTick.bCanEverTick = true;

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	audioComponent->bAutoActivate = false;
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();
	rotationAtStart = GetActorRotation().Yaw;
}

void ADoor::Tick(float DeltaTime)
{
	constexpr float MAX_ANGLE_DELTA = 0.5f;

	Super::Tick(DeltaTime);	

	float targetAngle;
	float currentRotation = wrapAngle(GetActorRotation().Yaw);
	float openSpeed = openDoorAngle / openTime;
	
	if (direction == DoorOpenDirection::Inside) {
		openSpeed = -openSpeed;
		targetAngle = wrapAngle(rotationAtStart - openDoorAngle);
	} else {
		targetAngle = wrapAngle(rotationAtStart + openDoorAngle);
	}
	
	if (opened && !FMath::IsNearlyEqual(currentRotation, targetAngle, MAX_ANGLE_DELTA))
		AddActorLocalRotation(FRotator(0, openSpeed * DeltaTime, 0));
	else if (!opened && !FMath::IsNearlyEqual(currentRotation, rotationAtStart, MAX_ANGLE_DELTA))
		AddActorLocalRotation(FRotator(0, -openSpeed * DeltaTime, 0));
}

void ADoor::OpenDoor(DoorOpenDirection openDirection)
{
	if (openDoorSound && openDoorSound->IsValidLowLevelFast())
	{
		audioComponent->SetSound(openDoorSound);
		audioComponent->Play();
	}

	direction = openDirection;
	opened = true;
}

void ADoor::CloseDoor()
{
	if (closeDoorSound && closeDoorSound->IsValidLowLevelFast())
	{
		audioComponent->SetSound(closeDoorSound);
		audioComponent->Play();
	}

	opened = false;
}

void ADoor::interactFunction(AActor *other)
{
	if (opened)
		CloseDoor();
	else
		openRightDirection(other);
}

void ADoor::openRightDirection(AActor *other)
{
	float angle = getAngleBetweenVectors(other->GetActorForwardVector(), GetActorForwardVector());

	if (FMath::IsWithin(angle, 0.0f, 90.0f))
		OpenDoor(DoorOpenDirection::Outside);
	else
		OpenDoor(DoorOpenDirection::Inside);
}

float ADoor::wrapAngle(float angle)
{
	int fullCircles = angle / 360;
	angle -= fullCircles * 360;
	
	if (angle < 0) {
		angle += 360;
	}

	return angle;
}

float ADoor::getAngleBetweenVectors(const FVector &arg1, const FVector &arg2)
{
	const float radians = acosf(FVector::DotProduct(arg1, arg2));
	return FMath::RadiansToDegrees(radians);
}