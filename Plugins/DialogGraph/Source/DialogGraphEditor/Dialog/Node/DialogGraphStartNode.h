// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogGraphNodeBase.h"
#include "UObject/Object.h"
#include "DialogGraphStartNode.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGGRAPHEDITOR_API UDialogGraphStartNode : public UDialogGraphNodeBase
{
	GENERATED_BODY()

public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool CanUserDeleteNode() const override;

public:
	virtual UEdGraphPin* CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name) override;
	virtual void CreateDefaultOutputPin() override;

public:
	UPROPERTY()
	TWeakObjectPtr<UDialogNodeData> NodeData;
	
	virtual void InitNodeData(UObject* Outer) override { NodeData = NewObject<UDialogNodeData>(Outer); }
	virtual void SetNodeData(UDialogNodeData* InData) override { NodeData = InData; }
	virtual UDialogNodeData* GetNodeData() { return NodeData.Get(); }
	virtual EDialogNodeType GetDialogNodeType() const override { return EDialogNodeType::Start; }

public:
	virtual void OnPropertiesChanged() override { Modify(); }
	
};
