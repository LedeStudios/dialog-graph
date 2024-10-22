// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogType.generated.h"

UENUM(BlueprintType)
enum class EDialogNodeType : uint8
{
	Unknown,
	Start,
	Dialog,
	Finish
};
