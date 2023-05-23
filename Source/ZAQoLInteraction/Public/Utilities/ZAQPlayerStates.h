/* Copyright (c) [2023] zakiandiga (github.com/zakiandiga) - All rights reserved. */

#pragma once

#include "CoreMinimal.h"
#include "ZAQPlayerStates.generated.h"

UENUM(BlueprintType)
enum class EZAQPlayerControlStates : uint8
{
	EPCS_Interacting UMETA(DisplayName = "Interacting"),
	EPCS_Moving UMETA(DisplayName = "Moving")
};