// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedPreviewScene.h"
#include "EditorViewportClient.h"
#include "SAssetEditorViewport.h"
#include "SCommonEditorViewportToolbarBase.h"

class FSACurvesDataAssetEditorToolkit;
class USACurvesDataAsset;

class STYLIZEDACTIONPLUGIN_API SSACurvesDataAssetEditorViewport : public SAssetEditorViewport,public ICommonEditorViewportToolbarInfoProvider,public FGCObject
{
public:
	SLATE_BEGIN_ARGS(SSACurvesDataAssetEditorViewport){}
	SLATE_ARGUMENT(TWeakPtr<FSACurvesDataAssetEditorToolkit>,SACurvesDataAssetEditorToolkit)
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs);
	void UpdateViewport(TSharedPtr<FSACurvesDataAssetEditorToolkit> SACurvesDataAssetEditorToolkit);
	void GenerateSphere(USACurvesDataAsset* SACurvesDataAsset);

	virtual TSharedRef<SEditorViewport> GetViewportWidget() override;
	virtual TSharedPtr<FExtender> GetExtenders() const override;
	virtual void OnFloatingButtonClicked() override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	virtual FString GetReferencerName() const override{return TEXT("SACurvesDataAssetEditorViewport");}

protected:
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;

private:
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;
	TSharedPtr<FEditorViewportClient> EditorViewportClient;
	TWeakPtr<FSACurvesDataAssetEditorToolkit> SACurvesDataAssetEditorToolkitPtr;
};

class FSAAssetEditorViewportClient : public FEditorViewportClient
{
public:
	using Super = FEditorViewportClient;
	FSAAssetEditorViewportClient(FPreviewScene* InPreviewScene,const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);
	virtual void Tick(float DeltaSeconds) override;
};
