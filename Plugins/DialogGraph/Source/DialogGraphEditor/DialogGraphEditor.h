// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

struct FDialogPinFactory;

class FDialogGraphEditorModule : public IModuleInterface
{

private:
	TSharedPtr<FSlateStyleSet> DialogStyleSet;
	TSharedPtr<FDialogPinFactory> PinFactory;
	
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
