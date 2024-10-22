// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogRuntimeGraph.generated.h"

class UDialogNodeData;

UENUM()
enum EDialogNodeType
{
	Start,
	Dialog,
	Finish
};

UCLASS()
class DIALOGGRAPH_API UDialogPin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FGuid PinId;
	
	UPROPERTY()
	FName PinName;

	UPROPERTY()
	TObjectPtr<UDialogPin> Connection = nullptr;
	
};

UCLASS()
class DIALOGGRAPH_API UDialogNode : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	EDialogNodeType NodeType = Dialog;
	
	UPROPERTY()
	TObjectPtr<UDialogPin> InputPin;

	UPROPERTY()
	TArray<UDialogPin*> OutputPins;

	UPROPERTY()
	FVector2D Position;

	UPROPERTY()
	TObjectPtr<UDialogNodeData> NodeData;
		
};

UCLASS()
class DIALOGGRAPH_API UDialogGraph : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TArray<UDialogNode*> Nodes;
	
};