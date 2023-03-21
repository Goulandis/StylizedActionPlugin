#include "FSACurvesDataAssetAction.h"

#include "EditorStyleSet.h"
#include "FSACurvesDataAssetEditorToolkit.h"
#include "SACurvesDataAsset.h"
#include "StylizedActionPlugin.h"

#define LOCTEXT_NAMESPACE "SACurveDataAsset"

FText FSACurvesDataAssetAction::GetName() const
{
	return NSLOCTEXT("AssetTypeActions","FSACurveDataAssetAction","风格化动作曲线");
}

FColor FSACurvesDataAssetAction::GetTypeColor() const
{
	return FColor(0,85,200);
}

UClass* FSACurvesDataAssetAction::GetSupportedClass() const
{
	return USACurvesDataAsset::StaticClass();
}

uint32 FSACurvesDataAssetAction::GetCategories()
{
	return FStylizedActionPluginModule::GetAssetCategory();
}

void FSACurvesDataAssetAction::OpenAssetEditor(const TArray<UObject*>& InObjects,TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid()?EToolkitMode::WorldCentric:EToolkitMode::Standalone;
	for(auto ObjIt = InObjects.CreateConstIterator();ObjIt;++ObjIt)
	{
		if(auto Object = Cast<USACurvesDataAsset>(*ObjIt))
		{
			FSACurvesDataAssetEditorToolkit::CreateEditor(Mode,Mode == EToolkitMode::WorldCentric?EditWithinLevelEditor:TSharedPtr<IToolkitHost>(),Object);
		}
	}
}

TSharedPtr<SWidget> FSACurvesDataAssetAction::GetThumbnailOverlay(const FAssetData& AssetData) const
{
	const FSlateDynamicImageBrush* Icon = new FSlateDynamicImageBrush(
		*(FPaths::ProjectPluginsDir()/"StylizedActionPlugin"/"Resources"/"SAIcon.png"),
		FVector2D(16,16));
	 return SNew(SBorder)
			.BorderImage(FEditorStyle::GetNoBrush())
			.Visibility(EVisibility::HitTestInvisible)
			.Padding(FMargin(0.0f,0.0f,0.0f,3.0f))
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Bottom)
			[
				SNew(SImage).Image(Icon)
			];
}
