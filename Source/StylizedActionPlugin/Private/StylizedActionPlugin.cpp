// Copyright Epic Games, Inc. All Rights Reserved.

#include "StylizedActionPlugin.h"

#include "AssetToolsModule.h"
#include "FStylizedActionPluginStyle.h"
#include "FStylizedActionPluginCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "EditorAssetLibrary.h"
#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "IAssetTools.h"
#include "SubobjectDataSubsystem.h"
#include "StylizedActionPlugin/Asset/FSACurvesDataAssetAction.h"
#include "StylizedActionPlugin/Asset/SACurvesDataAsset.h"

#define LOCTEXT_NAMESPACE "FStylizedActionPluginModule"
EAssetTypeCategories::Type FStylizedActionPluginModule::CurvesDataAssetCategory;

class UEditorUtilityWidgetBlueprint;

void FStylizedActionPluginModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	//注册工具栏按钮及触发回调
	FStylizedActionPluginStyle::Initialize();
	FStylizedActionPluginStyle::ReloadTextures();

	FStylizedActionPluginCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FStylizedActionPluginCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FStylizedActionPluginModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FStylizedActionPluginModule::RegisterMenus));

	//注册USACurvesDataAsset资产
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
	auto RegisterAssetTypeAction = [&](TSharedRef<IAssetTypeActions> Action)
	{
		AssetTools.RegisterAssetTypeActions((Action));
		CreatedAssetTypeActions.Add(Action);
	};
	RegisterAssetTypeAction(MakeShareable(new FSACurvesDataAssetAction));
	CurvesDataAssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("风格化动作曲线")),NSLOCTEXT("Editor","SACurvesDataAsset","风格化动作资产"));
}

void FStylizedActionPluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	//注销工具栏按钮
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FStylizedActionPluginStyle::Shutdown();

	FStylizedActionPluginCommands::Unregister();

	//注销USACurvesDataAsset资产
	if(FModuleManager::Get().IsModuleLoaded(TEXT("AssetTools")))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>(TEXT("AssetTools")).Get();
		for (auto CreatedAssetTypeAction : CreatedAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(CreatedAssetTypeAction.ToSharedRef());
		}
	}
	CreatedAssetTypeActions.Empty();
}

void FStylizedActionPluginModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	// FText DialogText = FText::Format(
	// 						LOCTEXT("PluginButtonDialogText", "Add code to {0} in {1} to override this button's actions"),
	// 						FText::FromString(TEXT("FStylizedActionEditorModule::PluginButtonClicked()")),
	// 						FText::FromString(TEXT("StylizedActionEditor.cpp"))
	// 				   );
	// FMessageDialog::Open(EAppMsgType::Ok, DialogText);

	RegistEditorUtilityWidget();
}

void FStylizedActionPluginModule::RegistEditorUtilityWidget()
{
	UObject * Blueprint = UEditorAssetLibrary::LoadAsset(FString(TEXT(
		"EditorUtilityWidgetBlueprint'/StylizedActionPlugin/UMG/WCurveDataEdit.WCurveDataEdit'")));

	if(Blueprint)
	{
		UEditorUtilityWidgetBlueprint* EditorWidget = Cast<UEditorUtilityWidgetBlueprint>(Blueprint);
		
		if(EditorWidget)
		{
			UEditorUtilitySubsystem* EditorUtilitySubsystem = 
				GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
	
			EditorUtilitySubsystem->SpawnAndRegisterTab(EditorWidget);
		}
	}
}


TSharedRef<FSACurvesDataAssetEditorToolkit> FStylizedActionPluginModule::CreateSaCurvesDataAssetEditor(
	const EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* SACurvesDataAsset)
{
	TSharedRef<FSACurvesDataAssetEditorToolkit> NewSACurvesDataAssetEditor(new FSACurvesDataAssetEditorToolkit());
	NewSACurvesDataAssetEditor->InitSACurvesDataAssetEditor(Mode,InitToolkitHost,SACurvesDataAsset);
	return NewSACurvesDataAssetEditor;
}

void FStylizedActionPluginModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FStylizedActionPluginCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FStylizedActionPluginCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FStylizedActionPluginModule, StylizedActionPlugin)