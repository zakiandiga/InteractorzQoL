// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Interaction/ZAQInteractable.h"
#include "ZAQPickupItem.generated.h"

class UZAQItem;
/**
 Pickup item example
 */
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Pickup Item", BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQPickupItem : public UZAQInteractable
{
	GENERATED_BODY()

public:
	UZAQPickupItem();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	UZAQItem* Item;

public:
	virtual void Interact_Implementation(AActor* InteractingActor) override;
	
	void InventoryFullFollowup();
	void InventoryAvailableFollowup();

	//temporary test functions
	UFUNCTION(BlueprintCallable, Category = "Pickup Item")
	bool CanPlayerPickup() { return !bPlayerInventoryFull; }

	UPROPERTY(EditAnywhere, Category = "Pickup Item")
	bool bPlayerInventoryFull = false;
};
