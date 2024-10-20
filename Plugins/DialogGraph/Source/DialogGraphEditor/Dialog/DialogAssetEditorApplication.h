// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"


class DIALOGGRAPHEDITOR_API FDialogAssetEditorApplication : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{

public:
	FDialogAssetEditorApplication();
	
public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InObject);

public:
	virtual FName GetToolkitFName() const override;
	
	virtual FText GetBaseToolkitName() const override;
	
	virtual FString GetWorldCentricTabPrefix() const override;
	
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual FString GetDocumentationLink() const override;

public:
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;

	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;
	
};
