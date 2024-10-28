// Copyright Lede Studios. All Rights Reserved.


#include "DialogPlayerComponent.h"

#include "Components/AudioComponent.h"
#include "DialogGraph/Data/Dialog.h"
#include "DialogGraph/Data/DialogData.h"
#include "DialogGraph/Data/DialogRuntimeGraph.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(DialogComponent, Log, All);

UDialogPlayerComponent::UDialogPlayerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDialogPlayerComponent::PlayFromStart()
{
	CurrentNode.Reset();
	Play();
}

void UDialogPlayerComponent::Play()
{
	Choice(0);
}

void UDialogPlayerComponent::Choice(int32 Index)
{
	if (Dialog == nullptr)
	{
		UE_LOG(DialogComponent, Error, TEXT("UDialogComponent::Choice: Empty dialog."));
		return;
	}
	
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

	// Play dialog actions
	PlaySoundOnly();

	// Call Choice Delegate
	if (OnDialogChoice.IsBound())
	{
		OnDialogChoice.Broadcast(Dialog, PrevNode, CurrentNode.Get(), Index);
	}
}

void UDialogPlayerComponent::Skip()
{
	if (Dialog == nullptr)
	{
		UE_LOG(DialogComponent, Error, TEXT("UDialogComponent::Skip: Empty dialog."));
		return;
	}
	
	Finish();
}

void UDialogPlayerComponent::PlaySoundOnly()
{
	// Stop Prev Sound
	if (CurrentSound)
	{
		CurrentSound->Stop();
	}

	// Play Current Sound
	if (USoundBase* Sound = CurrentNode->NodeData->SoundToPlay)
	{
		const FVector SoundLoc = CurrentNode->NodeData->SoundLocation;
		CurrentSound = UGameplayStatics::SpawnSoundAtLocation(this, Sound, SoundLoc);
		CurrentSound->Play();
	}
}

void UDialogPlayerComponent::StopSoundOnly()
{
	if (CurrentSound)
	{
		CurrentSound->Stop();
	}
	CurrentSound = nullptr;
}

void UDialogPlayerComponent::Finish()
{
	StopSoundOnly();
	CurrentNode.Reset();
	
	if (OnDialogFinish.IsBound())
	{
		OnDialogFinish.Broadcast(Dialog);
	}
}


