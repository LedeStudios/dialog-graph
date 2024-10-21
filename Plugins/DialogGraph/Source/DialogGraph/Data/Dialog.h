// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Dialog.generated.h"


class UDialogGraph;

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialog : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Dialog")
	FString DialogId;
	
	UPROPERTY()
	TObjectPtr<UDialogGraph> Graph;
	
};



