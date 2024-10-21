// Copyright Lede Studios. All Rights Reserved.


#include "DialogGraphTabFactory.h"
#include "DialogAssetEditorApplication.h"
#include "DialogGraph/Data/Dialog.h"

FDialogGraphTabFactory::FDialogGraphTabFactory(const TSharedPtr<FDialogAssetEditorApplication>& InApp)
: FWorkflowTabFactory(FName("DialogGraphTab"), InApp)
{
	App = InApp;
	TabLabel = FText::FromString("Graph");
	ViewMenuDescription = FText::FromString("Dialog Graph");
	ViewMenuTooltip = FText::FromString("Dialog Graph");
}

TSharedRef<SWidget> FDialogGraphTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
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

FText FDialogGraphTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("A graph view for dialog.");
}
