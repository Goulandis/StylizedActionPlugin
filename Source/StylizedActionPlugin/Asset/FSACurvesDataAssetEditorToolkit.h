#pragma once

#include "CoreMinimal.h"
#include "EditorViewportTabContent.h"
#include "Toolkits/SimpleAssetEditor.h"
#include "Misc/NotifyHook.h"
#include "SACurvesDataAsset.h"
#include "SSACurvesDataAssetEditorViewport.h"

class STYLIZEDACTIONPLUGIN_API FSACurvesDataAssetEditorToolkit : public FAssetEditorToolkit,public FNotifyHook,public FGCObject
{
public:
	void InitSACurvesDataAssetEditor(const EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost,UObject* ObjectToEdit);

	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override;

	static TSharedPtr<FSACurvesDataAssetEditorToolkit> CreateEditor(const EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost,UObject* ObjectToEdit);

private:
	void ExtendToolbar();
	void FillToolbar(FToolBarBuilder& ToolBarBuilder,const TSharedRef<FUICommandList> InToolkitCommands);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	void BindCommands();

	TSharedRef<SDockTab> SpawnTabViewport(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> SpawnTabProperties(const FSpawnTabArgs& Args);

	void OnPreopertyChanged(const FPropertyChangedEvent& InEvent);

public:
	USACurvesDataAsset* SACurvesDataAsset;
private:
	static const FName ViewportTabId;
	static const FName PropertiesTabId;

	TSharedPtr<FEditorViewportTabContent> SACurvesDatasAssetViewportTabContent;
	TSharedPtr<IDetailsView> SACurvesDataAssetDetailsView;
	TSharedPtr<SSACurvesDataAssetEditorViewport> SACurvesDataAssetViewport;
};
