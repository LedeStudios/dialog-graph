// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "WorkflowOrientedApp/WorkflowCentricApplication.h"


class UDialog;

class DIALOGGRAPHEDITOR_API FDialogAssetEditorApplication : public FWorkflowCentricApplication, public FEditorUndoClient, public FNotifyHook
{

protected:
	TObjectPtr<UDialog> WorkingAsset;

	TObjectPtr<UEdGraph> WorkingGraph;

public:
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

	void InitEditor(const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InObject);

public:
	void UpdateWorkingAssetFromGraph() const;

	void UpdateEditorGraphFromWorkingAsset() const;
	
	UDialog* GetWorkingAsset();

	UEdGraph* GetWorkingGraph();
	
public:
	virtual FName GetToolkitFName() const override;
	
	virtual FText GetBaseToolkitName() const override;
	
	virtual FString GetWorldCentricTabPrefix() const override;
	
	virtual FLinearColor GetWorldCentricTabColorScale() const override;

	virtual FString GetDocumentationLink() const override;

public:
	virtual void OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit) override;

	virtual void OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit) override;

public:
	virtual void OnClose() override;

	FDelegateHandle GraphChangeHandler;
	void OnGraphChanged(const FEdGraphEditAction& EditAction);
	
};
