// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FDialogGraphModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
