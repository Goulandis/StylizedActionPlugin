// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "SACurvesDataAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class STYLIZEDACTIONPLUGIN_API USACurvesDataAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	USACurvesDataAssetFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual FText GetToolTip() const override;
	
};
