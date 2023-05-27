/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#include "Components/Inventory/ZAQInventory.h"
#include "Math/UnrealMathUtility.h"
#include "Item/ZAQItem.h"

UZAQInventory::UZAQInventory()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UZAQInventory::AddToInventory(UZAQItem* ItemToAdd, int32 QuantityToAdd)
{	
	FZAQItemSlot* outSlot = nullptr;
	if (ItemToAdd->IsStackable() || ItemAvailable(ItemToAdd, *outSlot))
	{
		AddExistingEntryQuantity(outSlot, QuantityToAdd);	
		return;
	}

	AddNewEntry(ItemToAdd, QuantityToAdd);
}

void UZAQInventory::AddNewEntry(UZAQItem* ItemToAdd, int32 QuantityToAdd)
{
	int32 EmptySlot = 0;
	if (!EmptySlotAvailable(EmptySlot))
	{
		OnRetrieveItemFailed.Broadcast(EZAQRetrieveFailedType::ERF_FULLINVENTORY, ItemToAdd, QuantityToAdd);
		return;
	}
	
	FZAQItemSlot* NewEntry = new FZAQItemSlot();
	NewEntry->SetItem(ItemToAdd);	
	int32 ClampedQuantity = FMath::Clamp(QuantityToAdd, 0, GetSlotStackLimit(NewEntry));	
	NewEntry->ChangeQuantity(ClampedQuantity);
	InventorySlots.Add(*NewEntry);

	OnAddingItemSuccess.Broadcast(ItemToAdd, QuantityToAdd);
}

void UZAQInventory::AddExistingEntryQuantity(FZAQItemSlot* SlotToModify, int32 QuantityToModify)
{
	UZAQItem* ItemHandled = SlotToModify->GetItem();
	int32 AvailableStack = GetRemainingSlotStackAvailable(SlotToModify);
	int32 LeftoverQuantity = QuantityToModify - AvailableStack;

	if(LeftoverQuantity > 0)
	{
		OnRetrieveItemFailed.Broadcast(EZAQRetrieveFailedType::ERF_FULLSLOT, ItemHandled, LeftoverQuantity);
	}
		
	if (AvailableStack > 0)
	{
		SlotToModify->ChangeQuantity(AvailableStack);	
		OnAddingItemSuccess.Broadcast(ItemHandled, QuantityToModify);
	}
}

bool UZAQInventory::TryRemoveFromInventory(UZAQItem* ItemToRemove, int32 QuantityToRemove)
{
	FZAQItemSlot* ItemContainingSlot = nullptr;
	if (!ItemAvailable(ItemToRemove, *ItemContainingSlot))
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("Error: %s NOT found in the inventory!"), *ItemToRemove->GetItemName().ToString());
#endif
		OnRemoveItemFailed.Broadcast(EZAQRemoveFailedType::ERF_NOTFOUND, ItemToRemove);
		return false;
	}
	
	if (ItemContainingSlot->GetItemQuantity() < QuantityToRemove)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("Error: Inventory doesn't have enough %s!"), *ItemToRemove->GetItemName().ToString());
#endif
		OnRemoveItemFailed.Broadcast(EZAQRemoveFailedType::ERF_NOTENOUGH, ItemToRemove);
		return false;
	}

	ItemContainingSlot->ChangeQuantity(-QuantityToRemove);

	if (ItemContainingSlot->GetItemQuantity() <= 0)
	{
		ItemContainingSlot = nullptr;
	}

	OnRemovingItemSuccess.Broadcast(ItemToRemove, QuantityToRemove);
	return true;
}

bool UZAQInventory::ItemAvailable(UZAQItem* ItemToCheck, FZAQItemSlot& outItemSlot) const
{
	for (int i = 0; i < InventorySlots.Num(); i++)
	{
		if (InventorySlots[i].GetItem() == ItemToCheck)
		{
			outItemSlot = InventorySlots[i];
			return true;
		}
	}

	return false;
}

int32 UZAQInventory::GetSlotStackLimit(FZAQItemSlot* SlotToCheck) const
{
	return bIsStorage ? StorageStackLimitValue : SlotToCheck->GetItem()->GetStackLimit();
}

int32 UZAQInventory::GetRemainingSlotStackAvailable(FZAQItemSlot* SlotToCheck) const
{
	return GetSlotStackLimit(SlotToCheck) - SlotToCheck->GetItemQuantity();
}

bool UZAQInventory::EmptySlotAvailable(int32 outAmount) const
{
	outAmount = GetMaximumSlot() - GetOccupiedSlot();
	return outAmount <= GetMaximumSlot();
}

void UZAQInventory::RetrieveItem(UZAQItem* ItemToRetrieve, int32 QuantityToRetrieve)
{
	AddToInventory(ItemToRetrieve, QuantityToRetrieve);
}

void UZAQInventory::DropItem(UZAQItem* ItemToDrop, int32 QuantityToDrop)
{
	if (TryRemoveFromInventory(ItemToDrop, QuantityToDrop))
	{
		ItemToDrop->SpawnItem(GetOwner());
	}
}

void UZAQInventory::ConsumeItem(UZAQItem* ItemToConsume, int32 QuantityToConsume)
{
	if (TryRemoveFromInventory(ItemToConsume, QuantityToConsume))
	{
		ItemToConsume->UseItem(GetOwner());
	}
}

void UZAQInventory::ForceRemoveItem(UZAQItem* ItemToRemove, int32 QuantityToRemove)
{
	//Force remove functionalities, bypass Remove Item procedure
}





