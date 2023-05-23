/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDebug.generated.h"

class UZAQInteractable;

UCLASS(Blueprintable)
class ZAQOLINTERACTION_API AInteractableDebug : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractableDebug();

private:
	UZAQInteractable* Interactable;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


};
