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
	const TSharedPtr<FDialogAssetEditorApplication> PinApp = App.Pin();

	return SNew(SVerticalBox)
	+ SVerticalBox::Slot()
	.FillHeight(1.f)
	.HAlign(HAlign_Fill)
	[
		SNew(SGraphEditor)
		.IsEditable(true)
		.GraphToEdit(PinApp->GetWorkingGraph())
	];
}

FText FDialogGraphTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("A graph view for dialog.");
}
