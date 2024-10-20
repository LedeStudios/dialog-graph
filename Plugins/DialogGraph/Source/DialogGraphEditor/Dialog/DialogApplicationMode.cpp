// Copyright Lede Studios. All Rights Reserved.


#include "DialogApplicationMode.h"

#include "DialogAssetEditorApplication.h"
#include "DialogTabFactory.h"

FDialogApplicationMode::FDialogApplicationMode(const TSharedPtr<FDialogAssetEditorApplication>& InApp)
: FApplicationMode(TEXT("DialogApplicationMode"))
{
	App = InApp;
	Tabs.RegisterFactory(MakeShareable(new FDialogTabFactory(InApp)));

	TabLayout = FTabManager::NewLayout("DialogApplicationMode_Layout_v1")
	->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewStack()
			->AddTab(FName(TEXT("DialogTab")), ETabState::OpenedTab)
		)
	);
}

void FDialogApplicationMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	const TSharedPtr<FDialogAssetEditorApplication> PinApp = App.Pin();
	PinApp->PushTabFactories(Tabs);
	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FDialogApplicationMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();
}

void FDialogApplicationMode::PostActivateMode()
{
	FApplicationMode::PostActivateMode();
}
