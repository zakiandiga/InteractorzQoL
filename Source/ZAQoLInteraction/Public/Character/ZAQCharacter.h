/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Utilities/ZAQPlayerStates.h"
#include "ZAQCharacter.generated.h"

class UZAQInteractionHandler;
class UZAQInteractableTargetting;
class UZAQInteractableCollider;
class UZAQInventory;
class UCameraComponent;
class USpringArmComponent;

class UZAQItem;

UCLASS()
class ZAQOLINTERACTION_API AZAQCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AZAQCharacter();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UCameraComponent> PlayerCamera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UZAQInventory> PlayerInventory;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UZAQInteractionHandler> InteractionHandlerComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UZAQInteractableTargetting> InteractableTargettingComponent;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Components")
	TObjectPtr<UZAQInteractableCollider> InteractableDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Player States")
	EZAQPlayerControlStates PlayerStates = EZAQPlayerControlStates::EPCS_Moving;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "ControllerProperties")
	float RotationRate = 400.f;

	void MoveForward(float Value);
	void MoveSide(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	virtual void Jump() override;

	virtual void Interact();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/// <summary>
	/// UseItem() functionality unit test. Should be removed after the inventory functionality developed
	/// </summary>
	UPROPERTY(EditAnywhere, Category = "Test Unit")
	TSubclassOf<UZAQItem> GrabbedItemClass;

	TObjectPtr<UZAQItem> GrabbedItem;

	void UseItemTest();
	//END OF TEST LINES
};
