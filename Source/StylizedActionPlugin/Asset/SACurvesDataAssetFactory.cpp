// Fill out your copyright notice in the Description page of Project Settings.


#include "SACurvesDataAssetFactory.h"
#include "SACurvesDataAsset.h"

#define LOCTEXT_NAMESPACE "SACurvesDataAssetFactory"

USACurvesDataAssetFactory::USACurvesDataAssetFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = USACurvesDataAsset::StaticClass();
}

UObject* USACurvesDataAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	USACurvesDataAsset* NewAsset = NewObject<USACurvesDataAsset>(InParent,InClass,InName,Flags | RF_Transactional);
	return NewAsset;
}

FText USACurvesDataAssetFactory::GetToolTip() const
{
	return LOCTEXT("SACurvesDataAssetTooltip","创建风格化动作曲线资产");
}

#undef LOCTEXT_NAMESPACE
