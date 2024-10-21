// Copyright Lede Studios. All Rights Reserved.


#include "DialogAssetEditorApplication.h"

#include "DialogApplicationMode.h"
#include "DialogGraph/Data/Dialog.h"

void FDialogAssetEditorApplication::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void FDialogAssetEditorApplication::InitEditor(const EToolkitMode::Type Mode,
											const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	WorkingAsset = Cast<UDialog>(InObject);

	// Init Editor
	InitAssetEditor(Mode, InitToolkitHost, TEXT("DialogEditor"),
		FTabManager::FLayout::NullLayout, true, true, ObjectsToEdit);

	// Apply App Mode
	AddApplicationMode(TEXT("DialogApplicationMode"), MakeShareable(new FDialogApplicationMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogApplicationMode"));
}

UDialog* FDialogAssetEditorApplication::GetWorkingAsset()
{
	return WorkingAsset;
}

FName FDialogAssetEditorApplication::GetToolkitFName() const
{
	return FName("DialogEditorApp");
}

FText FDialogAssetEditorApplication::GetBaseToolkitName() const
{
	return FText::FromString("DialogEditorApp");
}

FString FDialogAssetEditorApplication::GetWorldCentricTabPrefix() const
{
	return TEXT("DialogEditorApp");
}

FLinearColor FDialogAssetEditorApplication::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.988f, 0.012f, 0.498f, 0.5f);
}

FString FDialogAssetEditorApplication::GetDocumentationLink() const
{
	return TEXT("https://github.com/LedeStudios/dialog-graph");
}

void FDialogAssetEditorApplication::OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit)
{
}

void FDialogAssetEditorApplication::OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit)
{
}
