// Fill out your copyright notice in the Description page of Project Settings.


#include "SSACurvesDataAssetEditorViewport.h"

#include "FSACurvesDataAssetEditorToolkit.h"
#include "AdvancedPreviewScene.h"
#include "PreviewScene.h"
#include "UObject/ObjectMacros.h"
#include "EditorViewportClient.h"
#include "SCommonEditorViewportToolbarBase.h"
#include "SEditorViewport.h"
#include "AssetViewerSettings.h"
#include "SSAEditorViewportToolbar.h"
#include "Persona/Private/SAnimViewportToolBar.h"

SSACurvesDataAssetEditorViewport::~SSACurvesDataAssetEditorViewport()
{
}

void SSACurvesDataAssetEditorViewport::Construct(const FArguments& InArgs)
{
	SACurvesDataAssetEditorToolkitPtr = InArgs._SACurvesDataAssetEditorToolkit;
	TSharedPtr<FSACurvesDataAssetEditorToolkit> SACurvesDataAssetEditorToolkit = SACurvesDataAssetEditorToolkitPtr.Pin();
	check(SACurvesDataAssetEditorToolkitPtr.IsValid());
	PreviewScene = MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues()));
	PreviewScene->SetFloorVisibility(false);
	GenerateSphere(SACurvesDataAssetEditorToolkit->SACurvesDataAsset);
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

void SSACurvesDataAssetEditorViewport::UpdateViewport(TSharedPtr<FSACurvesDataAssetEditorToolkit> SACurvesDataAssetEditorToolkit)
{
	if(EditorViewportClient.IsValid() && PreviewScene.IsValid())
	{
		UAssetViewerSettings* Setting = UAssetViewerSettings::Get();
		const int32 ProfilesIndex = PreviewScene->GetCurrentProfileIndex();
		if(Setting->Profiles.IsValidIndex(ProfilesIndex))
		{
			GenerateSphere(SACurvesDataAssetEditorToolkit->SACurvesDataAsset);
			PreviewScene->UpdateScene(Setting->Profiles[ProfilesIndex]);
		}
	}
}

void SSACurvesDataAssetEditorViewport::GenerateSphere(USACurvesDataAsset* SACurvesDataAsset)
{
	if(!SACurvesDataAsset)
	{
		return;
	}
	for(FViewportObject& Ele:SACurvesDataAsset->ViewportComponents)
	{
		PreviewScene->RemoveComponent(Ele.Component);
	}
	// SACurvesDataAsset->ViewportComponents.Empty();
	// FRichCurve* Curve = SACurvesDataAsset->ScaleCurve.GetRichCurve();
	// if(SACurvesDataAsset->Mesh)
	// {
	// 	for(uint32 i=0;i<SACurvesDataAsset->Num;++i)
	// 	{
	// 		UStaticMeshComponent* Component = NewObject<UStaticMeshComponent>(GetTransientPackage(),NAME_None,EObjectFlags::RF_Transient);
	// 		Component->SetMobility(EComponentMobility::Static);
	// 		FComponentReregisterContext ReregisterContext(Component);
	// 		Component->SetStaticMesh(SACurvesDataAsset->Mesh);
	// 		FTransform Transform;
	// 		Transform.SetLocation(FVector(0,i*100,i*100*Curve->Eval(i*1.0/SACurvesDataAsset->Num)));
	// 		PreviewScene->AddComponent(Component,Transform);
	// 		SACurvesDataAsset->ViewportComponents.Add(FViewportObject(Component,Transform));
	// 	}
	// }
	if(SkeletalMeshComponent == nullptr)
	{
		SkeletalMeshComponent = MakeShareable(NewObject<USkeletalMeshComponent>(GetTransientPackage(),NAME_None,EObjectFlags::RF_Transient));
	}
	SkeletalMeshComponent->SetMobility(EComponentMobility::Static);
	PreviewScene->AddComponent(SkeletalMeshComponent.Get(),SACurvesDataAsset->PreSkeletalTransform);
	SkeletalMeshComponent->SetSkeletalMesh(SACurvesDataAsset->GetPreviewMesh());
	FComponentReregisterContext ReregisterSkeletalMeshContext(SkeletalMeshComponent.Get());
}

TSharedRef<SEditorViewport> SSACurvesDataAssetEditorViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> SSACurvesDataAssetEditorViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void SSACurvesDataAssetEditorViewport::OnFloatingButtonClicked()
{
}

void SSACurvesDataAssetEditorViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
}

TSharedRef<FEditorViewportClient> SSACurvesDataAssetEditorViewport::MakeEditorViewportClient()
{
	EditorViewportClient = MakeShareable(new FSAAssetEditorViewportClient(PreviewScene.Get(),SharedThis(this)));
	EditorViewportClient->SetRealtime(true);
	return EditorViewportClient.ToSharedRef();
}

TSharedPtr<SWidget> SSACurvesDataAssetEditorViewport::MakeViewportToolbar()
{
	//return SNew(SCommonEditorViewportToolbarBase,SharedThis(this));
	return SNew(SSAEditorViewportToolbar);
}

FSAAssetEditorViewportClient::FSAAssetEditorViewportClient(FPreviewScene* InPreviewScene,const TWeakPtr<SEditorViewport>& InEditorViewportWidget)
	: FEditorViewportClient(nullptr,InPreviewScene,InEditorViewportWidget)
{
	bSetListenerPosition = false;
	SetRealtime(true);
	EngineShowFlags.Grid = false;
	SetViewLocation(FVector(-3000,0,2000));
	SetViewRotation(FRotator(-35.f,0.f,0.f));
}

void FSAAssetEditorViewportClient::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!GIntraFrameDebuggingGameThread)
	{
		PreviewScene->GetWorld()->Tick(IsRealtime()?LEVELTICK_All:LEVELTICK_TimeOnly,DeltaSeconds);
	}
	
	FEditorViewportClient::Tick(DeltaSeconds);
}
