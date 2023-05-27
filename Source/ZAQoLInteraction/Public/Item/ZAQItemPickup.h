// /* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZAQItemPickup.generated.h"

class UZAQInteractablePickup;
class UZAQItem;

UCLASS(Blueprintable)
class ZAQOLINTERACTION_API AZAQItemPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	AZAQItemPickup();

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Pickup Properties")
	UStaticMeshComponent* PickupMesh = nullptr;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Pickup Properties")
	UZAQInteractablePickup* InteractableComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Pickup Properties")
	TSubclassOf<UZAQItem> RepresentedItemClass = nullptr;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Pickup Properties")
	UZAQItem* RepresentedItem = nullptr;	

	void SetRepresentedItem(UZAQItem* ItemToRepresent) { RepresentedItem = Cast<UZAQItem>(ItemToRepresent); }
	void SetSprite(UStaticMesh* Sprite) { PickupMesh->SetStaticMesh(Sprite); }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void InitializeItemPickup(UZAQItem* Item);
};
