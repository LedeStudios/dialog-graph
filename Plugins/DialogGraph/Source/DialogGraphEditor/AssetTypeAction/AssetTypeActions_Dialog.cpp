// Copyright Lede Studios. All Rights Reserved.


#include "AssetTypeActions_Dialog.h"

#include "DialogGraph/Data/Dialog.h"

FAssetTypeActions_Dialog::FAssetTypeActions_Dialog(const uint32 InCategory)
{
	Category = InCategory;
}

FText FAssetTypeActions_Dialog::GetName() const
{
	return INVTEXT("Dialog");
}

FColor FAssetTypeActions_Dialog::GetTypeColor() const
{
	return FColor::FromHex("#FC037F");
}

UClass* FAssetTypeActions_Dialog::GetSupportedClass() const
{
	return UDialog::StaticClass();
}

void FAssetTypeActions_Dialog::OpenAssetEditor(const TArray<UObject*>& InObjects,
	TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	FAssetTypeActions_Base::OpenAssetEditor(InObjects, EditWithinLevelEditor);
}

uint32 FAssetTypeActions_Dialog::GetCategories()
{
	return Category;
}
