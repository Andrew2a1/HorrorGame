// Copyright 2018 Adam Brz�ka�a

#include "MainCharacter.h"

AMainCharacter::AMainCharacter() :
	sprintModificator(1.5f),
	MaxPlayerRange(250.0f),
	prevPointerTarget(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;

	EyeView = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	EyeView->SetupAttachment(GetCapsuleComponent());
	EyeView->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	EyeView->bUsePawnControlRotation = true;

	flashlight = CreateDefaultSubobject<AFlashlight>(TEXT("Flashlight"));

	GetMesh()->SetOwnerNoSee(true);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if (World)
	{
		flashlight = World->SpawnActor<AFlashlight>(FlashlightBlueprint);
		flashlight->AttachToComponent(EyeView, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		flashlight->SetActorRelativeLocation(FVector(18, 12, -8));
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AInteractiveItem *item = Cast<AInteractiveItem>(mouseTraceHitResult());

	if (prevPointerTarget && prevPointerTarget != item) {
		prevPointerTarget->OnEndPointingAt();
	}

	if (item && item != prevPointerTarget) {
		item->OnStartPointingAt();
	}

	prevPointerTarget = item;
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

	/*PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMainCharacter::startCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMainCharacter::stopCrouch);*/

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMainCharacter::interact);
	PlayerInputComponent->BindAction("Flashlight", IE_Pressed, this, &AMainCharacter::toggleFlashlight);

	PlayerInputComponent->BindAction("PrintDebug", IE_Pressed, this, &AMainCharacter::printDebug);
}

void AMainCharacter::addToEquipment(const FItemDescriptor &item)
{
	collectedItems.Add(item);
}

bool AMainCharacter::isItemInEquipment(const FName &itemName)
{
	for (auto &item : collectedItems)
	{
		if (itemName == item.ID)
			return true;
	}

	return false;
}

AActor *AMainCharacter::mouseTraceHitResult()
{
	FHitResult outHit;
	FCollisionQueryParams collisionParams;

	FVector forwardVector = EyeView->GetForwardVector();
	FVector traceStart = EyeView->GetComponentLocation();
	FVector traceEnd = forwardVector * MaxPlayerRange + traceStart;

	bool isHit = GetWorld()->LineTraceSingleByChannel(outHit, traceStart, traceEnd, ECC_WorldStatic, collisionParams);

	if (isHit && outHit.bBlockingHit && (outHit.GetActor() != this))
	{
		return outHit.GetActor();
	}

	return nullptr;
}

bool AMainCharacter::isActorInPlayerRange(AActor *target)
{
	return MaxPlayerRange >= FVector::Distance(target->GetActorLocation(), GetActorLocation());
}

void AMainCharacter::moveForward(float value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);

	AddMovementInput(direction, value);
}

void AMainCharacter::moveRight(float value)
{
	FVector direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);

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
	GetCharacterMovement()->MaxWalkSpeed = BASIC_CHARACTER_SPEED * sprintModificator;
}

void AMainCharacter::stopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = BASIC_CHARACTER_SPEED;
}

/*void AMainCharacter::startCrouch()
{
	if (CanCrouch())
		Crouch();
}

void AMainCharacter::stopCrouch()
{
	UnCrouch();
}*/

void AMainCharacter::interact()
{
	if (prevPointerTarget)
	{
		prevPointerTarget->interact(this);
	}
}

void AMainCharacter::toggleFlashlight()
{
	if (flashlight)
		flashlight->toggleLight();
}

void AMainCharacter::printDebug()
{
	if (GEngine)
	{
		for (auto& desc : collectedItems)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, desc.ID.ToString());
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("EQUIPMENT: "));
	}
}
		