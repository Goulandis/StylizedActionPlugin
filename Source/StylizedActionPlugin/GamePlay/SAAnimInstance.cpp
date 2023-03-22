// Fill out your copyright notice in the Description page of Project Settings.


#include "SAAnimInstance.h"

void USAAnimInstance::OnCurvesChanged()
{
	UE_LOG(SALog,Log,TEXT("Curves has changed"));
}

bool USAAnimInstance::IsEditor()
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE,TEXT("EWorldType::Type"),true);
	if(EnumPtr)
	{
		UE_LOG(SALog,Error,TEXT("%s"),*EnumPtr->GetNameStringByIndex(GetWorld()->WorldType));
	}
	
	if(GetWorld()->WorldType == EWorldType::Type::Editor)
	{
		return true;
	}
	else
	{
		return false;
	}
}

USACurvesDataAsset* USAAnimInstance::GetSACurvesAsset()
{
	if(!CurvesAsset)
	{
		UE_LOG(SALog,Error,TEXT("CurvesAsset is null,please specify in 'Class Default'"));
		return nullptr;
	}
	return CurvesAsset;
}

int32 USAAnimInstance::GetFrameMaxIndex()
{
	if(GetSACurvesAsset() == nullptr)
	{
		return 0;
	}
	int32 Max = 0;
	for (TPair<FName,FCurvesItem>& Item : GetSACurvesAsset()->Curves)
	{
		if(Max < Item.Value.GetMaxKeyNum())
		{
			Max = Item.Value.GetMaxKeyNum();
		}
	}
	CurvesAssetKeyMaxIndex = Max;
	return Max;
}

FSAFrameData USAAnimInstance::GetSingleFrameData(int32 Index,USACurvesDataAsset* InCurvesAsset)
{
	if(Index >= GetFrameMaxIndex())
	{
		UE_LOG(SALog,Error,TEXT("Index=%d is better than CurvesAssetKeyMaxIndex=%d"),Index,GetFrameMaxIndex());
		return FSAFrameData();
	}
	if(InCurvesAsset == nullptr)
	{
		if(GetSACurvesAsset() == nullptr)
		{
			return FSAFrameData();
		}
		else
		{
			InCurvesAsset = GetSACurvesAsset();
		}
	}

	FSAFrameData CurrentFrameData;
	//最好的方式是通过反射来设置骨骼的单帧数据，不过在UE5的源码里没有找到FFTransformProperty类型
	//参考https://blog.csdn.net/longyanbuhui/article/details/120330816
	for(TPair<FName,FCurvesItem> CurvesItem : InCurvesAsset->Curves)
	{
		FTransform TransformTemp = CurvesItem.Value.GetSingleFrameData(Index);
		
		if(CurvesItem.Key == TEXT("pelvis"))
		{
			CurrentFrameData.pelvis = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_01"))
		{
			CurrentFrameData.spine_01 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_02"))
		{
			CurrentFrameData.spine_02 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_03"))
		{
			CurrentFrameData.spine_03 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_04"))
		{
			CurrentFrameData.spine_04 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_05"))
		{
			CurrentFrameData.spine_04 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("clavicle_l"))
		{
			CurrentFrameData.clavicle_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("upperarm_l"))
		{
			CurrentFrameData.upperarm_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("lowerarm_l"))
		{
			CurrentFrameData.lowerarm_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("hand_l"))
		{
			CurrentFrameData.lowerarm_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("clavicle_r"))
		{
			CurrentFrameData.clavicle_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("upperarm_r"))
		{
			CurrentFrameData.upperarm_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("lowerarm_r"))
		{
			CurrentFrameData.lowerarm_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("hand_r"))
		{
			CurrentFrameData.hand_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("neck_01"))
		{
			CurrentFrameData.neck_01 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("neck_02"))
		{
			CurrentFrameData.neck_02 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("thigh_l"))
		{
			CurrentFrameData.thigh_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("calf_l"))
		{
			CurrentFrameData.calf_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("foot_l"))
		{
			CurrentFrameData.foot_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("ball_l"))
		{
			CurrentFrameData.ball_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("thigh_r"))
		{
			CurrentFrameData.thigh_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("calf_r"))
		{
			CurrentFrameData.calf_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("foot_r"))
		{
			CurrentFrameData.foot_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("ball_r"))
		{
			CurrentFrameData.ball_r = TransformTemp;
		}
	}
	return CurrentFrameData;
}

void USAAnimInstance::FrameInterpToTarget(USACurvesDataAsset* Target, float DeltaSeconds, float InterpSpeed)
{
	if(Target == nullptr)
	{
		FSAFrameData ZeroedData = FSAFrameData();
		ZeroedData.FrameDataInterpTo(FrameData,DeltaSeconds,InterpSpeed);
	}
	else
	{
		FSAFrameData TargetFrameData = GetSingleFrameData(0,Target);
		TargetFrameData.FrameDataInterpTo(FrameData,DeltaSeconds,InterpSpeed);
	}
}

bool USAAnimInstance::FrameDataZeroed()
{
	FSAFrameData ZeroedData;
	return FrameData == ZeroedData;
}

void USAAnimInstance::UpdateFrameData(float DeltaSeconds)
{
	// FSAFrameData Target = FSAFrameData();
	// switch (SAType)
	// {
	// 	case ESAType::Restore:
	// 		FrameInterpToTarget(Target,DeltaSeconds);
	// 		break;
	// 	case ESAType::InterpTo:
	// 		FrameInterpToTarget(TargetFramwData,DeltaSeconds);
	// 		break;
	// 	default:
	// 		break;
	// }
}
