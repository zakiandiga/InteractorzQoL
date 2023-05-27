/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#include "Components/Interaction/ZAQInteractablePickup.h"
#include "Item/ZAQItem.h"

UZAQInteractablePickup::UZAQInteractablePickup() : UZAQInteractable()
{
	SetAutoFinish(false);
}

void UZAQInteractablePickup::Interact_Implementation(AActor* InteractingActor)
{
	FString DebugMessage = TEXT("Pickup item is interacting with the player");
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Yellow;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);

	if (!CanPlayerPickup())
	{
		InventoryFullFollowup();
		return;
	}

	InventoryAvailableFollowup();
}

void UZAQInteractablePickup::InventoryFullFollowup()
{
	FString DebugMessage = TEXT("Player inventory is full, nothing happened!");
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Red;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);

	FinishedInteraction();
}

void UZAQInteractablePickup::InventoryAvailableFollowup()
{
	FString DebugMessage = TEXT("Player pickup the item, now destroy!");
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Green;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);

	FinishedInteraction();
	GetOwner()->Destroy();
}

