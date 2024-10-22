// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphFinishNode.h"

FText UDialogGraphFinishNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Finish");
}

FLinearColor UDialogGraphFinishNode::GetNodeTitleColor() const
{
	return FLinearColor(FColor::Blue);
}

bool UDialogGraphFinishNode::CanUserDeleteNode() const
{
	return true;
}

void UDialogGraphFinishNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("SectionName"), FText::FromString("End Node Actions"));
	UDialogGraphFinishNode* Node = const_cast<UDialogGraphFinishNode*>(this);
	
	Section.AddMenuEntry(
		TEXT("DeleteEntry"),
		FText::FromString("Delete Node"),
		FText::FromString("Deletes the node"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([Node]()
		{
			Node->GetGraph()->RemoveNode(Node);
		}))
	);
}

UEdGraphPin* UDialogGraphFinishNode::CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name)
{
	const FName Category = TEXT("Inputs");
	const FName SubCategory = TEXT("FinishPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, Name);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

UEdGraphPin* UDialogGraphFinishNode::CreateDefaultInputPin()
{
	return CreateDialogPin(EGPD_Input, TEXT("Finish"));
}
