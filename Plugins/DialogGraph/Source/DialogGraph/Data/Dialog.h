// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Dialog.generated.h"


class UDialogPlayerComponent;
class UDialogGraph;

UENUM(BlueprintType)
enum class ECameraPositionType : uint8
{
	Relative,
	Absolute
};

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialog : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	FString DialogId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	FTransform CameraPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	ECameraPositionType CameraPositionType = ECameraPositionType::Relative;
	
	UPROPERTY(BlueprintReadOnly, Category="Dialog")
	TObjectPtr<UDialogGraph> Graph;

public:
	UFUNCTION(BlueprintCallable, Category="Dialog")
	FTransform GetCameraPosition(UDialogPlayerComponent* DialogPlayer) const;
	
public:
	void SetPreSaveListener(const std::function<void()>& InOnPreSaveListener) { OnPreSaveListener = InOnPreSaveListener; }

private:
	std::function<void()> OnPreSaveListener;

public:
	virtual void PreSave(FObjectPreSaveContext SaveContext) override;
	
};



