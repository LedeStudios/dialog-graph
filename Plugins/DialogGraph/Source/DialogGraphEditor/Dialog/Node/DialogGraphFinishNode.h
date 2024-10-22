// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNodeBase.h"
#include "UObject/Object.h"
#include "DialogGraphFinishNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGGRAPHEDITOR_API UDialogGraphFinishNode : public UDialogGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

public:
	virtual UEdGraphPin* CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name) override;
	virtual UEdGraphPin* CreateDefaultInputPin() override;

public:
	UPROPERTY()
	TWeakObjectPtr<UDialogNodeData> NodeData;
	
	virtual void InitNodeData(UObject* Outer) override { NodeData = NewObject<UDialogNodeData>(Outer); }
	virtual void SetNodeData(UDialogNodeData* InData) override { NodeData = InData; }
	virtual UDialogNodeData* GetNodeData() { return NodeData.Get(); }
	virtual EDialogNodeType GetDialogNodeType() const override { return EDialogNodeType::Finish; }

public:
	virtual void OnPropertiesChanged() override { Modify(); }

};
