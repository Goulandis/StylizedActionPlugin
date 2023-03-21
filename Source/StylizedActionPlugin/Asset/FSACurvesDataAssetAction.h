// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class STYLIZEDACTIONPLUGIN_API FSACurvesDataAssetAction : public FAssetTypeActions_Base
{
public:
	//返回资产的名字
	virtual FText GetName() const override;
	//资产在Content Browser里的浏览颜色
	virtual FColor GetTypeColor() const override;
	//这个Action对应的操作类
	virtual UClass* GetSupportedClass() const override;
	//获取创建资产的目录
	virtual uint32 GetCategories() override;
	//自定义资产打开后显示的编辑器
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor) override;
	//设置自定义资产右下角图标
	virtual TSharedPtr<SWidget> GetThumbnailOverlay(const FAssetData& AssetData) const override;
};
