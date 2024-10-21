// Copyright Lede Studios. All Rights Reserved.


#include "DialogAssetEditorApplication.h"

#include "DialogApplicationMode.h"
#include "DialogGraphNode.h"
#include "DialogGraphSchema.h"
#include "DialogGraph/Data/Dialog.h"
#include "DialogGraph/Data/DialogRuntimeGraph.h"
#include "Kismet2/BlueprintEditorUtils.h"

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

	// Bind Handler
	GraphChangeHandler = WorkingGraph->AddOnGraphChangedHandler(
		FOnGraphChanged::FDelegate::CreateSP(this, &FDialogAssetEditorApplication::OnGraphChanged));
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

	for (UEdGraphNode* Node : WorkingGraph->Nodes)
	{
		// Create Node
		UDialogNode* RuntimeNode = NewObject<UDialogNode>(RuntimeGraph);
		RuntimeNode->Position = FVector2D(Node->NodePosX, Node->NodePosY);

		for (UEdGraphPin* Pin : Node->Pins)
		{
			// Create Pin
			UDialogPin* RuntimePin = NewObject<UDialogPin>(RuntimeNode);
			RuntimePin->PinName = Pin->PinName;
			RuntimePin->PinId = Pin->PinId;

			// Make Pin Connection
			if (Pin->HasAnyConnections() && Pin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->PinId, Pin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}

			// Add Pin to Node
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

		// Add Node to Graph
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
		return;
	}

	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;

	// Load Nodes
	for (UDialogNode* RuntimeNode : WorkingAsset->Graph->Nodes)
	{
		UDialogGraphNode* Node = NewObject<UDialogGraphNode>(WorkingGraph);
		Node->CreateNewGuid();
		Node->NodePosX = RuntimeNode->Position.X;
		Node->NodePosY = RuntimeNode->Position.Y;

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
	WorkingGraph->RemoveOnGraphChangedHandler(GraphChangeHandler);
	FAssetEditorToolkit::OnClose();
}

void FDialogAssetEditorApplication::OnGraphChanged(const FEdGraphEditAction& EditAction)
{
	UpdateWorkingAssetFromGraph();
}
