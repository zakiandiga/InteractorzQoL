// Copyright Zaki Agraraharja. All Rights Reserved.

#include "Components/Interaction/ZAQInteractableTargetting.h"
#include "Components/Interaction/ZAQInteractableCollider.h"
#include "Components/Interaction/ZAQInteractionHandler.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "DrawDebugHelpers.h"

UZAQInteractableTargetting::UZAQInteractableTargetting()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UZAQInteractableTargetting::BeginPlay()
{
	Super::BeginPlay();

	PlayerCamera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	CameraBoom = Cast<USpringArmComponent>(GetOwner()->GetComponentByClass(USpringArmComponent::StaticClass()));
	InteractableCollider = Cast<UZAQInteractableCollider>(GetOwner()->GetComponentByClass(UZAQInteractableCollider::StaticClass()));
	InteractionHandler = Cast<UZAQInteractionHandler>(GetOwner()->GetComponentByClass(UZAQInteractionHandler::StaticClass()));
}

void UZAQInteractableTargetting::TracingInteractable()
{
#if WITH_EDITOR
	if (PlayerCamera == nullptr && CameraBoom == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: PlayerCamera OR CameraBoom are nullptr, cannot TracingInteractable()"));
		return;
	}
#endif

	FVector StartPoint = PlayerCamera->GetComponentLocation() + (PlayerCamera->GetForwardVector() * CameraBoom->TargetArmLength);
	FVector EndPoint = StartPoint + (PlayerCamera->GetForwardVector() * TracingRange);

	FHitResult CurrentHitResult;
	FCollisionQueryParams LineTraceParams;
	LineTraceParams.AddIgnoredActor(GetOwner());
	
	GetWorld()->LineTraceSingleByChannel(CurrentHitResult, StartPoint, EndPoint, ECollisionChannel::ECC_Visibility, LineTraceParams);

	AActor* HitActor = CurrentHitResult.GetActor();

	TryAssignInteractable(HitActor);	
}


void UZAQInteractableTargetting::TryAssignInteractable(AActor* TracedActor)
{
	if (TracedActor == nullptr || !InteractionHandler->IsInteractableActor(TracedActor))
	{
		if (InteractionHandler->GetCurrentInteractableActor() != nullptr)
		{
			InteractionHandler->ClearInteractable();
			OnInteractableGone.Broadcast();
			return;
		}
	}

	if (TracedActor != InteractionHandler->GetCurrentInteractableActor())
	{
		InteractionHandler->AssignInteractable(TracedActor);
		OnInteractableFound.Broadcast(TracedActor);
	}
}

bool UZAQInteractableTargetting::IsTracing() const
{
#if WITH_EDITOR
	if (InteractableCollider == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s: InteractableCollider not found!"), *GetOwner()->GetName());
		return false;
	}
#endif

	return InteractableCollider->InteractablesDetected();
}


void UZAQInteractableTargetting::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsTracing())
	{
		TracingInteractable();
	}	
}

