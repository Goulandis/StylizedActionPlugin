// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Kismet/KismetMathLibrary.h"
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

	bool TransformEqual(const FTransform& Source,const FTransform& Target)
	{
		if(Source.GetLocation() == Target.GetLocation() && Source.GetRotation() == Target.GetRotation() && Source.GetScale3D() == Target.GetScale3D())
		{return true;}
		else{return false;}
	}
	
	bool operator==(const FSAFrameData& Target)
	{
		return TransformEqual(this->pelvis,Target.pelvis)
			&& TransformEqual(this->spine_01,Target.spine_01)
			&& TransformEqual(this->spine_02,Target.spine_02)
			&& TransformEqual(this->spine_03,Target.spine_03)
			&& TransformEqual(this->spine_04,Target.spine_04)
			&& TransformEqual(this->spine_05,Target.spine_05)
			&& TransformEqual(this->clavicle_l,Target.clavicle_l)
			&& TransformEqual(this->upperarm_l,Target.upperarm_l)
			&& TransformEqual(this->lowerarm_l,Target.lowerarm_l)
			&& TransformEqual(this->hand_l,Target.hand_l)
			&& TransformEqual(this->clavicle_r,Target.clavicle_r)
			&& TransformEqual(this->upperarm_r,Target.upperarm_r)
			&& TransformEqual(this->lowerarm_r,Target.lowerarm_r)
			&& TransformEqual(this->hand_r,Target.hand_r)
			&& TransformEqual(this->neck_01,Target.neck_01)
			&& TransformEqual(this->neck_02,Target.neck_02)
			&& TransformEqual(this->head,Target.head)
			&& TransformEqual(this->thigh_l,Target.thigh_l)
			&& TransformEqual(this->calf_l,Target.calf_l)
			&& TransformEqual(this->foot_l,Target.foot_l)
			&& TransformEqual(this->ball_l,Target.ball_l)
			&& TransformEqual(this->thigh_r,Target.thigh_r)
			&& TransformEqual(this->calf_r,Target.calf_r)
			&& TransformEqual(this->foot_r,Target.foot_r)
			&& TransformEqual(this->ball_r,Target.ball_r);
	}

	void FrameDataInterpTo(FSAFrameData& Start,float DeltaSeconds,float InterpSpeed=5.0f)
	{
		Start.pelvis = UKismetMathLibrary::TInterpTo(Start.pelvis,this->pelvis,DeltaSeconds,InterpSpeed);
		Start.spine_01 = UKismetMathLibrary::TInterpTo(Start.spine_01,this->spine_01,DeltaSeconds,InterpSpeed);
		Start.spine_02 = UKismetMathLibrary::TInterpTo(Start.spine_02,this->spine_02,DeltaSeconds,InterpSpeed);
		Start.spine_03 = UKismetMathLibrary::TInterpTo(Start.spine_03,this->spine_03,DeltaSeconds,InterpSpeed);
		Start.spine_04 = UKismetMathLibrary::TInterpTo(Start.spine_04,this->spine_04,DeltaSeconds,InterpSpeed);
		Start.spine_05 = UKismetMathLibrary::TInterpTo(Start.spine_05,this->spine_05,DeltaSeconds,InterpSpeed);
		Start.clavicle_l = UKismetMathLibrary::TInterpTo(Start.clavicle_l,this->clavicle_l,DeltaSeconds,InterpSpeed);
		Start.upperarm_l = UKismetMathLibrary::TInterpTo(Start.upperarm_l,this->upperarm_l,DeltaSeconds,InterpSpeed);
		Start.lowerarm_l = UKismetMathLibrary::TInterpTo(Start.lowerarm_l,this->lowerarm_l,DeltaSeconds,InterpSpeed);
		Start.hand_l = UKismetMathLibrary::TInterpTo(Start.hand_l,this->hand_l,DeltaSeconds,InterpSpeed);
		Start.clavicle_r = UKismetMathLibrary::TInterpTo(Start.clavicle_r,this->clavicle_r,DeltaSeconds,InterpSpeed);
		Start.upperarm_r = UKismetMathLibrary::TInterpTo(Start.upperarm_r,this->upperarm_r,DeltaSeconds,InterpSpeed);
		Start.lowerarm_r = UKismetMathLibrary::TInterpTo(Start.lowerarm_r,this->lowerarm_r,DeltaSeconds,InterpSpeed);
		Start.hand_r = UKismetMathLibrary::TInterpTo(Start.hand_r,this->hand_r,DeltaSeconds,InterpSpeed);
		Start.neck_01 = UKismetMathLibrary::TInterpTo(Start.neck_01,this->neck_01,DeltaSeconds,InterpSpeed);
		Start.neck_02 = UKismetMathLibrary::TInterpTo(Start.neck_02,this->neck_02,DeltaSeconds,InterpSpeed);
		Start.head = UKismetMathLibrary::TInterpTo(Start.head,this->head,DeltaSeconds,InterpSpeed);
		Start.thigh_l = UKismetMathLibrary::TInterpTo(Start.thigh_l,this->thigh_l,DeltaSeconds,InterpSpeed);
		Start.calf_l = UKismetMathLibrary::TInterpTo(Start.calf_l,this->calf_l,DeltaSeconds,InterpSpeed);
		Start.foot_l = UKismetMathLibrary::TInterpTo(Start.foot_l,this->foot_l,DeltaSeconds,InterpSpeed);
		Start.ball_l = UKismetMathLibrary::TInterpTo(Start.ball_l,this->ball_l,DeltaSeconds,InterpSpeed);
		Start.thigh_r = UKismetMathLibrary::TInterpTo(Start.thigh_r,this->thigh_r,DeltaSeconds,InterpSpeed);
		Start.calf_r = UKismetMathLibrary::TInterpTo(Start.calf_r,this->calf_r,DeltaSeconds,InterpSpeed);
		Start.foot_r = UKismetMathLibrary::TInterpTo(Start.foot_r,this->foot_r,DeltaSeconds,InterpSpeed);
		Start.ball_r = UKismetMathLibrary::TInterpTo(Start.ball_r,this->ball_r,DeltaSeconds,InterpSpeed);
	}
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

UENUM(BlueprintType)
enum class ESAType : uint8
{
	Defualt,
	Restore,
	InterpTo
};

UENUM(BlueprintType)
enum class EPawnState : uint8
{
	Defualt,
	Idle,
	Walk,
	Run,
	Jump
};

UCLASS()
class STYLIZEDACTIONPLUGIN_API USAData : public UObject
{
	GENERATED_BODY()
	
};
