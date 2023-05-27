/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#include "Item/ZAQItem.h"
#include "Kismet/GameplayStatics.h"

UZAQItem::UZAQItem()
{
	if (ItemDataClass != nullptr)
	{
		//AssignPropertiesFromItemData();
	}
}

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
	ItemSprite = Item->ItemData.ItemSprite;	
	bStackable = Item->ItemData.bIsStackable;
	StackLimit = Item->ItemData.StackLimit;
	
}

void UZAQItem::ClearProperties()
{
	ItemName = FName();
	ItemIcon = nullptr;
	ItemDescription = FString();	
	ItemSprite = nullptr;
	bStackable = true;
	StackLimit = 99;
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
	//AActor* ActorToSpawn = GetWorld()->SpawnActor<AActor>(GetWorldRepresentation(), FVector(0,0,0), FRotator::ZeroRotator);

	FString NameToPrint = ItemName.ToString();
	FString User = ItemSpawner->GetName();

	FString DebugMessage = FString::Printf(TEXT("%s spawn %s to the level!"), *NameToPrint, *User);
	float DisplayTime = 5.0f;
	FColor TextColor = FColor::Yellow;
	int32 Key = -1;

	GEngine->AddOnScreenDebugMessage(Key, DisplayTime, TextColor, DebugMessage);
}

void UZAQItem::SetStackedQuantity(int32 Value)
{
	if (!IsStackable())
	{
		StackedQuantity = 1;
#if WITH_EDITOR
		UE_LOG(LogTemp, Warning, TEXT("Item is not stackable, assign value = 1"));
#endif
		return;
	}

	StackedQuantity = Value;
}
