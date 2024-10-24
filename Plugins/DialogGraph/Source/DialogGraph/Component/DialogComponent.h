// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"


class UDialogNode;
class UDialog;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogStartDelegate, UDialog*, Dialog);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogFinishDelegate, UDialog*, Dialog);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnDialogChoiceDelegate, UDialog*, Dialog, UDialogNode*, PrevNode, UDialogNode*, CurrentNode, int32, SelectedIndex);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIALOGGRAPH_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog|Data")
	TObjectPtr<UDialog> Dialog;

public:
	void SetDialog(UDialog* InDialog) { Dialog = InDialog; }
	UDialog* GetDialog() const { return Dialog.Get(); }

private:
	TWeakObjectPtr<UDialogNode> CurrentNode;

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

private:
	void Finish() const;

public:
	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogStartDelegate OnDialogStart;

	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogFinishDelegate OnDialogFinish;

	UPROPERTY(BlueprintAssignable, Category="Dialog")
	FOnDialogChoiceDelegate OnDialogChoice;
	
};
