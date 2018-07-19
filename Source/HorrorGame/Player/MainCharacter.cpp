// Copyright 2018 Adam Brzakala

#include "MainCharacter.h"
#include "Debug/DebugToolbox.h"

AMainCharacter::AMainCharacter() :
	sprintModificator(1.5f),
	maxPlayerRange(250.0f),
	lastPointerTarget(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	EyeView = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	EyeView->SetupAttachment(GetCapsuleComponent());
	EyeView->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	EyeView->bUsePawnControlRotation = true;

	FlashlightSpawnLocation = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("FlashlightLocation"));
	FlashlightSpawnLocation->SetupAttachment(EyeView);

	GetMesh()->SetOwnerNoSee(true);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld *World = GetWorld();

	if (World && FlashlightBlueprint.Get())
	{
		flashlight = World->SpawnActor<AFlashlight>(FlashlightBlueprint);
		flashlight->AttachToComponent(FlashlightSpawnLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AInteractiveItem *pointerTarget = Cast<AInteractiveItem>(getPointerTarget());

	if (userEndedPointingAtItem(pointerTarget))
		lastPointerTarget->OnEndPointingAt();

	if (userStartedPointingAtItem(pointerTarget))
		pointerTarget->OnStartPointingAt();

	lastPointerTarget = pointerTarget;
}

AActor *AMainCharacter::getPointerTarget()
{
	FHitResult outHit;
	FCollisionQueryParams collisionParams;

	FVector forwardVector = EyeView->GetForwardVector();
	FVector traceStart = EyeView->GetComponentLocation();
	FVector traceEnd = forwardVector * maxPlayerRange + traceStart;

	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, traceStart, traceEnd, ECC_WorldStatic, collisionParams);

	if (isHit && outHit.bBlockingHit && (outHit.GetActor() != this))
		return outHit.GetActor();
	return nullptr;
}

bool AMainCharacter::userEndedPointingAtItem(const AInteractiveItem *item) const
{
	return lastPointerTarget && lastPointerTarget != item;
}

bool AMainCharacter::userStartedPointingAtItem(const AInteractiveItem *item) const
{
	return item && item != lastPointerTarget;
}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::moveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::startJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMainCharacter::stopJump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMainCharacter::startSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMainCharacter::stopSprint);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::startCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::stopCrouch);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::interact);
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &AMainCharacter::toggleFlashlight);

	PlayerInputComponent->BindAction("PrintDebug", IE_Pressed, this, &AMainCharacter::printDebug);
}

void AMainCharacter::addToEquipment(const FItemDescriptor &item)
{
	collectedItems.Add(item);
}

bool AMainCharacter::hasItemInEquipment(const FName &itemName)
{
	for (auto &item : collectedItems)
		if (itemName == item.ID)
			return true;
	return false;
}

bool AMainCharacter::LoadDataFromGameSave_Implementation(const UGameSaveData *GameSaveData)
{
	if (GameSaveData == nullptr)
		return false;

	SetActorTransform(GameSaveData->PlayerTransform,
		false,
		nullptr,
		ETeleportType::TeleportPhysics);

	return true;
}

bool AMainCharacter::SaveDataToGameSave_Implementation(UGameSaveData *GameSaveData) const
{
	if (GameSaveData == nullptr)
		return false;

	GameSaveData->PlayerTransform = GetActorTransform();
	return true;
}

void AMainCharacter::moveForward(float value)
{
	AddMovementInput(GetActorForwardVector(), value);
}

void AMainCharacter::moveRight(float value)
{
	FVector direction = GetActorForwardVector().RotateAngleAxis(90, FVector(0, 0, 1));
	AddMovementInput(direction, value);
}

void AMainCharacter::startJump()
{
	bPressedJump = true;
}

void AMainCharacter::stopJump()
{
	bPressedJump = false;
}

void AMainCharacter::startSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultCharacterSpeed * sprintModificator;
}

void AMainCharacter::stopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultCharacterSpeed;
}

void AMainCharacter::startCrouch()
{
	if (CanCrouch())
		Crouch();
}

void AMainCharacter::stopCrouch()
{
	UnCrouch();
}

void AMainCharacter::interact()
{
	if (lastPointerTarget)
		lastPointerTarget->interact(this);
}

void AMainCharacter::toggleFlashlight()
{
	if (flashlight)
		flashlight->toggleLight();
}

bool AMainCharacter::isActorInPlayerRange(AActor *target)
{
	return maxPlayerRange >= FVector::Distance(target->GetActorLocation(), GetActorLocation());
}

void AMainCharacter::printDebug()
{
	if (GEngine)
	{
		for (auto& desc : collectedItems)
		{
			PRINT(desc.ID.ToString());
		}
		PRINT(TEXT("EQUIPMENT: "));
	}
}