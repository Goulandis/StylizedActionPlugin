// Fill out your copyright notice in the Description page of Project Settings.


#include "SACurvesDataAsset.h"

DEFINE_LOG_CATEGORY(SALog);

USACurvesDataAsset::USACurvesDataAsset(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	auto Curve = ScaleCurve.GetRichCurve();
	Curve->AddKey(0.f,0.f);
	Curve->AddKey(1.f,1.f);
	InitCurves();
}

void USACurvesDataAsset::BeginDestroy()
{
	UObject::BeginDestroy();
}
#if WITH_EDITOR
void USACurvesDataAsset::PostDuplicate(EDuplicateMode::Type DuplicateMode)
{
	UObject::PostDuplicate(DuplicateMode);
}

void USACurvesDataAsset::PostLoad()
{
	UObject::PostLoad();
}

void USACurvesDataAsset::PreEditUndo()
{
	UObject::PreEditUndo();
}

void USACurvesDataAsset::PostEditUndo()
{
	UObject::PostEditUndo();
}

void USACurvesDataAsset::PreEditChange(FProperty* PropertyAboutToChange)
{
	UObject::PreEditChange(PropertyAboutToChange);
}

void USACurvesDataAsset::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	AssetModify();
}

#endif

void USACurvesDataAsset::AssetModify()
{
	Modify();
	PostEditCallback.ExecuteIfBound();
}

void USACurvesDataAsset::InitCurves()
{
	FSAFrameData* FrameData = new FSAFrameData();
	//遍历FSAFrameData结构体，动态初始化风格化曲线资产
	for (TFieldIterator<FProperty> PropIt(FrameData->StaticStruct()); PropIt; ++PropIt)
	{
		FProperty* Property = *PropIt;
		FCurvesItem Item;
		Item.Scale.X.GetRichCurve()->AddKey(0.0f,1.0f);
		Item.Scale.Y.GetRichCurve()->AddKey(0.0f,1.0f);
		Item.Scale.Z.GetRichCurve()->AddKey(0.0f,1.0f);
		Curves.Add(FName(*Property->GetName()),Item);
	}
}
