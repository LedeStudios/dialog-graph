// Copyright Lede Studios. All Rights Reserved.


#include "DialogAssetEditorApplication.h"

#include "DialogApplicationMode.h"
#include "Node/DialogGraphDialogNode.h"
#include "DialogGraphSchema.h"
#include "DialogGraph/Data/Dialog.h"
#include "DialogGraph/Data/DialogData.h"
#include "DialogGraph/Data/DialogRuntimeGraph.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Node/DialogGraphFinishNode.h"
#include "Node/DialogGraphStartNode.h"

DEFINE_LOG_CATEGORY_STATIC(DialogEditorApp, Log, All)

void FDialogAssetEditorApplication::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void FDialogAssetEditorApplication::InitEditor(const EToolkitMode::Type Mode,
											const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	TArray<UObject*> ObjectsToEdit;
	ObjectsToEdit.Add(InObject);

	WorkingAsset = Cast<UDialog>(InObject);
	WorkingAsset->SetPreSaveListener([this]()
	{
		OnWorkingAssetPreSave();
	});

	WorkingGraph = FBlueprintEditorUtils::CreateNewGraph(
		WorkingAsset, NAME_None, UEdGraph::StaticClass(), UDialogGraphSchema::StaticClass());

	// Init Editor
	InitAssetEditor(Mode, InitToolkitHost, TEXT("DialogEditor"),
		FTabManager::FLayout::NullLayout, true, true, ObjectsToEdit);

	// Apply App Mode
	AddApplicationMode(TEXT("DialogApplicationMode"), MakeShareable(new FDialogApplicationMode(SharedThis(this))));
	SetCurrentMode(TEXT("DialogApplicationMode"));

	// Load Graph
	UpdateEditorGraphFromWorkingAsset();
}

void FDialogAssetEditorApplication::UpdateWorkingAssetFromGraph() const
{
	if (WorkingAsset == nullptr || WorkingGraph == nullptr)
	{
		return;
	}

	UDialogGraph* RuntimeGraph = NewObject<UDialogGraph>(WorkingAsset);
	WorkingAsset->Graph = RuntimeGraph;

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UDialogPin*> IdToPinMap;

	// Save Nodes
	for (UEdGraphNode* Node : WorkingGraph->Nodes)
	{
		UDialogNode* RuntimeNode = NewObject<UDialogNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(Node->NodePosX, Node->NodePosY);
		
		// Save Pins
		for (UEdGraphPin* Pin : Node->Pins)
		{
			UDialogPin* RuntimePin = NewObject<UDialogPin>(RuntimeNode);
			RuntimePin->PinName = Pin->PinName;
			RuntimePin->PinId = Pin->PinId;

			if (Pin->HasAnyConnections() && Pin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->PinId, Pin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}

			IdToPinMap.Add(Pin->PinId, RuntimePin);
			if (Pin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}

		if (Node->IsA(UDialogGraphDialogNode::StaticClass()))
		{
			const UDialogGraphDialogNode* GraphNode = Cast<UDialogGraphDialogNode>(Node);
			RuntimeNode->NodeData = GraphNode->GetNodeData();
		}
		else if (Node->IsA(UDialogGraphStartNode::StaticClass()))
		{
			RuntimeNode->NodeType = EDialogNodeType::Start;
		}
		else if (Node->IsA(UDialogGraphFinishNode::StaticClass()))
		{
			RuntimeNode->NodeType = EDialogNodeType::Finish;
		}
		
		RuntimeGraph->Nodes.Add(RuntimeNode);
	}

	// Save Pin Connections
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UDialogPin* First = IdToPinMap[Connection.first];
		UDialogPin* Second = IdToPinMap[Connection.second];
		First->Connection = Second;
	}
}

void FDialogAssetEditorApplication::UpdateEditorGraphFromWorkingAsset() const
{
	if (WorkingAsset->Graph == nullptr)
	{
		WorkingGraph->GetSchema()->CreateDefaultNodesForGraph(*WorkingGraph);
		return;
	}

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	// Load Nodes
	for (UDialogNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogGraphNodeBase* Node = nullptr;
		switch (RuntimeNode->NodeType)
		{
		case EDialogNodeType::Start:
			Node = NewObject<UDialogGraphStartNode>(WorkingGraph);
			break;
		case EDialogNodeType::Finish:
			Node = NewObject<UDialogGraphFinishNode>(WorkingGraph);
			break;
		case EDialogNodeType::Dialog:
			Node = NewObject<UDialogGraphDialogNode>(WorkingGraph);
			break;
		}
		
		Node->CreateNewGuid();
		Node->NodePosX = RuntimeNode->Position.X;
		Node->NodePosY = RuntimeNode->Position.Y;

		// Load Node Data
		if (RuntimeNode->NodeData != nullptr)
		{
			Node->SetNodeData(DuplicateObject(RuntimeNode->NodeData, RuntimeNode));
		}
		else
		{
			if (RuntimeNode->NodeType == EDialogNodeType::Dialog)
			{
				Node->SetNodeData(NewObject<UDialogNodeData>(RuntimeNode));
			}
		}

		// Load Input Pins
		if (RuntimeNode->InputPin != nullptr)
		{
			UDialogPin* RuntimePin = RuntimeNode->InputPin;
			UEdGraphPin* Pin = Node->CreateDialogPin(EGPD_Input, RuntimePin->PinName);
			Pin->PinId = RuntimePin->PinId;

			if (RuntimePin->Connection != nullptr)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(RuntimePin->PinId, RuntimePin->Connection->PinId);
				Connections.Add(Connection);
			}
			IdToPinMap.Add(RuntimePin->PinId, Pin);
		}

		// Load Output Pins
		for (UDialogPin* RuntimePin : RuntimeNode->OutputPins)
		{
			UEdGraphPin* Pin = Node->CreateDialogPin(EGPD_Output, RuntimePin->PinName);
			Pin->PinId = RuntimePin->PinId;

			if (RuntimePin->Connection != nullptr)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(RuntimePin->PinId, RuntimePin->Connection->PinId);
				Connections.Add(Connection);
			}
			IdToPinMap.Add(RuntimePin->PinId, Pin);
		}

		// Add Node to Graph
		WorkingGraph->AddNode(Node, true, true);
	}

	// Load Pin Connections
	for (std::pair<FGuid, FGuid> Connection : Connections)
	{
		UEdGraphPin* From = IdToPinMap[Connection.first];
		UEdGraphPin* To = IdToPinMap[Connection.second];
		From->LinkedTo.Add(To);
		To->LinkedTo.Add(From);
	}
}

UDialog* FDialogAssetEditorApplication::GetWorkingAsset()
{
	return WorkingAsset;
}

UEdGraph* FDialogAssetEditorApplication::GetWorkingGraph()
{
	return WorkingGraph;
}

void FDialogAssetEditorApplication::SetWorkingGraphUI(const TSharedPtr<SGraphEditor>& InWorkingGraphUI)
{
	WorkingGraphUI = InWorkingGraphUI;
}

UDialogGraphDialogNode* FDialogAssetEditorApplication::GetSelectedNode(const FGraphPanelSelectionSet& InSelection)
{
	for (UObject* Obj : InSelection)
	{
		if (UDialogGraphDialogNode* Node = Cast<UDialogGraphDialogNode>(Obj); Node != nullptr)
		{
			return Node;
		}
	}
	return nullptr;
}

void FDialogAssetEditorApplication::SetSelectedNodeDetailsView(const TSharedPtr<IDetailsView>& InDetailsView)
{
	SelectedNodeDetailsView = InDetailsView;
	SelectedNodeDetailsView->OnFinishedChangingProperties().AddRaw(this, &FDialogAssetEditorApplication::OnNodeDetailViewPropertiesUpdated);
}

FName FDialogAssetEditorApplication::GetToolkitFName() const
{
	return FName("DialogEditorApp");
}

FText FDialogAssetEditorApplication::GetBaseToolkitName() const
{
	return FText::FromString("DialogEditorApp");
}

FString FDialogAssetEditorApplication::GetWorldCentricTabPrefix() const
{
	return TEXT("DialogEditorApp");
}

FLinearColor FDialogAssetEditorApplication::GetWorldCentricTabColorScale() const
{
	return FLinearColor(FColor::FromHex("#FC037F"));
}

FString FDialogAssetEditorApplication::GetDocumentationLink() const
{
	return TEXT("https://github.com/LedeStudios/dialog-graph");
}

void FDialogAssetEditorApplication::OnToolkitHostingStarted(const TSharedRef<IToolkit>& Toolkit)
{
}

void FDialogAssetEditorApplication::OnToolkitHostingFinished(const TSharedRef<IToolkit>& Toolkit)
{
}

void FDialogAssetEditorApplication::OnClose()
{
	UpdateWorkingAssetFromGraph();
	WorkingAsset->SetPreSaveListener(nullptr);
	FAssetEditorToolkit::OnClose();
}

void FDialogAssetEditorApplication::OnWorkingAssetPreSave() const
{
	// Update asset from the graph just before saving it.
	UpdateWorkingAssetFromGraph();
}

void FDialogAssetEditorApplication::OnNodeDetailViewPropertiesUpdated(const FPropertyChangedEvent& InEvent)
{
	if (WorkingGraphUI != nullptr)
	{
		if (UDialogGraphDialogNode* Node = GetSelectedNode(WorkingGraphUI->GetSelectedNodes()); Node != nullptr)
		{
			Node->SyncPinsWithChoices();
		}
		WorkingGraphUI->NotifyGraphChanged();
	}
}

void FDialogAssetEditorApplication::OnGraphSelectionChanged(const FGraphPanelSelectionSet& InSelection)
{
	if (const UDialogGraphDialogNode* Node = GetSelectedNode(InSelection); Node != nullptr)
	{
		SelectedNodeDetailsView->SetObject(Node->GetNodeData());
	}
	else
	{
		SelectedNodeDetailsView->SetObject(nullptr);
	}
}
