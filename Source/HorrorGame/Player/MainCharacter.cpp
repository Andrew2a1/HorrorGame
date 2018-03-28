// Copyright 2018 Adam Brz¹ka³a

#include "MainCharacter.h"

AMainCharacter::AMainCharacter() :
	sprintModificator(1.5f)
{
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	FPSCameraComponent->bUsePawnControlRotation = true;

	GetMesh()->SetOwnerNoSee(true);
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

void AMainCharacter::startCrouch()
{
	if (CanCrouch())
		Crouch();
}

void AMainCharacter::stopCrouch()
{
	UnCrouch();
}