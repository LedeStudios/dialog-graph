// Copyright Lede Studios. All Rights Reserved.

#include "DialogGraphEditor.h"

#include "IAssetTools.h"
#include "AssetTypeAction/AssetTypeActions_Dialog.h"

#define LOCTEXT_NAMESPACE "FDialogGraphModule"

void FDialogGraphEditorModule::StartupModule()
{
	// Load AssetTools Module
	IAssetTools& AssetToolsModule =  FAssetToolsModule::GetModule().Get();

	// Register Dialog Asset
	const uint32 AssetCategoryBit = AssetToolsModule.RegisterAdvancedAssetCategory(
		FName(TEXT("Dialog")), LOCTEXT("DialogAssetCategory", "Dialogs"));
	const TSharedPtr<FAssetTypeActions_Dialog> DialogAssetTypeActions = MakeShareable(new FAssetTypeActions_Dialog(AssetCategoryBit));
	AssetToolsModule.RegisterAssetTypeActions(DialogAssetTypeActions.ToSharedRef());
	
	UE_LOG(LogTemp, Warning, TEXT("Load Dialog Graph Editor Plugin."))
}

void FDialogGraphEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogGraphEditorModule, DialogGraphEditor)