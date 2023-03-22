// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "SAData.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SACurvesDataAsset.generated.h"

USTRUCT()
struct FViewportObject
{
	GENERATED_USTRUCT_BODY()
	TObjectPtr<UStaticMeshComponent> Component;
	FTransform Transform;
	FViewportObject(){};
	FViewportObject(TObjectPtr<UStaticMeshComponent> Component,FTransform Transform):Component(Component),Transform(Transform){}
};

UCLASS(BlueprintType,Blueprintable,AutoExpandCategories="风格化动作曲线")
class STYLIZEDACTIONPLUGIN_API USACurvesDataAsset : public UObject
{
	GENERATED_UCLASS_BODY()
	DECLARE_DELEGATE(FPostEditCallback)
public:
	virtual void BeginDestroy() override;

#if WITH_EDITOR
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PreEditUndo() override;
	virtual void PostEditUndo() override;
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
	
	void AssetModify();
	void InitCurves();
public:
	UPROPERTY(EditAnywhere,Category="SACurvesDataAsset",meta=(Subcategory="Growth",XAxisName="Normalized Age",YAxisName="Scale Factor"))
	FRuntimeFloatCurve ScaleCurve;
	UPROPERTY(EditAnywhere,Category="SACurvesDataAsset",meta=(Subcategory="Growth"))
	TObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere,Category="SACurvesDataAsset",meta=(Subcategory="Growth"))
	uint32 Num;

	UPROPERTY(EditAnywhere,Category="SACurvesDataAsset",meta=(Subcategory="Growth"))
	UDebugSkelMeshComponent* PreviewMeshComponent;
	UPROPERTY(EditAnywhere,Category="SACurvesDataAsset",meta=(Subcategory="Growth",XAxisName="Normalized Age",YAxisName="Scale Factor"))
	TMap<FName,FCurvesItem> Curves;
	
	FPostEditCallback PostEditCallback;
	TArray<FViewportObject> ViewportComponents;
};
