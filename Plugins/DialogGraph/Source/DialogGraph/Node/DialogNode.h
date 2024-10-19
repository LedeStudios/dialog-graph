// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogNode.generated.h"

UCLASS(Blueprintable)
class DIALOGGRAPH_API UDialogNode : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	FText Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	FText Line;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	TObjectPtr<UDialogNode> NextNode;
	
};

USTRUCT(Blueprintable)
struct FDialogChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture Icon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDialogNode> NextNode;
	
};

UCLASS(Blueprintable)
class UDialogChoiceNode : public UDialogNode
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog")
	TArray<FDialogChoice*> Choices;
	
};
