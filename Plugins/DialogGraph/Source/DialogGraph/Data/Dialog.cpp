// Copyright Lede Studios. All Rights Reserved.


#include "Dialog.h"

#include "DialogGraph/Component/DialogPlayerComponent.h"
#include "UObject/ObjectSaveContext.h"

FTransform UDialog::GetCameraPosition(UDialogPlayerComponent* DialogPlayer) const
{
	FTransform Transform;
	switch (CameraPositionType)
	{
	case ECameraPositionType::Absolute:
		Transform = CameraPosition;
		break;
	case ECameraPositionType::Relative:
		Transform = DialogPlayer->GetOwner()->GetTransform() + CameraPosition;
	}
	return Transform;
}

void UDialog::PreSave(const FObjectPreSaveContext SaveContext)
{
	if (OnPreSaveListener)
	{
		OnPreSaveListener();
	}
	
	UObject::PreSave(SaveContext);
}
