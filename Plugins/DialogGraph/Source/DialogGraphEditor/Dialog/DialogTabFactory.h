﻿// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"


class FDialogAssetEditorApplication;

class DIALOGGRAPHEDITOR_API FDialogTabFactory : public FWorkflowTabFactory
{

protected:
	TWeakPtr<FDialogAssetEditorApplication> Editor;
	
public:
	explicit FDialogTabFactory(const TSharedPtr<FDialogAssetEditorApplication>& InApp);

public:
	virtual TSharedRef<SWidget> CreateTabBody(const FWorkflowTabSpawnInfo& Info) const override;

	virtual FText GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const override;
	
};