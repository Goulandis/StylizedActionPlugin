// Fill out your copyright notice in the Description page of Project Settings.


#include "SAAnimInstance.h"

void USAAnimInstance::OnCurvesChanged()
{
	UE_LOG(SALog,Log,TEXT("Curves has changed"));
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

FSAFrameData USAAnimInstance::GetSingleFrameData(int32 Index)
{
	if(Index >= GetFrameMaxIndex())
	{
		UE_LOG(SALog,Error,TEXT("Index=%d is better than CurvesAssetKeyMaxIndex=%d"),Index,GetFrameMaxIndex());
		return FSAFrameData();
	}
	if(GetSACurvesAsset() == nullptr)
	{
		return FSAFrameData();
	}
	//最好的方式是通过反射来设置骨骼的单帧数据，不过在UE5的源码里没有找到FFTransformProperty类型
	//参考https://blog.csdn.net/longyanbuhui/article/details/120330816
	for(TPair<FName,FCurvesItem> CurvesItem : GetSACurvesAsset()->Curves)
	{
		FTransform TransformTemp = CurvesItem.Value.GetSingleFrameData(Index);
		
		if(CurvesItem.Key == TEXT("pelvis"))
		{
			FrameData.pelvis = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_01"))
		{
			FrameData.spine_01 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_02"))
		{
			FrameData.spine_02 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_03"))
		{
			FrameData.spine_03 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_04"))
		{
			FrameData.spine_04 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("spine_05"))
		{
			FrameData.spine_04 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("clavicle_l"))
		{
			FrameData.clavicle_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("upperarm_l"))
		{
			FrameData.upperarm_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("lowerarm_l"))
		{
			FrameData.lowerarm_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("hand_l"))
		{
			FrameData.lowerarm_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("clavicle_r"))
		{
			FrameData.clavicle_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("upperarm_r"))
		{
			FrameData.upperarm_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("lowerarm_r"))
		{
			FrameData.lowerarm_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("hand_r"))
		{
			FrameData.hand_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("neck_01"))
		{
			FrameData.neck_01 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("neck_02"))
		{
			FrameData.neck_02 = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("thigh_l"))
		{
			FrameData.thigh_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("calf_l"))
		{
			FrameData.calf_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("foot_l"))
		{
			FrameData.foot_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("ball_l"))
		{
			FrameData.ball_l = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("thigh_r"))
		{
			FrameData.thigh_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("calf_r"))
		{
			FrameData.calf_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("foot_r"))
		{
			FrameData.foot_r = TransformTemp;
		}
		else if(CurvesItem.Key == TEXT("ball_r"))
		{
			FrameData.ball_r = TransformTemp;
		}
	}
	return FrameData;
}

FTransform USAAnimInstance::GetFrameDataFromCurve(int32 Index, USACurvesDataAsset* CurveAsset)
{
	//CurveAsset->Curves[Index].
	return FTransform();
}
