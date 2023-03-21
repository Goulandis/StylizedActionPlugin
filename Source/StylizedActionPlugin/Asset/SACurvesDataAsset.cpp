// Fill out your copyright notice in the Description page of Project Settings.


#include "SACurvesDataAsset.h"

USACurvesDataAsset::USACurvesDataAsset(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	auto Curve = ScaleCurve.GetRichCurve();
	Curve->AddKey(0.f,0.f);
	Curve->AddKey(1.f,1.f);
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
