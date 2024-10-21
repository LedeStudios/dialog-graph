// Copyright Lede Studios. All Rights Reserved.

#include "DialogGraphEditor.h"

#include "EdGraphUtilities.h"
#include "IAssetTools.h"
#include "SGraphPin.h"
#include "Dialog/DialogTypeAction.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FDialogGraphModule"

class SDialogGraphPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SDialogGraphPin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPin)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InGraphPin);
	}

protected:
	virtual FSlateColor GetPinColor() const override
	{
		return FSlateColor(FLinearColor(0.2f, 1.f, 0.2f));
	}
};

struct FDialogPinFactory : FGraphPanelPinFactory
{
public:
	virtual ~FDialogPinFactory() override {}

	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override
	{
		if (FName(TEXT("DialogPin")) == Pin->PinType.PinSubCategory)
		{
			return SNew(SDialogGraphPin, Pin);
		}
		return FGraphPanelPinFactory::CreatePin(Pin);
	}
};

void FDialogGraphEditorModule::StartupModule()
{
	// Load AssetTools Module
	IAssetTools& AssetToolsModule =  FAssetToolsModule::GetModule().Get();

	// Register Dialog Asset
	const EAssetTypeCategories::Type DialogCategory = AssetToolsModule.RegisterAdvancedAssetCategory(
		FName(TEXT("Dialogs")), FText::FromString("Dialogs"));
	const TSharedPtr<FDialogTypeAction> DialogAssetTypeActions = MakeShareable(new FDialogTypeAction(DialogCategory));
	AssetToolsModule.RegisterAssetTypeActions(DialogAssetTypeActions.ToSharedRef());

	// Setup and Register Dialog Style Set
	DialogStyleSet = MakeShareable(new FSlateStyleSet(TEXT("DialogEditorStyle")));
	const TSharedPtr<IPlugin> Plugin = IPluginManager::Get().FindPlugin("DialogGraph");
	DialogStyleSet->SetContentRoot(Plugin->GetContentDir());

	FSlateImageBrush* ThumbnailBrush = new FSlateImageBrush(
		DialogStyleSet->RootToContentDir(TEXT("dialog"), TEXT(".png")),
		FVector2D(512.f, 512.f));
	DialogStyleSet->Set(TEXT("ClassThumbnail.Dialog"), ThumbnailBrush);
	
	FSlateImageBrush* IconBrush = new FSlateImageBrush(
		DialogStyleSet->RootToContentDir(TEXT("dialog"), TEXT(".png")),
		FVector2D(512.f, 512.f));
	DialogStyleSet->Set(TEXT("ClassIcon.Dialog"), IconBrush);

	FSlateStyleRegistry::RegisterSlateStyle(*DialogStyleSet);

	// Pin Style
	PinFactory = MakeShareable(new FDialogPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(PinFactory);
	
	UE_LOG(LogTemp, Warning, TEXT("Load Dialog Graph Editor Plugin."))
}

void FDialogGraphEditorModule::ShutdownModule()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*DialogStyleSet);
	FEdGraphUtilities::UnregisterVisualPinFactory(PinFactory);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogGraphEditorModule, DialogGraphEditor)