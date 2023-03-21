// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "AssetTypeCategories.h"
#include "IAssetTypeActions.h"
#include "StylizedActionPlugin/Asset/FSACurvesDataAssetEditorToolkit.h"

class FStylizedActionPluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void RegistEditorUtilityWidget();

	static EAssetTypeCategories::Type GetAssetCategory(){return CurvesDataAssetCategory;}
	TSharedRef<FSACurvesDataAssetEditorToolkit> CreateSACurvesDataAssetEditor(const EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost,UObject* SACurvesDataAsset);
private:
	void RegisterMenus();

private:
	static EAssetTypeCategories::Type CurvesDataAssetCategory;
	
	TSharedPtr<class FUICommandList> PluginCommands;
	TArray<TSharedPtr<IAssetTypeActions>> CreatedAssetTypeActions;
};
