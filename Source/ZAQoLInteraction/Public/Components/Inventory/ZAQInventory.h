// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQInventory.generated.h"

class UZAQItem;

UENUM(Blueprintable)
enum class EZAQItemProcessType : uint8
{
	EIP_DROP UMETA(DisplayName = "Drop"),
	EIP_USE UMETA(DisplayName = "Use"),
	EIP_REMOVE UMETA(DisplayName = "Remove"),
	EIP_RETRIEVE UMETA(DisplayName = "Retrieve")
};

UENUM(Blueprintable)
enum class EZAQRetrieveFailedType : uint8
{
	ERF_FULLINVENTORY UMETA(DisplayName = "Full Inventory"),
	ERF_FULLSLOT UMETA(DisplayName = "Full Slot"),
	ERF_INTERUPTED UMETA(DisplayName = "Interupted")
};

UENUM(Blueprintable)
enum class EZAQRemoveFailedType : uint8
{
	ERF_NOTFOUND UMETA(DisplayName = "Not Found"),
	ERF_NOTENOUGH UMETA(DisplayName = "Not Enough"),
	ERF_INTERUPTED UMETA(DisplayName = "Interupted")
};

USTRUCT(BlueprintType)
struct FZAQItemSlot
{
	GENERATED_USTRUCT_BODY()

	UZAQItem* Item;
	int32 Quantity;

	UZAQItem* GetItem() const { return Item; }
	int32 GetItemQuantity() const { return Quantity; }

	void SetItem(UZAQItem* ItemToSet) { Item = ItemToSet; }
	void ChangeQuantity(int32 Value) { Quantity += Value; }
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FZAOnRetrieveItemFailed, EZAQRetrieveFailedType, RetrieveFailedType, UZAQItem*, Item, int32, Quantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FZAOnRemoveItemFailed, EZAQRemoveFailedType, RemoveFailedType, UZAQItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FZAOnTransferItemSuccess, UZAQItem*, Item, int32, Quantity);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FZAOnUsedItem, UZAQItem*, Item);
UCLASS( Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Inventory"), meta=(BlueprintSpawnableComponent) )
class ZAQOLINTERACTION_API UZAQInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQInventory();

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	TArray<FZAQItemSlot> InventorySlots = TArray<FZAQItemSlot>();

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 MaximumSlotNumber = 99;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 OccupiedSlot = 0;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	bool bOverrideStackLimit = false;

	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = "true"), Category = "Inventory Properties")
	int32 OverridedStackLimitValue = 99;
	
	void AddToInventory(UZAQItem* ItemToAdd, int32 QuantityToAdd);	
	void AddNewEntry(UZAQItem* ItemToAdd, int32 QuantityToAdd);	
	void AddExistingEntryQuantity(FZAQItemSlot* SlotToModify, int32 QuantityToModify);
	bool TryRemoveFromInventory(UZAQItem* ItemToRemove, int32 QuantityToRemove);

	bool ItemAvailable(UZAQItem* ItemToCheck, FZAQItemSlot& outItemSlot) const;
	int32 GetMaximumSlot() const { return MaximumSlotNumber; }
	int32 GetOccupiedSlot() const { return OccupiedSlot; }

	int32 GetSlotStackLimit(FZAQItemSlot* SlotToCheck) const;
	int32 GetRemainingSlotStackAvailable(FZAQItemSlot* SlotToCheck) const;

public:
	UFUNCTION(BlueprintPure, Category = "Inventory Action")
	TArray<FZAQItemSlot> GetInventory() { return InventorySlots; }

	UFUNCTION(BlueprintPure, Category = "Inventory Properties")
	AActor* GetInventoryOwner() { return GetOwner(); }

	UFUNCTION(BlueprintPure, Category = "Inventory Action")
	bool EmptySlotAvailable(int32 outAmount) const;

	UFUNCTION(BlueprintCallable, Category = "Inventory Action")
	void SetMaximumSlot(int32 NewMaximumSlotNumber) { MaximumSlotNumber = NewMaximumSlotNumber; }
	
	UFUNCTION(BlueprintCallable, Category = "Inventory Action")
	void RetrieveItem(UZAQItem* ItemToRetrieve, int32 QuantityToRetrieve);
	
	UFUNCTION(BlueprintCallable, Category = "Inventory Action")
	void DropItem(UZAQItem* ItemToDrop, int32 QuantityToDrop);

	UFUNCTION(BlueprintCallable, Category = "Inventory Action")
	void ConsumeItem(UZAQItem* ItemToConsume, int32 QuantityToConsume);

	UFUNCTION(BlueprintCallable, Category = "Inventory Action")
	void ForceRemoveItem(UZAQItem* ItemToRemove, int32 QuantityToRemove);


	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FZAOnRetrieveItemFailed OnRetrieveItemFailed;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FZAOnRemoveItemFailed OnRemoveItemFailed;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FZAOnTransferItemSuccess OnAddingItemSuccess;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FZAOnTransferItemSuccess OnRemovingItemSuccess;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FZAOnUsedItem OnConsumeItem;

	UPROPERTY(BlueprintAssignable, Category = "Inventory Events")
	FZAOnUsedItem OnDropItem;
};
