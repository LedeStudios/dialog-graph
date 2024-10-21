// Copyright Lede Studios. All Rights Reserved.


#include "DialogPropertyTabFactory.h"

#include "DialogAssetEditorApplication.h"
#include "DialogGraph/Data/Dialog.h"

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
	TSharedPtr<FDialogAssetEditorApplication> PinApp = App.Pin();
	
	return SNew(SVerticalBox)
	+ SVerticalBox::Slot().FillHeight(1.f).HAlign(HAlign_Fill)
	[
		SNew(STextBlock)
	];
}

FText FDialogPropertyTabFactory::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	return FText::FromString("A properties view for dialog.");
}
