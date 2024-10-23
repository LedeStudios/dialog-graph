// Copyright Lede Studios. All Rights Reserved.


#include "DialogComponent.h"

#include "DialogGraph/Data/Dialog.h"
#include "DialogGraph/Data/DialogRuntimeGraph.h"

UDialogComponent::UDialogComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogComponent::PlayFromStart()
{
	CurrentNode.Reset();
	Play();
}

void UDialogComponent::Play()
{
	Choice(0);
}

void UDialogComponent::Choice(int32 Index)
{
	UDialogNode* PrevNode = CurrentNode.Get();
	
	// Find next dialog node.
	if (!CurrentNode.IsValid())
	{
		CurrentNode = Dialog->Graph->Nodes[0];
	}
	else
	{
		CurrentNode = Dialog->Graph->FindNextNodeByIndex(CurrentNode.Get(), Index);

		// If the next dialogue node cannot be retrieved, stop the execution.
		if (!CurrentNode.IsValid())
		{
			Finish();
		}
	}

	// If the current node is the starting node of the dialogue, move to the next node and play.
	if (CurrentNode->NodeType == EDialogNodeType::Start)
	{
		// Call Start Delegate
		if (OnDialogStart.IsBound())
		{
			OnDialogStart.Broadcast(Dialog);
		}
		Choice(0);
		return;
	}

	// If the current node is the dialogue completion node, stop the execution.
	if (CurrentNode->NodeType == EDialogNodeType::Finish)
	{
		Finish();
		return;
	}

	// Call Choice Delegate
	if (OnDialogChoice.IsBound())
	{
		OnDialogChoice.Broadcast(Dialog, PrevNode, CurrentNode.Get(), Index);
	}
}

void UDialogComponent::Skip()
{
	CurrentNode.Reset();
	Finish();
}

void UDialogComponent::Finish() const
{
	if (OnDialogFinish.IsBound())
	{
		OnDialogFinish.Broadcast(Dialog);
	}
}


