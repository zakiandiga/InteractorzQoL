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
class ZAQOLINTERACTION_API UZAQItem : public UObject
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

	virtual void UseItem_Implementation(AActor* ItemUser);

	FName GetName() const { return ItemName; }
	FString GetDescription() const { return ItemDescription; }
	EZAItemType GetItemType() const { return ItemType; }
	UTexture2D* GetIcon() const { return ItemIcon; }
	UStaticMesh* GetMesh() const { return ItemPickupSprite; }
	bool IsStackable() const { return Stackable; }

	int32 GetStackLimit() const { return StackLimit; }
	int32 GetCurrentStackedQuantity() const { return StackedQuantity; }
};
