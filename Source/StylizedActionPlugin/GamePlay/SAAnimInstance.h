// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "../Asset/SAData.h"
#include "../Asset/SACurvesDataAsset.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SAAnimInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STYLIZEDACTIONPLUGIN_API USAAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="SAAnimInstance")
	FSAFrameData FrameData;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="SAAnimInstance")
	USACurvesDataAsset* Curves;
public:
	int32 GetMaxFrameIndex();
	FSAFrameData GetSingleFrameData(int32 Index);
	FTransform GetFrameDataFromCurve(int32 Index,USACurvesDataAsset* CurveAsset);
};
