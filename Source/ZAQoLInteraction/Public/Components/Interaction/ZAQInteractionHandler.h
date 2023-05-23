// Copyright Zaki Agraraharja. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ZAQInteractionHandler.generated.h"

class UZAQInteractable;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FQIOnInteractionEnds);
UCLASS(Blueprintable, ClassGroup = ("ZAQoLInteraction"), meta = (BlueprintSpawnableComponent))
class ZAQOLINTERACTION_API UZAQInteractionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	UZAQInteractionHandler();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Interaction Handler")
	TObjectPtr<AActor> CurrentInteractableActor = nullptr;

	UPROPERTY()
	TObjectPtr<UZAQInteractable> AssignedInteractableComponent = nullptr;


public:
	/// <summary>
	/// Assign interactable for InitiateInteraction()
	/// </summary>
	/// <param name="ActorToInteract">Interactable to interact with</param>
	UFUNCTION(BlueprintCallable, Category = "Interaction")
	void AssignInteractable(AActor* ActorToInteract);

	UFUNCTION(Category = "Interaction Handler")
	void ClearInteractable() { AssignedInteractableComponent = nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void InitiateInteraction();
	
	UFUNCTION(BlueprintCallable, Category = "Interaction Handler")
	void EndInteraction(AActor* InteractedActor);
	
	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	bool IsInteractableActor(const AActor* ActorToCheck) { return ActorToCheck->IsA<UZAQInteractable>(); }

	UFUNCTION(BlueprintPure, Category = "Interaction Handler")
	AActor* GetCurrentInteractableActor() { return CurrentInteractableActor; }
	

	UPROPERTY(BlueprintAssignable, Category = "Interaction Handler")
	FQIOnInteractionEnds OnInteractionEnds;		
};
