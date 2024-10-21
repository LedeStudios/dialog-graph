// Copyright Lede Studios. All Rights Reserved.


#include "DialogTabFactory.h"
#include "DialogAssetEditorApplication.h"

FDialogTabFactory::FDialogTabFactory(const TSharedPtr<FDialogAssetEditorApplication>& InApp)
: FWorkflowTabFactory(FName("DialogTab"), InApp)
{
	Editor = InApp;
	TabLabel = FText::FromString("Dialog Label");
	ViewMenuDescription = FText::FromString("Dialog Description");
	ViewMenuTooltip = FText::FromString("Dialog Tooltip");
}

TSharedRef<SWidget> FDialogTabFactory::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	return SNew(STextBlock).Text(FText::FromString("text widget for dialog tab."));
}

FText FDialogTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("tool tip text for dialog tab.");
}
