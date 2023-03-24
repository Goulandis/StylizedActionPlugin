// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SSACurvesDataAssetEditorViewport.h"
#include "SViewportToolBar.h"
#include "UICommandList_Pinnable.h"

/**
 * 
 */
class STYLIZEDACTIONPLUGIN_API SSAEditorViewportToolbar : public SViewportToolBar
{
public:
	SLATE_BEGIN_ARGS(SSAEditorViewportToolbar){}
	SLATE_END_ARGS()
public:
	void Construct(const FArguments& InArgs);
	TSharedRef<SWidget> GenerateCharacterMenu() const;

private:
	/** Commands that are bound to delegates*/
	TSharedPtr<FUICommandList_Pinnable> UICommandList;
	/** Extenders */
	TArray<TSharedPtr<FExtender>> Extenders;
};

// class STYLIZEDACTIONPLUGIN_API FSAEditorViewportToolbarCommads : public TCommands<FSAEditorViewportToolbarCommads>
// {
// public:
// 	FSAEditorViewportToolbarCommads() 
// 	: TCommands<FSAEditorViewportToolbarCommads>
// 	(
// 		TEXT("StylizedActionEditor"), // Context name for fast lookup
// 		NSLOCTEXT("Contexts", "StylizedActionEditor", "Stylized Action Plugin Viewport Show Command"), // Localized context name for displaying
// 		NAME_None, // Parent context name. 
// 		FEditorStyle::GetStyleSetName() // Icon Style Set
// 	)
// 	{
// 	}
//
// 	virtual void RegisterCommands() override;
//
// 	/** Hide all bones */
// 	TSharedPtr< FUICommandInfo > ShowBoneDrawNone;
//
// 	/** Show only selected bones */
// 	TSharedPtr< FUICommandInfo > ShowBoneDrawSelected;
//
// 	/** Show only selected bones and their parents */
// 	TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndParents;
//
// 	/** Show only selected bones and their children */
// 	TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndChildren;
//
// 	/** Show only selected bones and their parents and children */
// 	TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndParentsAndChildren;
//
// 	/** Show all bones */
// 	TSharedPtr< FUICommandInfo > ShowBoneDrawAll;
// };
