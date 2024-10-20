// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DialogFactory.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGGRAPHEDITOR_API UDialogFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogFactory();
	
public:
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};
