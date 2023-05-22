// Copyright Zaki Agraraharja. All Rights Reserved.


#include "Components/Inventory/ZAQInventory.h"
#include "Item/ZAQItem.h"

// Sets default values for this component's properties
UZAQInventory::UZAQInventory()
{
	PrimaryComponentTick.bCanEverTick = false;


}

void UZAQInventory::AddToInventory(UZAQItem* ItemToAdd, int32 QuantityToAdd)
{	
	FZAQItemSlot* outSlot = nullptr;
	if (ItemAvailable(ItemToAdd, *outSlot))
	{
		ModifyExistingEntryQuantity(outSlot, QuantityToAdd);	
		return;
	}

	AddNewEntry(ItemToAdd, QuantityToAdd);
}

void UZAQInventory::AddNewEntry(UZAQItem* ItemToAdd, int32 QuantityToAdd)
{
	int32 EmptySlot = 0;
	if (!EmptySlotAvailable(EmptySlot))
	{
		OnRetrieveItemFailed.Broadcast(EZAQRetrieveFailedType::ERF_FULLINVENTORY, ItemToAdd);
		return;
	}
	
	FZAQItemSlot* NewEntry = new FZAQItemSlot();
	NewEntry->SetItem(ItemToAdd);
	NewEntry->ChangeQuantity(QuantityToAdd);
	InventorySlots.Add(*NewEntry);

	OnAddingItemSuccess.Broadcast(ItemToAdd, QuantityToAdd);
}

void UZAQInventory::ModifyExistingEntryQuantity(FZAQItemSlot* SlotToModify, int32 QuantityToModify)
{
	UZAQItem* ItemHandled = SlotToModify->GetItem();
	if (SlotToModify->GetItemQuantity() + QuantityToModify >= ItemHandled->GetStackLimit())
	{
		OnRetrieveItemFailed.Broadcast(EZAQRetrieveFailedType::ERF_FULLSLOT, ItemHandled);
		return;
	}
		
	SlotToModify->ChangeQuantity(QuantityToModify);	

	OnAddingItemSuccess.Broadcast(ItemHandled, QuantityToModify);
}

void UZAQInventory::RemoveFromInventory(UZAQItem* ItemToRemove, int32 QuantityToRemove)
{
	FZAQItemSlot* ItemContainingSlot = nullptr;
	if (!ItemAvailable(ItemToRemove, *ItemContainingSlot))
	{
		UE_LOG(LogTemp, Error, TEXT("Error: %s NOT found in the inventory!"), *ItemToRemove->GetName().ToString());
		OnRemoveItemFailed.Broadcast(EZAQRemoveFailedType::ERF_NOTFOUND, ItemToRemove);
		return;
	}
	
	if (ItemContainingSlot->GetItemQuantity() < QuantityToRemove)
	{
		UE_LOG(LogTemp, Error, TEXT("Error: Inventory doesn't have enough %s!"), *ItemToRemove->GetName().ToString());
		OnRemoveItemFailed.Broadcast(EZAQRemoveFailedType::ERF_NOTENOUGH, ItemToRemove);
		return;
	}

	ItemContainingSlot->ChangeQuantity(-QuantityToRemove);

	if (ItemContainingSlot->GetItemQuantity() <= 0)
	{
		ItemContainingSlot = nullptr;
	}

	OnRemovingItemSuccess.Broadcast(ItemToRemove, QuantityToRemove);
}

bool UZAQInventory::ItemAvailable(UZAQItem* ItemToCheck, FZAQItemSlot& outItemSlot) const
{
	if (ItemToCheck == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("ItemAvailable() return false because there's no ItemToCheck"));
		return false;
	}
	
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
	return bOverrideStackLimit ? OverridedStackLimitValue : SlotToCheck->GetItem()->GetStackLimit();
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
	if (ItemToRetrieve == nullptr) return;

	AddToInventory(ItemToRetrieve, QuantityToRetrieve);
}

void UZAQInventory::DropItem(UZAQItem* ItemToDrop, int32 QuantityToDrop)
{
	//Spawn to world functionalities
}

void UZAQInventory::ConsumeItem(UZAQItem* ItemToConsume)
{
	//Consume functionalities
}

void UZAQInventory::ForceRemoveItem(UZAQItem* ItemToRemove, int32 QuantityToRemove)
{
	//Force remove functionalities, bypass Remove Item procedure
}





