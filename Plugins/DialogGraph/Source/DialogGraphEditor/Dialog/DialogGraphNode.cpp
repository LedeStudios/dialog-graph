// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"


FText UDialogGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("Dialog"));
}

FLinearColor UDialogGraphNode::GetNodeTitleColor() const
{
	return FLinearColor(FColor::FromHex("#FC037F"));
}

bool UDialogGraphNode::CanUserDeleteNode() const
{
	return true;
}

void UDialogGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString("Dialog Node Actions"));
	UDialogGraphNode* Node = const_cast<UDialogGraphNode*>(this);
	
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString("Add Pin"),
		FText::FromString("Creates a new pin"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([Node]()
		{
			Node->CreatePin(EGPD_Output, TEXT("Outputs"), TEXT("Another Output"));
			Node->GetGraph()->NotifyGraphChanged();
			Node->GetGraph()->Modify();
		}))
	);

	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString("Delete Pin"),
		FText::FromString("Deletes the last pin"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([Node]()
		{
			if (UEdGraphPin* Pin = Node->GetPinAt(Node->Pins.Num() - 1); Pin->Direction != EGPD_Input)
			{
				Node->RemovePin(Pin);
				Node->GetGraph()->NotifyGraphChanged();
				Node->GetGraph()->Modify();
			}
		}))
	);

	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString("Delete Node"),
		FText::FromString("Deletes the Node"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([Node]()
		{
			Node->GetGraph()->RemoveNode(Node);
		}))
	);
}
