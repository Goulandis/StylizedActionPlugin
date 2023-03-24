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
class STYLIZEDACTIONPLUGIN_API USACurvesDataAsset : public UObject,public IInterface_PreviewMeshProvider
{
	GENERATED_UCLASS_BODY()
	DECLARE_DELEGATE(FPostEditCallback)
public:
	virtual void BeginDestroy() override;

#if WITH_EDITOR
	//UObject 函数重写
	virtual void PostDuplicate(EDuplicateMode::Type DuplicateMode) override;
	virtual void PostLoad() override;
	virtual void PreEditUndo() override;
	virtual void PostEditUndo() override;
	virtual void PreEditChange(FProperty* PropertyAboutToChange) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

	//IInterface_PreviewMeshProvider 接口实现
	virtual void SetPreviewMesh(USkeletalMesh* PreviewMesh, bool bMarkAsDirty) override;
	virtual USkeletalMesh* GetPreviewMesh() const override;
#endif
	
	void AssetModify();
	void InitCurves();
	void InitSkeletalMesh();
public:
	UPROPERTY(EditAnywhere,Category="Stylized Action")
	FRuntimeFloatCurve ScaleCurve;
	UPROPERTY(EditAnywhere,Category="Stylized Action")
	TObjectPtr<UStaticMesh> Mesh;
	UPROPERTY(EditAnywhere,Category="Stylized Action")
	uint32 Num;

	//动画预览
	UPROPERTY(EditAnywhere,duplicatetransient, AssetRegistrySearchable,Category="Stylized Action")
	TSoftObjectPtr<class USkeletalMesh> PreSkeletalMesh;
	UPROPERTY(EditAnywhere,Category="Stylized Action")
	FTransform PreSkeletalTransform;
	UPROPERTY(EditAnywhere,Category="Stylized Action")
	UAnimBlueprint* PreviewAnimation;

	//风格化动作曲线
	UPROPERTY(EditAnywhere,Category="Stylized Action")
	TMap<FName,FCurvesItem> Curves;
	
	FPostEditCallback PostEditCallback;
	TArray<FViewportObject> ViewportComponents;
};
