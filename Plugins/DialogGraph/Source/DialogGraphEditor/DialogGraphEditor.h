// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FDialogGraphEditorModule : public IModuleInterface
{

private:
	TSharedPtr<FSlateStyleSet> DialogStyleSet;
	
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
