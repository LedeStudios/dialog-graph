// Copyright Lede Studios. All Rights Reserved.


#include "DialogTypeAction.h"

#include "DialogGraph/Data/Dialog.h"
#include "DialogAssetEditorApplication.h"

FDialogTypeAction::FDialogTypeAction(const EAssetTypeCategories::Type InCategory)
{
	Category = InCategory;
}

FText FDialogTypeAction::GetName() const
{
	return FText::FromString("Dialog");
}

FColor FDialogTypeAction::GetTypeColor() const
{
	return FColor::FromHex("#FC037F");
}

UClass* FDialogTypeAction::GetSupportedClass() const
{
	return UDialog::StaticClass();
}

void FDialogTypeAction::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	const EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (UObject* Object : InObjects)
	{
		if (UDialog* Dialog = Cast<UDialog>(Object))
		{
			const TSharedRef<FDialogAssetEditorApplication> NewEditor(new FDialogAssetEditorApplication());
			NewEditor->InitEditor(Mode, EditWithinLevelEditor, Dialog);
		}
	}
}

uint32 FDialogTypeAction::GetCategories()
{
	return Category;
}
