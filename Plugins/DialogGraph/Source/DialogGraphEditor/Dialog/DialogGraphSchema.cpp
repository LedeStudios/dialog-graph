// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphSchema.h"

#include "Node/DialogGraphDialogNode.h"
#include "DialogGraph/Data/DialogData.h"
#include "Node/DialogGraphFinishNode.h"
#include "Node/DialogGraphStartNode.h"

void UDialogGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	Super::GetGraphContextActions(ContextMenuBuilder);

	const TSharedPtr<FNewNodeAction> NewNodeAction(
		new FNewNodeAction(
			FText::FromString(TEXT("Nodes")),
			FText::FromString(TEXT("New Node")),
			FText::FromString(TEXT("Makes a new node")),
			0
		)
	);

	ContextMenuBuilder.AddAction(NewNodeAction);
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
	StartNode->CreateDialogPin(EGPD_Output, TEXT("Start"));
	Graph.AddNode(StartNode, true, true);

	UDialogGraphFinishNode* FinishNode = NewObject<UDialogGraphFinishNode>(&Graph);
	FinishNode->CreateNewGuid();
	FinishNode->NodePosX = 100;
	FinishNode->NodePosY = 0;
	FinishNode->CreateDialogPin(EGPD_Input, TEXT("Finish"));
	Graph.AddNode(FinishNode, true, true);
	
	Graph.Modify();
}

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
                                            bool bSelectNewNode)
{
	UDialogGraphDialogNode* Node = NewObject<UDialogGraphDialogNode>(ParentGraph);
	Node->CreateNewGuid();
	Node->NodePosX = Location.X;
	Node->NodePosY = Location.Y;
	Node->SetNodeData(NewObject<UDialogNodeData>(Node));

	UEdGraphPin* InputPin = Node->CreateDialogPin(EGPD_Input, TEXT("In"));
	Node->SyncPinsWithChoices();

	if (FromPin != nullptr)
	{
		Node->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}

	ParentGraph->Modify();
	ParentGraph->AddNode(Node, true, true);
	
	return Node;
}
