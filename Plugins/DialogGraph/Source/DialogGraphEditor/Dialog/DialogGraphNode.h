// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogGraph/Data/DialogData.h"
#include "EdGraph/EdGraphNode.h"
#include "DialogGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGGRAPHEDITOR_API UDialogGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

public:
	UEdGraphPin* CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name);

	void SyncPinsWithChoices();

public:
	UPROPERTY()
	TWeakObjectPtr<UDialogNodeData> NodeData;
	
	void SetNodeData(UDialogNodeData* InData) { NodeData = InData; }

	UDialogNodeData* GetNodeData() const { return NodeData.Get(); }
	
};
