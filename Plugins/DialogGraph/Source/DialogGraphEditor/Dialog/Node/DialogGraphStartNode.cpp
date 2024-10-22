// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphStartNode.h"

FText UDialogGraphStartNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Start");
}

FLinearColor UDialogGraphStartNode::GetNodeTitleColor() const
{
	return FLinearColor(FColor::Red);
}

bool UDialogGraphStartNode::CanUserDeleteNode() const
{
	return false;
}

UEdGraphPin* UDialogGraphStartNode::CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name)
{
	const FName Category = TEXT("Outputs");
	const FName SubCategory = TEXT("StartPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, Name);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

void UDialogGraphStartNode::CreateDefaultOutputPin()
{
	CreateDialogPin(EGPD_Output, TEXT("Start"));
}
