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

	int32 GetMaxKeysNum()
	{
		int32 Max = 0;
		if(Max < X.GetRichCurveConst()->GetNumKeys())
		{
			Max = X.GetRichCurveConst()->GetNumKeys();
		}
		if(Max < Y.GetRichCurveConst()->GetNumKeys())
		{
			Max = Y.GetRichCurveConst()->GetNumKeys();
		}
		if(Max < Z.GetRichCurveConst()->GetNumKeys())
		{
			Max = Z.GetRichCurveConst()->GetNumKeys();
		}
		return Max;
	}
	FVector GetSingleFrameData(int32 Index)
	{
		FVector LocationTemp;
		if(Index < GetMaxKeysNum())
		{
			const FRichCurve* RichCurveX = X.GetRichCurveConst();
			if(!RichCurveX)
			{
				UE_LOG(SALog,Error,TEXT("RichCurveX is nullptr"));
				return FVector();
			}
			if(Index < RichCurveX->GetNumKeys())
			{
				LocationTemp.X =  RichCurveX->GetCopyOfKeys()[Index].Value;
			}
			else
			{
				if(RichCurveX->GetNumKeys() > 0)
				{
					LocationTemp.Y = RichCurveX->GetLastKey().Value;
				}
				else
				{
					LocationTemp.Y = 0;
				}
			}
			const FRichCurve* RichCurveY = Y.GetRichCurveConst();
			if(!RichCurveY)
			{
				UE_LOG(SALog,Error,TEXT("RichCurveY is nullptr"));
				return FVector();
			}
			if(Index < RichCurveY->GetNumKeys())
			{
				LocationTemp.Y =  RichCurveY->GetCopyOfKeys()[Index].Value;
			}
			else
			{
				if(RichCurveY->GetNumKeys() > 0)
				{
					LocationTemp.Y = RichCurveY->GetLastKey().Value;
				}
				else
				{
					LocationTemp.Y = 0;
				}
			}
			const FRichCurve* RichCurveZ = Z.GetRichCurveConst();
			if(!RichCurveZ)
			{
				UE_LOG(SALog,Error,TEXT("RichCurveZ is nullptr"));
				return FVector();
			}
			if(Index < RichCurveZ->GetNumKeys())
			{
				LocationTemp.Z =  RichCurveZ->GetCopyOfKeys()[Index].Value;
			}
			else
			{
				if(RichCurveZ->GetNumKeys() > 0)
				{
					LocationTemp.Y = RichCurveZ->GetLastKey().Value;
				}
				else
				{
					LocationTemp.Y = 0;
				}
			}
		}
		return LocationTemp;
	}
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

	int32 GetMaxKeyNum()
	{
		int32 Max = 0;
		if(Max < Location.GetMaxKeysNum())
		{
			Max = Location.GetMaxKeysNum();
		}
		if(Max < Rotation.GetMaxKeysNum())
		{
			Max = Rotation.GetMaxKeysNum();
		}
		if(Max < Scale.GetMaxKeysNum())
		{
			Max = Scale.GetMaxKeysNum();
		}
		return Max;
	}

	FTransform GetSingleFrameData(int32 Index)
	{
		FTransform TransformTemp;
		TransformTemp.SetLocation(Location.GetSingleFrameData(Index));
		TransformTemp.SetRotation(FQuat::MakeFromEuler(Rotation.GetSingleFrameData(Index)));
		TransformTemp.SetScale3D(Scale.GetSingleFrameData(Index));
		return TransformTemp;
	}
};

UCLASS()
class STYLIZEDACTIONPLUGIN_API USAData : public UObject
{
	GENERATED_BODY()
	
};
