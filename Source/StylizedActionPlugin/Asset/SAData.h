// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SAData.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(SALog,All,All);

USTRUCT(BlueprintType)
struct FSAFrameData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform pelvis;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform spine_01;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform spine_02;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform spine_03;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform spine_04;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform spine_05;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform clavicle_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform upperarm_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform lowerarm_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform hand_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform clavicle_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform upperarm_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform lowerarm_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform hand_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform neck_01;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform neck_02;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform head;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform thigh_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform calf_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform foot_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform ball_l;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform thigh_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform calf_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform foot_r;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FTransform ball_r;
};

USTRUCT(BlueprintType)
struct FCurvesMetaItem
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FRuntimeFloatCurve X;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FRuntimeFloatCurve Y;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FRuntimeFloatCurve Z;
};

USTRUCT(BlueprintType)
struct FCurvesItem
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCurvesMetaItem Location;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCurvesMetaItem Rotation;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	FCurvesMetaItem Scale;
};

UCLASS()
class STYLIZEDACTIONPLUGIN_API USAData : public UObject
{
	GENERATED_BODY()
	
};
