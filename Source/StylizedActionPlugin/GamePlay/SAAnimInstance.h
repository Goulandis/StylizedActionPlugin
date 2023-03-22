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
	UPROPERTY(BlueprintReadWrite,Category="Stylized Action")
	FSAFrameData FrameData;
	UPROPERTY(BlueprintReadWrite,Category="Stylized Action")
	FSAFrameData TargetFramwData;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Stylized Action")
	USACurvesDataAsset* CurvesAsset;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Stylized Action")
	ESAType SAType;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Stylized Action")
	EPawnState PawnState;
private:
	int32 CurvesAssetKeyMaxIndex;
public:
	UFUNCTION()
	void OnCurvesChanged();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Stylized Action")
	bool IsEditor();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Stylized Action")
	USACurvesDataAsset* GetSACurvesAsset();
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Stylized Action")
	int32 GetFrameMaxIndex();
	UFUNCTION(BlueprintCallable,Category="Stylized Action")
	FSAFrameData GetSingleFrameData(int32 Index,USACurvesDataAsset* InCurvesAsset = nullptr);
	UFUNCTION(BlueprintCallable,Category="Stylized Action")
	void FrameInterpToTarget(USACurvesDataAsset* Target, float DeltaSeconds, float InterpSpeed = 5.0f);
	UFUNCTION(BlueprintCallable,Category="Stylized Action")
	bool FrameDataZeroed();
	UFUNCTION(BlueprintCallable,Category="Stylized Action")
	void UpdateFrameData(float DeltaSeconds);
};
