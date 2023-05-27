// /* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ZAQItemCreator.generated.h"

class UDA_ZAQItemData;
class UDataAsset;
class UZAQItem;
class AZAQItemPickup;

/**
 * 
 */
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (DisplayName = "Item Creation Tool"))
class ZAQOLINTERACTION_API UZAQItemCreator : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#if WITH_EDITOR
public:

	UFUNCTION(BlueprintCallable, Category = "Item Creator")
	static UZAQItem* SetupItemInstance(TSubclassOf<UDA_ZAQItemData> ItemData, TSubclassOf<UZAQItem> Item);

	UFUNCTION(BlueprintCallable, Category = "Item Creator")
	static UBlueprint* CreateBlueprintForItemPickup(UPackage* Package, FString Path);

	UFUNCTION(BlueprintCallable, Category = "Item Creator")
	static void CreateItemPickupAsset(FString AssetName, FString TargetPath, TSubclassOf<UDA_ZAQItemData> ItemData, TSubclassOf<UZAQItem> Item);

	UFUNCTION(BlueprintCallable, Category = "Item Creator")
	static TArray<TSubclassOf<UDA_ZAQItemData>> GetItemDataList();
#endif

};
