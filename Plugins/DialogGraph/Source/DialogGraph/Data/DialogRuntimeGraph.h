// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogType.h"
#include "UObject/Object.h"
#include "DialogRuntimeGraph.generated.h"

class UDialogNodeData;

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialogPin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	FGuid PinId;
	
	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	FName PinName;

	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	TObjectPtr<UDialogPin> Connection = nullptr;
	
};

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialogNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	EDialogNodeType NodeType = EDialogNodeType::Dialog;
	
	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	TObjectPtr<UDialogPin> InputPin;

	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	TArray<UDialogPin*> OutputPins;

	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	FVector2D Position;

	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	TObjectPtr<UDialogNodeData> NodeData;
		
};

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialogGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	TArray<UDialogNode*> Nodes;

public:
	UFUNCTION(BlueprintCallable, Category="Dialog")
	UDialogNode* FindNextNode(UDialogNode* CurrentNode);

	UFUNCTION(BlueprintCallable, Category="Dialog")
	UDialogNode* FindNextNodeByIndex(UDialogNode* CurrentNode, int32& Index);
	
};