// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Dialog.generated.h"

class UDialogNode;

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialog : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Dialog")
	TObjectPtr<UDialogNode> Node;
	
};

UCLASS(BlueprintType)
class UDialogNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Node")
	FText Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Node")
	FText Line;
	
};





