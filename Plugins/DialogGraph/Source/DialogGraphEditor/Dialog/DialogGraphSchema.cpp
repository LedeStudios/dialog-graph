// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphSchema.h"

#include "DialogGraphNode.h"

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

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
                                            bool bSelectNewNode)
{
	UDialogGraphNode* Node = NewObject<UDialogGraphNode>(ParentGraph);
	Node->NodePosX = Location.X;
	Node->NodePosY = Location.Y;

	Node->CreatePin(EGPD_Input, TEXT("Inputs"), TEXT("Input"));
	Node->CreatePin(EGPD_Output, TEXT("Outputs"), TEXT("Output 1"));
	Node->CreatePin(EGPD_Output, TEXT("Outputs"), TEXT("Output 2"));

	ParentGraph->Modify();
	ParentGraph->AddNode(Node, true, true);
	
	return Node;
}
