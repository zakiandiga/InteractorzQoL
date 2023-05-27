/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Class.h"
#include "UObject/PropertyPortFlags.h"
#include "Item/DA_ZAQItemData.h"
#include "Item/ZAQItemPickup.h"
#include "ZAQItem.generated.h"

class UStaticMesh;

UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Item"))
class ZAQOLINTERACTION_API UZAQItem : public UObject
{
	GENERATED_BODY()

public:
	UZAQItem();

private:	
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	TSubclassOf<UDA_ZAQItemData> ItemDataClass;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	TSubclassOf<AActor> WorldRepresentationActor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	FName ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	FString ItemDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	EZAItemType ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	UStaticMesh* ItemSprite = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	bool bStackable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	int32 StackLimit = 1;	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	int32 StackedQuantity = 1;

	


#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void ClearProperties();
	
public:
	void AssignPropertiesFromItemData();

	void SetItemDataClass(TSubclassOf<UDA_ZAQItemData> ItemDataToSet) { ItemDataClass = ItemDataToSet; }
	
	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void UseItem(AActor* ItemUser);

	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void SpawnItem(AActor* ItemUser);

	virtual void UseItem_Implementation(AActor* ItemUser);
	virtual void SpawnItem_Implementation(AActor* ItemSpawner);

	UFUNCTION(BlueprintPure, Category = "Item")
	FName GetItemName() const { return ItemName; }

	UFUNCTION(BlueprintPure, Category = "Item")
	FString GetItemDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintPure, Category = "Item")
	EZAItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure, Category = "Item")
	UTexture2D* GetItemIcon() const { return ItemIcon; }

	UFUNCTION(BlueprintPure, Category = "Item")
	UStaticMesh* GetItemSprite() const { return ItemSprite; }

	UFUNCTION(BlueprintPure, Category = "Item")
	bool IsStackable() const { return bStackable; }

	UFUNCTION(BlueprintPure, Category = "Item")
	int32 GetStackLimit() const { return StackLimit; }
	
	UFUNCTION(BlueprintPure, Category = "Item")
	int32 GetCurrentStackedQuantity() const { return StackedQuantity; }

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetStackedQuantity(int32 Value);
};
