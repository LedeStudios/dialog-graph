// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogPlayerComponent.generated.h"


class UDialogNode;
class UDialog;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogStartDelegate, UDialog*, Dialog);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogFinishDelegate, UDialog*, Dialog);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDialogChoiceDelegate, UDialog*, Dialog, UDialogNode*, PrevNode, UDialogNode*, CurrentNode, int32, SelectedIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDialogWaitFinishDelegate, UDialog*, Dialog, UDialogNode*, CurrentNode);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIALOGGRAPH_API UDialogPlayerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogPlayerComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialog|Data")
	TObjectPtr<UDialog> Dialog;

public:
	void SetDialog(UDialog* InDialog) { Dialog = InDialog; }
	UDialog* GetDialog() const { return Dialog.Get(); }

private:
	TWeakObjectPtr<UDialogNode> CurrentNode;
	TObjectPtr<UAudioComponent> CurrentSound;

public:
	UDialogNode* GetCurrentNode() const { return CurrentNode.Get(); }
	
public:
	UFUNCTION(BlueprintCallable, Category="Dialog")
	void PlayFromStart();

	UFUNCTION(BlueprintCallable, Category="Dialog")
	void Play();

	UFUNCTION(BlueprintCallable, Category="Dialog")
	void Choice(int32 Index);
	
	UFUNCTION(BlueprintCallable, Category="Dialog")
	void Skip();

	UFUNCTION(BlueprintCallable, Category="Dialog")
	void PlaySoundOnly();

	UFUNCTION(BlueprintCallable, Category="Dialog")
	void StopSoundOnly();
	
private:
	void Finish();

public:
	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogStartDelegate OnDialogStart;

	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogFinishDelegate OnDialogFinish;

	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogChoiceDelegate OnDialogChoice;

	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogWaitFinishDelegate OnDialogWaitFinish;
	
};
