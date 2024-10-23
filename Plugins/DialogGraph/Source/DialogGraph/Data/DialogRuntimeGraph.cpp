// Copyright Lede Studios. All Rights Reserved.


#include "DialogRuntimeGraph.h"

UDialogNode* UDialogGraph::FindNextNode(UDialogNode* CurrentNode)
{
	int32 Index = 0;
	return FindNextNode(CurrentNode, Index);
}

UDialogNode* UDialogGraph::FindNextNode(UDialogNode* CurrentNode, int32& Index)
{
	Index = FMath::Clamp(Index, 0, CurrentNode->OutputPins.Num() - 1);
	if (const UDialogPin* OutPin = CurrentNode->OutputPins[Index])
	{
		if (const UDialogPin* NextPin = OutPin->Connection)
		{
			for (UDialogNode* Node : Nodes)
			{
				if (NextPin == Node->InputPin)
				{
					return Node;
				}
			}
		}
	}
	return nullptr;
}
