// Copyright Lede Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "UObject/Object.h"

/**
 * 
 */
class DIALOGGRAPHEDITOR_API FAssetTypeActions_Dialog : public FAssetTypeActions_Base
{

protected:
	uint32 Category;
	
public:
	explicit FAssetTypeActions_Dialog(uint32 InCategory);
	
public:
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	virtual uint32 GetCategories() override;
	
};
