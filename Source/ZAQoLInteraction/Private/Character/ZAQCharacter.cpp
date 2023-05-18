// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ZAQCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "InputCoreTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/Interaction/ZAQInteractionHandler.h"
#include "Components/Interaction/ZAQInteractableCollider.h"

AZAQCharacter::AZAQCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	InteractionHandlerComponent = CreateDefaultSubobject<UZAQInteractionHandler>(TEXT("Interaction Handler"));
	InteractableTargettingComponent = CreateDefaultSubobject<UZAQInteractableTargetting>(TEXT("Interaction Targetting"));
	InteractableDetector = CreateDefaultSubobject<UZAQInteractableCollider>(TEXT("Interactable Detector"));

	CameraBoom->SetupAttachment(GetRootComponent());
	PlayerCamera->SetupAttachment(CameraBoom);
	InteractableDetector->SetupAttachment(GetRootComponent());

	PlayerCamera->SetAutoActivate(true);

	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritYaw = true;
	CameraBoom->bInheritRoll = true;

	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0, 30.f, 0);
	CameraBoom->TargetOffset = FVector(0, 0, 90.f);

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, RotationRate, 0);
}

void AZAQCharacter::MoveForward(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerStates == EZAQPlayerControlStates::EPCS_Interacting) return;

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	AddMovementInput(ForwardDirection, Value);
}

void AZAQCharacter::MoveSide(float Value)
{
	if (Controller == nullptr) return;
	if (Value == 0) return;
	if (PlayerStates == EZAQPlayerControlStates::EPCS_Interacting) return;

	const FRotator ControllerRotation = GetControlRotation();
	const FRotator YawRotation(0, ControllerRotation.Yaw, 0);
	const FVector SideDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(SideDirection, Value);
}

void AZAQCharacter::Turn(float Value)
{
	if (Value == 0) return;
	if (Controller == nullptr) return;
	if (PlayerStates == EZAQPlayerControlStates::EPCS_Interacting) return;

	AddControllerYawInput(Value);
}

void AZAQCharacter::LookUp(float Value)
{
	if (Value == 0) return;
	if (Controller == nullptr) return;
	if (PlayerStates == EZAQPlayerControlStates::EPCS_Interacting) return;

	AddControllerPitchInput(Value);
}

void AZAQCharacter::Interact()
{
	if (Controller == nullptr) return;
	if (PlayerStates == EZAQPlayerControlStates::EPCS_Interacting) return;

	if (InteractionHandlerComponent == nullptr) return;

	InteractionHandlerComponent->InitiateInteraction();
}

void AZAQCharacter::Jump()
{
	if (Controller == nullptr) return;
	if (PlayerStates == EZAQPlayerControlStates::EPCS_Interacting) return;

	Super::Jump();
}

void AZAQCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AZAQCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AZAQCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	FInputAxisBinding& Forward = PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &AZAQCharacter::MoveForward);
	FInputAxisBinding& Right = PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &AZAQCharacter::MoveSide);
	FInputAxisBinding& LookRight = PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &AZAQCharacter::Turn);
	FInputAxisBinding& LookUp = PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &AZAQCharacter::LookUp);
	FInputActionBinding& Jump = PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AZAQCharacter::Jump);
	FInputActionBinding& Interact = PlayerInputComponent->BindAction(TEXT("Interact"), EInputEvent::IE_Pressed, this, &AZAQCharacter::Interact);
}

