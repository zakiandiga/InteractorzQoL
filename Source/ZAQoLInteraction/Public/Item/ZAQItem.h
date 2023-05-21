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
	TObjectPtr<UTexture2D> ItemIcon = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	FString ItemDescription;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	EZAItemType ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item Info")
	TObjectPtr<UStaticMesh> ItemPickupSprite = nullptr;

#if WITH_EDITOR
	void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	void AssignPropertiesFromItemData();
	void ClearProperties();
	
public:
	UFUNCTION(BlueprintNativeEvent, Category = "Item")
	void UseItem(AActor* ItemUser);

	virtual void UseItem_Implementation(AActor* ItemUser);
};
