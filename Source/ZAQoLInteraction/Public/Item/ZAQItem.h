// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Class.h"
#include "UObject/PropertyPortFlags.h"
#include "Item/DA_ZAQItem.h"
#include "ZAQItem.generated.h"

UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Item"))
class ZAQOLINTERACTION_API UZAQItem : public USceneComponent
{
	GENERATED_BODY()


private:	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Item Data")
	TSubclassOf<UDA_ZAQItemData> ItemDataClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	FName ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	FString ItemDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	EZAItemType ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	UTexture2D* ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	UStaticMesh* ItemPickupSprite = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	bool Stackable = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	int32 StackLimit = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	int32 StackedQuantity = 1;


#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void AssignPropertiesFromItemData();
	void ClearProperties();
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void UseItem(AActor* ItemUser);

	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void SpawnItem(AActor* ItemUser);

	virtual void UseItem_Implementation(AActor* ItemUser);
	virtual void SpawnItem_Implementation(AActor* ItemSpawner);

	UFUNCTION(BlueprintPure, Category = "Item")
	FName GetName() const { return ItemName; }

	UFUNCTION(BlueprintPure, Category = "Item")
	FString GetDescription() const { return ItemDescription; }

	UFUNCTION(BlueprintPure, Category = "Item")
	EZAItemType GetItemType() const { return ItemType; }

	UFUNCTION(BlueprintPure, Category = "Item")
	UTexture2D* GetIcon() const { return ItemIcon; }

	UFUNCTION(BlueprintPure, Category = "Item")
	UStaticMesh* GetMesh() const { return ItemPickupSprite; }

	UFUNCTION(BlueprintPure, Category = "Item")
	bool IsStackable() const { return Stackable; }


	UFUNCTION(BlueprintPure, Category = "Item")
	int32 GetStackLimit() const { return StackLimit; }

	UFUNCTION(BlueprintPure, Category = "Item")
	int32 GetCurrentStackedQuantity() const { return StackedQuantity; }
};
