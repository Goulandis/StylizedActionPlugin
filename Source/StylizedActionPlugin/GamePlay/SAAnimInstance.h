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
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Stylized Action")
	FSAFrameData FrameData;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Stylized Action")
	USACurvesDataAsset* CurvesAsset;
private:
	int32 CurvesAssetKeyMaxIndex;
public:
	UFUNCTION()
	void OnCurvesChanged();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Stylized Action")
	USACurvesDataAsset* GetSACurvesAsset();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Stylized Action")
	int32 GetFrameMaxIndex();
	UFUNCTION(BlueprintCallable,Category="Stylized Action")
	FSAFrameData GetSingleFrameData(int32 Index);
	UFUNCTION(BlueprintCallable,Category="Stylized Action")
	FTransform GetFrameDataFromCurve(int32 Index,USACurvesDataAsset* CurveAsset);
};
