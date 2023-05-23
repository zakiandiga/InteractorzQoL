// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Item/ZAQItem.h"

#if WITH_EDITOR
void UZAQItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = GET_MEMBER_NAME_CHECKED(UZAQItem, ItemDataClass);

	if (PropertyChangedEvent.Property == nullptr) return;

	if (PropertyChangedEvent.Property->GetFName() == PropertyName)
	{
		AssignPropertiesFromItemData();
	}
}
#endif

void UZAQItem::AssignPropertiesFromItemData()
{
	if (ItemDataClass == nullptr)
	{
		ClearProperties();
		return;
	}

	UDA_ZAQItemData* Item = NewObject<UDA_ZAQItemData>(this, ItemDataClass);
	
	ItemName = Item->ItemData.Name;	
	ItemIcon = Item->ItemData.Icon;
	ItemDescription = Item->ItemData.Description;
	ItemType = Item->ItemData.ItemType;
	ItemPickupSprite = Item->ItemData.PickUpSprite;	
	Stackable = Item->ItemData.bIsStackable;
	StackLimit = Item->ItemData.StackLimit;
}

void UZAQItem::ClearProperties()
{
	ItemName = FName();
	ItemIcon = nullptr;
	ItemDescription = FString();	
	ItemPickupSprite = nullptr;
	Stackable = true;
	StackLimit = 1;
}

void UZAQItem::UseItem_Implementation(AActor* ItemUser)
{	
	FString NameToPrint = ItemName.ToString();
	FString User = ItemUser->GetName();

	FString DebugMessage = FString::Printf(TEXT("%s used %s!"), *NameToPrint, *User);
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Yellow;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);
}

void UZAQItem::SpawnItem_Implementation(AActor* ItemSpawner)
{
	FString NameToPrint = ItemName.ToString();
	FString User = ItemSpawner->GetName();

	FString DebugMessage = FString::Printf(TEXT("%s spawn %s to the level!"), *NameToPrint, *User);
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Yellow;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);
}
