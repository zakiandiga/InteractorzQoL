/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Components/Interaction/ZAQInteractable.h"
#include "ZAQInteractablePickup.generated.h"

class UZAQItem;
/**
 Pickup item example
 */
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Pickup Item", BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQInteractablePickup : public UZAQInteractable
{
	GENERATED_BODY()

public:
	UZAQInteractablePickup();

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
