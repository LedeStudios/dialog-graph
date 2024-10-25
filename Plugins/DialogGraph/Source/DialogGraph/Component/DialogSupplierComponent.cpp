// Copyright Lede Studios. All Rights Reserved.


#include "DialogSupplierComponent.h"


UDialogSupplierComponent::UDialogSupplierComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UDialog* UDialogSupplierComponent::GetDialog(int32 InIndex)
{
	InIndex = FMath::Clamp(InIndex, 0, Dialogs.Num());
	return Dialogs[InIndex];
}

TArray<UDialog*> UDialogSupplierComponent::GetDialogs()
{
	return Dialogs;
}


