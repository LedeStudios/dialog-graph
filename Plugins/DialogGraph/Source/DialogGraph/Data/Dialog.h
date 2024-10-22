// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Dialog.generated.h"


class UDialogGraph;

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialog : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Dialog")
	FString DialogId;

	UPROPERTY(EditAnywhere, Category="Dialog")
	FTransform CameraPosition;
	
	UPROPERTY()
	TObjectPtr<UDialogGraph> Graph;

public:
	void SetPreSaveListener(const std::function<void()>& InOnPreSaveListener) { OnPreSaveListener = InOnPreSaveListener; }

private:
	std::function<void()> OnPreSaveListener;

public:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
};



