/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_ZAQItem.generated.h"

class UTexture2D;
class UStaticMesh;

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

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	FName Name;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	FString Description;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	EZAItemType ItemType = EZAItemType::EIT_Materials;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	UTexture2D* Icon = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	UStaticMesh* PickUpSprite = nullptr;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	bool bIsStackable = true;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Item Data")
	int32 StackLimit = 99;
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
