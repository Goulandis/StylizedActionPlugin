#include "FSACurvesDataAssetEditorToolkit.h"

#include "FStylizedActionPluginCommands.h"
#include "FStylizedActionPluginStyle.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "SACurvesDataEditorToolkit"

const FName FSACurvesDataAssetEditorToolkit::ViewportTabId(TEXT("SACurvesDataAssetEditorViewport"));
const FName FSACurvesDataAssetEditorToolkit::PropertiesTabId(TEXT("SACurvesDataAssetEditorProperties"));

void FSACurvesDataAssetEditorToolkit::InitSACurvesDataAssetEditor(const EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
	SACurvesDataAsset = CastChecked<USACurvesDataAsset>(ObjectToEdit);
	SACurvesDataAsset->PostEditCallback.Unbind();
	SACurvesDataAsset->PostEditCallback.BindLambda([this]()
	{
		SACurvesDataAssetViewport->UpdateViewport(SharedThis(this));
	});
	SACurvesDataAssetViewport = SNew(SSACurvesDataAssetEditorViewport).SACurvesDataAssetEditorToolkit(SharedThis(this));
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>(TEXT("PropertyEditor"));
	
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = true;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.NotifyHook = this;

	SACurvesDataAssetDetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	SACurvesDataAssetDetailsView->SetObject(SACurvesDataAsset);
	SACurvesDataAssetDetailsView->OnFinishedChangingProperties().AddSP(this,&FSACurvesDataAssetEditorToolkit::OnPreopertyChanged);

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout(TEXT("StandaloneSACurvesDataAssetEidtorLayout"))
	->AddArea(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split(
			FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
			->Split(
					FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
					->SetSizeCoefficient(0.9f)
					->Split(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.6f)
						->AddTab(ViewportTabId,ETabState::OpenedTab)
						->SetHideTabWell(true)
					)
					->Split(
						FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
						->SetSizeCoefficient(0.2f)
						->Split(
							FTabManager::NewStack()
							->SetSizeCoefficient(0.7f)
							->AddTab(PropertiesTabId,ETabState::OpenedTab)
						)
					)
			)
		)
	);

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	FAssetEditorToolkit::InitAssetEditor(Mode,InitToolkitHost,FName(TEXT("SACurvesDataAssetEditorApp")),StandaloneDefaultLayout,bCreateDefaultToolbar,bCreateDefaultStandaloneMenu,ObjectToEdit);
}

FName FSACurvesDataAssetEditorToolkit::GetToolkitFName() const
{
	return FName(TEXT("SACurvesDataAssetEditor"));
}

FText FSACurvesDataAssetEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel","SACurvesDataAsset Editor");
}

FString FSACurvesDataAssetEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldContericTabPrefix","SACurveDataAsset").ToString();
}

FLinearColor FSACurvesDataAssetEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f,0.2f,0.5f,0.5f);
}

void FSACurvesDataAssetEditorToolkit::AddReferencedObjects(FReferenceCollector& Collector)
{
}

FString FSACurvesDataAssetEditorToolkit::GetReferencerName() const
{
	return TEXT("FSAAssetCurvesDataEditorToolkit");
}

TSharedPtr<FSACurvesDataAssetEditorToolkit> FSACurvesDataAssetEditorToolkit::CreateEditor(const EToolkitMode::Type Mode,const TSharedPtr<IToolkitHost>& InitToolkitHost, UObject* ObjectToEdit)
{
	TSharedPtr<FSACurvesDataAssetEditorToolkit> NewEditor = MakeShareable(new FSACurvesDataAssetEditorToolkit());
	NewEditor->InitSACurvesDataAssetEditor(Mode,InitToolkitHost,ObjectToEdit);
	return NewEditor;
}

void FSACurvesDataAssetEditorToolkit::ExtendToolbar()
{
	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension(
		TEXT("Asset"),
		EExtensionHook::After,
		GetToolkitCommands(),
		FToolBarExtensionDelegate::CreateSP(this,&FSACurvesDataAssetEditorToolkit::FillToolbar,GetToolkitCommands())
		);
	AddToolbarExtender(ToolbarExtender);
}

void FSACurvesDataAssetEditorToolkit::FillToolbar(FToolBarBuilder& ToolBarBuilder,const TSharedRef<FUICommandList> InToolkitCommands)
{
	const ISlateStyle* UIStyle = FSlateStyleRegistry::FindSlateStyle(FStylizedActionPluginStyle::GetStyleSetName());

	ToolBarBuilder.BeginSection(TEXT("SACurvesDataAsset"));
	//风格代码
	//...
	ToolBarBuilder.EndSection();
}

void FSACurvesDataAssetEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenuSACurvesDataAssetEditor","SACurvesDataAsset Editor"));
	TSharedRef<FWorkspaceItem> WorkspaceMenuCategortRef = WorkspaceMenuCategory.ToSharedRef();
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(ViewportTabId,FOnSpawnTab::CreateSP(this,&FSACurvesDataAssetEditorToolkit::SpawnTabViewport))
	.SetDisplayName(LOCTEXT("ViewportTab","Viewport"))
	.SetGroup(WorkspaceMenuCategortRef)
	.SetIcon(FSlateIcon(FAppStyle::Get().GetStyleSetName(),"LevelEditor.Tabs.Viewports"));

	InTabManager->RegisterTabSpawner(PropertiesTabId,FOnSpawnTab::CreateSP(this,&FSACurvesDataAssetEditorToolkit::SpawnTabProperties))
	.SetDisplayName(LOCTEXT("PropertiesTab","Details"))
	.SetGroup(WorkspaceMenuCategortRef)
	.SetIcon(FSlateIcon(FAppStyle::Get().GetStyleSetName(),"LevelEditor.Tabs.Details"));
}

void FSACurvesDataAssetEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(ViewportTabId);
	InTabManager->UnregisterTabSpawner(PropertiesTabId);
}

void FSACurvesDataAssetEditorToolkit::BindCommands()
{
	const FStylizedActionPluginCommands& Commands = FStylizedActionPluginCommands::Get();
	const TSharedRef<FUICommandList>& FUICommandList = GetToolkitCommands();
	//todo
	//...
}

TSharedRef<SDockTab> FSACurvesDataAssetEditorToolkit::SpawnTabViewport(const FSpawnTabArgs& Args)
{
	TSharedRef<SDockTab> DockableTab = SNew(SDockTab);
	SACurvesDatasAssetViewportTabContent = MakeShareable(new FEditorViewportTabContent());
	const FString LayoutId = FString("SACurvesDataAssetEditorViewport");
	SACurvesDatasAssetViewportTabContent->Initialize([this](const FAssetEditorViewportConstructionArgs& InConstructionArgs)
	{
		return SACurvesDataAssetViewport.ToSharedRef();
	},DockableTab,LayoutId);
	return DockableTab;
}

TSharedRef<SDockTab> FSACurvesDataAssetEditorToolkit::SpawnTabProperties(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId() == PropertiesTabId)

	return SNew(SDockTab).Label(LOCTEXT("SACurvesDataAssetEditorPropertiesTabTitle","Details"))[SACurvesDataAssetDetailsView.ToSharedRef()];
}

void FSACurvesDataAssetEditorToolkit::OnPreopertyChanged(const FPropertyChangedEvent& InEvent)
{
}

#undef LOCTEXT_NAMESPACE