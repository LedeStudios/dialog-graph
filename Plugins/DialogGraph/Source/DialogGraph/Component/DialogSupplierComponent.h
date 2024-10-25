// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogSupplierComponent.generated.h"


class UDialog;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DIALOGGRAPH_API UDialogSupplierComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDialogSupplierComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Diolog")
	TArray<UDialog*> Dialogs;

public:
	UDialog* GetDialog(int32 InIndex);

	TArray<UDialog*> GetDialogs();
	
};
