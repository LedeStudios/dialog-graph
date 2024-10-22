// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"


class FDialogAssetEditorApplication;

class DIALOGGRAPHEDITOR_API FDialogPropertyTabFactory : public FWorkflowTabFactory
{

protected:
	TWeakPtr<FDialogAssetEditorApplication> App;
	
public:
	explicit FDialogPropertyTabFactory(const TSharedPtr<FDialogAssetEditorApplication>& InApp);

public:
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
	
};
