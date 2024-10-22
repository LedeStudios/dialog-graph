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

UEdGraphPin* UDialogGraphFinishNode::CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name)
{
	const FName Category = TEXT("Inputs");
	const FName SubCategory = TEXT("FinishPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, Name);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}
