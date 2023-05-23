/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#include "Components/Interaction/ZAQInteractionHandler.h"
#include "Components/Interaction/ZAQInteractable.h"
#include "Kismet/KismetSystemLibrary.h"

UZAQInteractionHandler::UZAQInteractionHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UZAQInteractionHandler::InitiateInteraction()
{
	if (AssignedInteractableComponent != nullptr)
	{
		AssignedInteractableComponent->OnInteractionFinished.AddUniqueDynamic(this, &UZAQInteractionHandler::EndInteraction);
		AssignedInteractableComponent->Interact(GetOwner());
	}	
}

void UZAQInteractionHandler::EndInteraction(AActor* InteractedActor)
{	
	AssignedInteractableComponent->OnInteractionFinished.RemoveDynamic(this, &UZAQInteractionHandler::EndInteraction);
	ClearInteractable();
	OnInteractionEnds.Broadcast();
}

bool UZAQInteractionHandler::IsInteractableActor(AActor* ActorToCheck)
{	
	UZAQInteractable* InteractableComponent = Cast<UZAQInteractable>(ActorToCheck->GetComponentByClass(UZAQInteractable::StaticClass()));
	return InteractableComponent != nullptr;
}

void UZAQInteractionHandler::AssignInteractable(AActor* ActorToAssign)
{	
	if (IsInteractableActor(ActorToAssign))
	{
		AssignedInteractableComponent = Cast<UZAQInteractable>(ActorToAssign->GetComponentByClass(UZAQInteractable::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("Interactable = %s"), *AssignedInteractableComponent->GetName());
	}
}