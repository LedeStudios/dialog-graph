// Copyright Lede Studios. All Rights Reserved.


#include "Dialog.h"

#include "UObject/ObjectSaveContext.h"

void UDialog::PreSave(const FObjectPreSaveContext SaveContext)
{
	if (OnPreSaveListener)
	{
		OnPreSaveListener();
	}
	
	UObject::PreSave(SaveContext);
}
