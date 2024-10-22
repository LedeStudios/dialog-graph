// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogGraph/Data/DialogData.h"
#include "DialogGraph/Data/DialogType.h"
#include "UObject/Object.h"
#include "DialogGraphNodeBase.generated.h"

enum class EDialogNodeType : uint8;
/**
 * 
 */
UCLASS()
class DIALOGGRAPHEDITOR_API UDialogGraphNodeBase : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual UEdGraphPin* CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name) { return nullptr; }
	virtual UEdGraphPin* CreateDefaultInputPin() { return nullptr; }
	virtual void CreateDefaultOutputPin() {}

public:
	virtual void InitNodeData(UObject* Outer) {}
	virtual void SetNodeData(UDialogNodeData* InData) {}
	virtual UDialogNodeData* GetNodeData() const { return nullptr; }
	virtual EDialogNodeType GetDialogNodeType()  const { return EDialogNodeType::Unknown; }

public:
	virtual void OnPropertiesChanged() {}
	
};
