// /* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */


#include "Item/ZAQItemPickup.h"
#include "Item/ZAQItem.h"
#include "Components/Interaction/ZAQInteractablePickup.h"

AZAQItemPickup::AZAQItemPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	InteractableComponent = CreateDefaultSubobject<UZAQInteractablePickup>(TEXT("Interactable"));	

	PickupMesh->SetCollisionProfileName("Interactable");
	PickupMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PickupMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Overlap);
}

void AZAQItemPickup::InitializeItemPickup(UZAQItem* Item)
{
	SetRepresentedItem(Item);

	if (RepresentedItem != nullptr)
	{
		SetSprite(RepresentedItem->GetItemSprite());
	}
}

void AZAQItemPickup::BeginPlay()
{
	Super::BeginPlay();	
}

void AZAQItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


