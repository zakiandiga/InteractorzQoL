// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Item/ZAQItem.h"

#if WITH_EDITOR
void UZAQItem::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName PropertyName = GET_MEMBER_NAME_CHECKED(UZAQItem, ItemDataClass);

	if (PropertyChangedEvent.Property == nullptr) return;
	if (PropertyChangedEvent.Property->GetFName() != PropertyName) return;

	AssignPropertiesFromItemData();
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

	if (Item == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("failed to create new UDA_ZAQItem* Item object!"));
		return;
	}

	ItemName = Item->ItemData.Name;	
	ItemIcon = Item->ItemData.Icon;
	ItemDescription = Item->ItemData.Description;
	ItemType = Item->ItemData.ItemType;
	ItemPickupSprite = Item->ItemData.PickUpSprite;	
}

void UZAQItem::ClearProperties()
{
	ItemName = FName();
	ItemIcon = nullptr;
	ItemDescription = FString();	
	ItemPickupSprite = nullptr;
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
