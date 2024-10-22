// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphNode.h"
#include "Framework/Commands/UIAction.h"
#include "ToolMenu.h"
#include "DialogGraph/Data/DialogData.h"


FText UDialogGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	if (NodeData->Speaker.IsEmpty()) {
		return FText::FromString("Enter Dialog Speaker");
	}
	return NodeData->Speaker;
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
		FText::FromString("Add Choice"),
		FText::FromString("Creates a new choice"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([Node]()
		{
			Node->GetNodeData()->Choices.Add(FDialogChoice());
			Node->SyncPinsWithChoices();
			
			Node->GetGraph()->NotifyGraphChanged();
			Node->GetGraph()->Modify();
		}))
	);

	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString("Delete Choice"),
		FText::FromString("Deletes the last choice"),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([Node]()
		{
			UDialogNodeData* Data = Node->GetNodeData();
			if (Data->Choices.Num() > 0)
			{
				Data->Choices.RemoveAt(Data->Choices.Num() - 1);
			}

			Node->SyncPinsWithChoices();
			Node->GetGraph()->NotifyGraphChanged();
			Node->GetGraph()->Modify();
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

UEdGraphPin* UDialogGraphNode::CreateDialogPin(const EEdGraphPinDirection Direction, const FName Name)
{
	const FName Category = (Direction == EGPD_Input) ? TEXT("Inputs") : TEXT("Outputs");
	const FName SubCategory = TEXT("DialogPin");

	UEdGraphPin* Pin = CreatePin(Direction, Category, Name);
	Pin->PinType.PinSubCategory = SubCategory;

	return Pin;
}

void UDialogGraphNode::SyncPinsWithChoices()
{
	const UDialogNodeData* Data = GetNodeData();

	// Remove All Output Pins
	for (int Index = Pins.Num() - 1; Index > 0; --Index)
	{
		RemovePinAt(Index - 1, EGPD_Output);
	}
	
	// Add Regular Dialog Pin
	const int32 ChoiceNum = Data->Choices.Num();
	if (ChoiceNum < 1)
	{
		UEdGraphPin* Pin = CreateDialogPin(EGPD_Output, TEXT("Continue"));
		return;
	}
	
	// Or Choice Dialog Pin
	for (int Index = 0; Index < ChoiceNum; ++Index)
	{
		UEdGraphPin* Pin = CreateDialogPin(EGPD_Output, FName(Data->Choices[Index].Line.ToString()));
	}
	
}
