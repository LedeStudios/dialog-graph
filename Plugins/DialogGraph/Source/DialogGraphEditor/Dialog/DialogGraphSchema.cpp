// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphSchema.h"

#include "Node/DialogGraphDialogNode.h"
#include "DialogGraph/Data/DialogData.h"
#include "Node/DialogGraphFinishNode.h"
#include "Node/DialogGraphStartNode.h"

void UDialogGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	const TSharedPtr<FNewNodeAction> NewDialogNodeAction(
		new FNewNodeAction(
			UDialogGraphDialogNode::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Dialog Node")),
			FText::FromString(TEXT("Makes a new dialog node")),
			0
		)
	);

	const TSharedPtr<FNewNodeAction> NewDialogFinishNodeAction(
		new FNewNodeAction(
			UDialogGraphFinishNode::StaticClass(),
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Finish Node")),
			FText::FromString(TEXT("Makes a new finish node")),
			0
		)
	);
	
	ContextMenuBuilder.AddAction(NewDialogNodeAction);
	ContextMenuBuilder.AddAction(NewDialogFinishNodeAction);
}

const FPinConnectionResponse UDialogGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Need 2 pins"));
	}

	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Inputs can only connect to outputs"));
	}
	
	return FPinConnectionResponse(CONNECT_RESPONSE_BREAK_OTHERS_AB, TEXT(""));
}

void UDialogGraphSchema::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	UDialogGraphStartNode* StartNode = NewObject<UDialogGraphStartNode>(&Graph);
	StartNode->CreateNewGuid();
	StartNode->NodePosX = 0;
	StartNode->NodePosY = 0;
	StartNode->CreateDefaultOutputPin();
	Graph.AddNode(StartNode, true, true);

	UDialogGraphFinishNode* FinishNode = NewObject<UDialogGraphFinishNode>(&Graph);
	FinishNode->CreateNewGuid();
	FinishNode->NodePosX = 100;
	FinishNode->NodePosY = 0;
	FinishNode->CreateDefaultInputPin();
	Graph.AddNode(FinishNode, true, true);
	
	Graph.Modify();
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
                                            bool bSelectNewNode)
{
	UDialogGraphNodeBase* Node = NewObject<UDialogGraphDialogNode>(ParentGraph, ClassTemplate);
	Node->CreateNewGuid();
	Node->NodePosX = Location.X;
	Node->NodePosY = Location.Y;
	Node->InitNodeData(Node);

	UEdGraphPin* InputPin = Node->CreateDefaultInputPin();
	Node->CreateDefaultOutputPin();

	if (FromPin != nullptr)
	{
		Node->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}

	ParentGraph->Modify();
	ParentGraph->AddNode(Node, true, true);
	
	return Node;
}
