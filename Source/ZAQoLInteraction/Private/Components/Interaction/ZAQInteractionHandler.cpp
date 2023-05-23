// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Components/Interaction/ZAQInteractionHandler.h"
#include "Components/Interaction/ZAQInteractable.h"
#include "Kismet/KismetSystemLibrary.h"

UZAQInteractionHandler::UZAQInteractionHandler()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UZAQInteractionHandler::InitiateInteraction()
{
	if (AssignedInteractableComponent == nullptr)
	{
#if WITH_EDITOR
		UE_LOG(LogTemp, Error, TEXT("%s: No Interactable assigned, will not InitiateInteraction()!"), *GetOwner()->GetName());
#endif
		return;
	}
	
	AssignedInteractableComponent->OnInteractionFinished.AddUniqueDynamic(this, &UZAQInteractionHandler::EndInteraction);
	AssignedInteractableComponent->Interact(GetOwner());
}

void UZAQInteractionHandler::EndInteraction(AActor* InteractedActor)
{	
	AssignedInteractableComponent->OnInteractionFinished.RemoveDynamic(this, &UZAQInteractionHandler::EndInteraction);
	ClearInteractable();
	OnInteractionEnds.Broadcast();
}

void UZAQInteractionHandler::AssignInteractable(AActor* ActorToAssign)
{	
	if (IsInteractableActor(ActorToAssign))
	{
		AssignedInteractableComponent = Cast<UZAQInteractable>(ActorToAssign->GetComponentByClass(UZAQInteractable::StaticClass()));
	}
}