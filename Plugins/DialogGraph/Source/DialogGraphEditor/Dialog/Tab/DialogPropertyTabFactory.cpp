// Copyright Lede Studios. All Rights Reserved.


#include "DialogPropertyTabFactory.h"

#include "DialogGraph/Data/Dialog.h"
#include "DialogGraphEditor/Dialog/DialogAssetEditorApplication.h"

FDialogPropertyTabFactory::FDialogPropertyTabFactory(const TSharedPtr<FDialogAssetEditorApplication>& InApp)
: FWorkflowTabFactory(FName("DialogPropertyTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString("Properties");
	ViewMenuDescription = FText::FromString("Dialog Properties");
	ViewMenuTooltip = FText::FromString("Dialog Properties");
}

TSharedRef<SWidget> FDialogPropertyTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	const TSharedPtr<FDialogAssetEditorApplication> PinApp = App.Pin();
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

	FDetailsViewArgs Args;
	Args.bAllowSearch = false;
	Args.bHideSelectionTip = true;
	Args.bLockable = false;
	Args.bSearchInitialKeyFocus = true;
	Args.bUpdatesFromSelection = false;
	Args.NotifyHook = nullptr;
	Args.bShowOptions = true;
	Args.bShowModifiedPropertiesOption = false;
	Args.bShowScrollBar = false;

	const TSharedPtr<IDetailsView> DetailsView = PropertyEditor.CreateDetailView(Args);
	DetailsView->SetObject(PinApp->GetWorkingAsset());

	const TSharedPtr<IDetailsView> SelectedNodeDetailsView = PropertyEditor.CreateDetailView(Args);
	SelectedNodeDetailsView->SetObject(nullptr);
	PinApp->SetSelectedNodeDetailsView(SelectedNodeDetailsView);
	
	return SNew(SVerticalBox)
	+ SVerticalBox::Slot().FillHeight(1.f).HAlign(HAlign_Fill)
	[
		DetailsView.ToSharedRef()
	]
	+ SVerticalBox::Slot().FillHeight(1.f).HAlign(HAlign_Fill)
	[
		SelectedNodeDetailsView.ToSharedRef()
	];
}

FText FDialogPropertyTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("A properties view for dialog.");
}
