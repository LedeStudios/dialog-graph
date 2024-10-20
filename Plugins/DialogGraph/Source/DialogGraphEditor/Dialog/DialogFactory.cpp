// Copyright Lede Studios. All Rights Reserved.


#include "DialogFactory.h"

#include "DialogGraph/Data/Dialog.h"

UDialogFactory::UDialogFactory()
{
	SupportedClass = UDialog::StaticClass();
	bCreateNew = true;
}

UObject* UDialogFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                          UObject* Context, FFeedbackContext* Warn)
{
	check(InClass->IsChildOf(UDialog::StaticClass()));
	return NewObject<UDialog>(InParent, InClass, InName, Flags, Context);
}

