// Copyright Lede Studios. All Rights Reserved.

#include "DialogGraphEditor.h"

#include "IAssetTools.h"
#include "Dialog/DialogTypeAction.h"

#define LOCTEXT_NAMESPACE "FDialogGraphModule"

void FDialogGraphEditorModule::StartupModule()
{
	// Load AssetTools Module
	IAssetTools& AssetToolsModule =  FAssetToolsModule::GetModule().Get();

	// Register Dialog Asset
	const EAssetTypeCategories::Type DialogCategory = AssetToolsModule.RegisterAdvancedAssetCategory(
		FName(TEXT("Dialogs")), FText::FromString("Dialogs"));
	const TSharedPtr<FDialogTypeAction> DialogAssetTypeActions = MakeShareable(new FDialogTypeAction(DialogCategory));
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