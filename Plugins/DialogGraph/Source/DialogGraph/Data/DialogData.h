// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogData.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNodeSelectedDelegate);

USTRUCT(BlueprintType)
struct FDialogChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	FText Line;
	
};

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialogNodeData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	FText Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	FText Line;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	FTransform CameraOffset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	TObjectPtr<USoundBase> SoundToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialog")
	TArray<FDialogChoice> Choices;
	
};
