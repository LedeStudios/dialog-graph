// Copyright Lede Studios. All Rights Reserved.


#include "DialogApplicationMode.h"

#include "DialogAssetEditorApplication.h"
#include "DialogGraphTabFactory.h"
#include "DialogPropertyTabFactory.h"

FDialogApplicationMode::FDialogApplicationMode(const TSharedPtr<FDialogAssetEditorApplication>& InApp)
: FApplicationMode(TEXT("DialogApplicationMode"))
{
	App = InApp;
	Tabs.RegisterFactory(MakeShareable(new FDialogGraphTabFactory(InApp)));
	Tabs.RegisterFactory(MakeShareable(new FDialogPropertyTabFactory(InApp)));

	TabLayout = FTabManager::NewLayout("DialogApplicationMode_Layout_v1")
	->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.75f)
				->AddTab(FName(TEXT("DialogGraphTab")), ETabState::OpenedTab)
			)
			->Split(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.25f)
				->AddTab(FName(TEXT("DialogPropertyTab")), ETabState::OpenedTab)
			)
		)
	);
}

void FDialogApplicationMode::RegisterTabFactories(const TSharedPtr<FTabManager> InTabManager)
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
