// Copyright Zaki Agraraharja. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ZAQItem.generated.h"

UENUM(BlueprintType)
enum class EZAItemType : uint8
{
	EIT_Consumables UMETA(DisplayName = "Consumables"),
	EIT_Materials UMETA(DisplayName = "Materials"),
	EIT_Equipments UMETA(DisplayName = "Equipments"),
	EIT_Quest UMETA(DisplayName = "Quest"),
};

USTRUCT(BlueprintType)
struct FZAItemData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName Name;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	class UTexture2D* Icon = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	bool bIsStackable = true;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Item Data")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EZAItemType ItemType = EZAItemType::EIT_Materials;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	class UStaticMesh* PickUpSprite = nullptr;
};

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Item Data"))
class ZAQOLINTERACTION_API UDA_ZAQItemData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FZAItemData ItemData;
};
