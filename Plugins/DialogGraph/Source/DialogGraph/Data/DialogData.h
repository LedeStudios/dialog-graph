// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogData.generated.h"

USTRUCT(BlueprintType)
struct FDialogChoice
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditAnywhere)
	FText Line;
	
};

UCLASS(BlueprintType)
class DIALOGGRAPH_API UDialogNodeData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="Dialog")
	FText Speaker;

	UPROPERTY(EditAnywhere, Category="Dialog")
	FText Line;

	UPROPERTY(EditAnywhere, Category="Dialog")
	FTransform CameraOffset;

	UPROPERTY(EditAnywhere, Category="Dialog")
	TObjectPtr<USoundBase> SoundToPlay;

	UPROPERTY(EditAnywhere, Category="Dialog")
	TArray<FDialogChoice> Choices;
	
};
