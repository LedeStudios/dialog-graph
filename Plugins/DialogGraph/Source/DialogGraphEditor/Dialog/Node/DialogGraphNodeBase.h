// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogGraph/Data/DialogData.h"
#include "UObject/Object.h"
#include "DialogGraphNodeBase.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGGRAPHEDITOR_API UDialogGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual UEdGraphPin* CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name) { return nullptr; }

protected:
	UPROPERTY()
	TWeakObjectPtr<UDialogNodeData> NodeData;

public:
	void SetNodeData(UDialogNodeData* InData) { NodeData = InData; }

	UDialogNodeData* GetNodeData() const { return NodeData.Get(); }
	
};
