// Copyright Lede Studios. All Rights Reserved.


#include "DialogTabFactory.h"
#include "DialogAssetEditorApplication.h"
#include "DialogGraph/Data/Dialog.h"

FDialogTabFactory::FDialogTabFactory(const TSharedPtr<FDialogAssetEditorApplication>& InApp)
: FWorkflowTabFactory(FName("DialogTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString("Dialog Label");
	ViewMenuDescription = FText::FromString("Dialog Description");
	ViewMenuTooltip = FText::FromString("Dialog Tooltip");
}

TSharedRef<SWidget> FDialogTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	TSharedPtr<FDialogAssetEditorApplication> PinApp = App.Pin();
	FPropertyEditorModule& PropertyEditor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));

	FDetailsViewArgs ViewArgs;
	ViewArgs.bAllowSearch = false;
	ViewArgs.bHideSelectionTip = true;
	ViewArgs.bLockable = false;
	ViewArgs.bSearchInitialKeyFocus = true;
	ViewArgs.bUpdatesFromSelection = false;
	ViewArgs.NotifyHook = nullptr;
	ViewArgs.bShowOptions = true;
	ViewArgs.bShowModifiedPropertiesOption = false;
	ViewArgs.bShowScrollBar = false;

	const TSharedPtr<IDetailsView> View = PropertyEditor.CreateDetailView(ViewArgs);
	View->SetObject(PinApp->GetWorkingAsset());
	
	return SNew(SVerticalBox)
	+ SVerticalBox::Slot().FillHeight(1.f).HAlign(HAlign_Fill) [ View.ToSharedRef() ];
}

FText FDialogTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("tool tip text for dialog tab.");
}
