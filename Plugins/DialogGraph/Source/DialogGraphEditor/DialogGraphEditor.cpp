// Copyright Lede Studios. All Rights Reserved.

#include "DialogGraphEditor.h"

#include "IAssetTools.h"
#include "Dialog/DialogTypeAction.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

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

	// Setup and Register Dialog Style Set
	DialogStyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogEditorStyle")));
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("DialogGraph");
	DialogStyleSet->SetContentRoot(Plugin->GetContentDir());

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(
		DialogStyleSet->RootToContentDir(TEXT("dialog"), TEXT(".png")),
		FVector2D(512.f, 512.f));
	DialogStyleSet->Set(TEXT("ClassThumbnail.Dialog"), ThumbnailBrush);
	
	FSlateImageBrush* IconBrush = new FSlateImageBrush(
		DialogStyleSet->RootToContentDir(TEXT("dialog"), TEXT(".png")),
		FVector2D(512.f, 512.f));
	DialogStyleSet->Set(TEXT("ClassIcon.Dialog"), IconBrush);

	// FSlateImageBrush* NodeAddBrush = new FSlateImageBrush(
	// DialogStyleSet->RootToContentDir(TEXT("add"), TEXT(".png")),
	// FVector2D(512.f, 512.f));
	// DialogStyleSet->Set(TEXT("DialogEditor.NodeAppPinIcon"), NodeAddBrush);
	//
	// FSlateImageBrush* NodeDeleteBrush = new FSlateImageBrush(
	// DialogStyleSet->RootToContentDir(TEXT("delete"), TEXT(".png")),
	// FVector2D(512.f, 512.f));
	// DialogStyleSet->Set(TEXT("DialogEditor.NodeDeletePinIcon"), NodeDeleteBrush);
	//
	// FSlateImageBrush* NodeDeleteNodeBrush = new FSlateImageBrush(
	// DialogStyleSet->RootToContentDir(TEXT("pin_delete"), TEXT(".png")),
	// FVector2D(512.f, 512.f));
	// DialogStyleSet->Set(TEXT("DialogEditor.NodeDeleteNodeIcon"), NodeDeleteNodeBrush);

	FSlateStyleRegistry::RegisterSlateStyle(*DialogStyleSet);
	
	UE_LOG(LogTemp, Warning, TEXT("Load Dialog Graph Editor Plugin."))
}

void FDialogGraphEditorModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*DialogStyleSet);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogGraphEditorModule, DialogGraphEditor)