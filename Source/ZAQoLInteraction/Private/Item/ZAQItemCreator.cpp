// /* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */


#include "Item/ZAQItemCreator.h"
#include "Item/ZAQItem.h"
#include "Item/DA_ZAQItemData.h"
#include "Item/ZAQItemPickup.h"

#if WITH_EDITOR
#include "AssetRegistry/AssetRegistryModule.h"
#include "KismetCompilerModule.h"
#include "Kismet2/KismetEditorUtilities.h"

UZAQItem* UZAQItemCreator::SetupItemInstance(TSubclassOf<UDA_ZAQItemData> ItemData, TSubclassOf<UZAQItem> Item)
{
	UZAQItem* ItemInstance = NewObject<UZAQItem>(GetTransientPackage(), Item);
	ItemInstance->SetItemDataClass(ItemData);
	ItemInstance->AssignPropertiesFromItemData();

	return ItemInstance;
}

UBlueprint* UZAQItemCreator::CreateBlueprintForItemPickup(UPackage* Package, FString Path)
{
	TSubclassOf<AZAQItemPickup> ParentClass = AZAQItemPickup::StaticClass();

	if (!FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Parent class not blueprintable"));
		return nullptr;
	}

	UClass* BlueprintClass = nullptr;
	UClass* BlueprintGenClass = nullptr;
	FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler").GetBlueprintTypesForClass(ParentClass, BlueprintClass, BlueprintGenClass);

	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(ParentClass, Package, *FPaths::GetBaseFilename(Path), BPTYPE_Normal, BlueprintClass, BlueprintGenClass);
	return Blueprint;
}

void UZAQItemCreator::CreateItemPickupAsset(FString AssetName, FString TargetPath, TSubclassOf<UDA_ZAQItemData> ItemData, TSubclassOf<UZAQItem> Item)
{
	FString BlueprintPath = TargetPath.Append(AssetName);

	if (StaticLoadObject(UObject::StaticClass(), nullptr, *BlueprintPath) != nullptr)
	{		
		UE_LOG(LogTemp, Error, TEXT("Asset already exist: %s"), *BlueprintPath);
		return;
	}

	UPackage* Package = CreatePackage(*BlueprintPath);

	if (Package == nullptr)
	{		
		UE_LOG(LogTemp, Error, TEXT("Cannot create package! Check the file path and file name!"));
		return;
	}

	UBlueprint* Blueprint = CreateBlueprintForItemPickup(Package, BlueprintPath);
		
	AZAQItemPickup* ItemPickup = Blueprint->GeneratedClass.Get()->GetDefaultObject<AZAQItemPickup>();

	if (ItemPickup == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot initialize Item Pickup properties! Check if AZAQItemPickup class is valid!"))
		return;
	}

	ItemPickup->InitializeItemPickup(SetupItemInstance(ItemData, Item));

	FAssetRegistryModule::AssetCreated(Blueprint);
	Blueprint->MarkPackageDirty();

	UE_LOG(LogTemp, Log, TEXT("Item CREATED!"));
}

TArray<TSubclassOf<UDA_ZAQItemData>> UZAQItemCreator::GetItemDataList()
{
	TSubclassOf<UDA_ZAQItemData> ItemDataClass = UDA_ZAQItemData::StaticClass();

	UClass* ItemData = ItemDataClass.Get();
	TArray<TSubclassOf<UDA_ZAQItemData>> Subclasses;

	if (ItemData)
	{
		for (TObjectIterator<UClass> i; i; ++i)
		{

			if (i->IsChildOf(ItemDataClass) && !i->HasAnyClassFlags(CLASS_Abstract))
			{
				Subclasses.Add(*i);
			}			
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Fetched UDA_ZAQItemData subclasses!"));
	return Subclasses;
}

#endif