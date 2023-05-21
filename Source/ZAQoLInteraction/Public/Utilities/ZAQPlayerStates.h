// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ZAQPlayerStates.generated.h"

UENUM(BlueprintType)
enum class EZAQPlayerControlStates : uint8
{
	EPCS_Interacting UMETA(DisplayName = "Interacting"),
	EPCS_Moving UMETA(DisplayName = "Moving")
};