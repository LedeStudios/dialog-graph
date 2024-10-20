// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"

class FDialogAssetEditorApplication;

class DIALOGGRAPHEDITOR_API FDialogApplicationMode : public FApplicationMode
{

public:
	TWeakPtr<FDialogAssetEditorApplication> App;

	FWorkflowAllowedTabSet Tabs;
	
public:
	explicit FDialogApplicationMode(const TSharedPtr<FDialogAssetEditorApplication>& InApp);

public:
	virtual void RegisterTabFactories(TSharedPtr<FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;
 
};
