#include "FStylizedActionPluginStyle.h"
//#include "StylizedActionEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FStylizedActionPluginStyle::StyleInstance = nullptr;

void FStylizedActionPluginStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FStylizedActionPluginStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FStylizedActionPluginStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("StylizedActionEditorStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FStylizedActionPluginStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("StylizedActionEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("StylizedActionPlugin")->GetBaseDir() / TEXT("Resources"));

	Style->Set("StylizedActionEditor.PluginAction", new IMAGE_BRUSH(TEXT("SAIcon"), CoreStyleConstants::Icon32x32));
	return Style;
}

void FStylizedActionPluginStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FStylizedActionPluginStyle::Get()
{
	return *StyleInstance;
}