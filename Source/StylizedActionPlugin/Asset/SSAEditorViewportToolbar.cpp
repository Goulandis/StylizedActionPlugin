// Fill out your copyright notice in the Description page of Project Settings.


#include "SSAEditorViewportToolbar.h"
#include "SEditorViewportToolBarMenu.h"
#include "SAData.h"
#include "../Public/FStylizedActionPluginCommands.h"

#define LOCTEXT_NAMESPACE "SSAEditorViewportToobar"

void SSAEditorViewportToolbar::Construct(const FArguments& InArgs)
{
	UICommandList = MakeShareable(new FUICommandList_Pinnable);
	
	const FMargin ToolbarSlotPadding(4.0f, 1.0f);
	const FMargin ToolbarButtonPadding(4.0f, 1.0f);
	TSharedRef<SHorizontalBox> LeftToolbar = SNew(SHorizontalBox)
	+SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(ToolbarSlotPadding)
		[
		SNew(SEditorViewportToolbarMenu)
		.ToolTipText(LOCTEXT("CharacterMenuTooltip", "Character Options. Control character-related rendering options.\nShift-clicking items will 'pin' them to the toolbar."))
		.ParentToolBar(SharedThis(this))
		.Label(LOCTEXT("Character", "Character"))
		.OnGetMenuContent(this, &SSAEditorViewportToolbar::GenerateCharacterMenu)
		];
	ChildSlot
	[
		SNew( SVerticalBox )
		+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FAppStyle::Get().GetBrush("EditorViewportToolBar.Background"))
			.Cursor(EMouseCursor::Default)
			[
				LeftToolbar
			]
		]
	];
}

TSharedRef<SWidget> SSAEditorViewportToolbar::GenerateCharacterMenu() const
{
	TSharedPtr<FExtender> MenuExtender = FExtender::Combine(Extenders);

	const bool bInShouldCloseWindowAfterMenuSelection = true;
	FMenuBuilder InMenuBuilder(bInShouldCloseWindowAfterMenuSelection, UICommandList,MenuExtender);
	InMenuBuilder.PushExtender(MenuExtender.ToSharedRef());
	{
		InMenuBuilder.BeginSection("AnimViewportSceneElements", LOCTEXT("CharacterMenu_SceneElements", "Scene Elements"));
		{
			InMenuBuilder.AddSubMenu(
				LOCTEXT("CharacterMenu_BoneDrawSubMenu", "Bones"),
				LOCTEXT("CharacterMenu_BoneDrawSubMenuToolTip", "Bone Drawing Options"),
				FNewMenuDelegate::CreateLambda([](FMenuBuilder& SubMenuBuilder)
				{
					SubMenuBuilder.BeginSection("AnimViewportPreviewHierarchyBoneDraw", LOCTEXT("CharacterMenu_Actions_BoneDrawing", "Bone Drawing"));
					{
						SubMenuBuilder.AddMenuEntry(FStylizedActionPluginCommands::Get().ShowBoneDrawAll);
						SubMenuBuilder.AddMenuEntry(FStylizedActionPluginCommands::Get().ShowBoneDrawSelected);
						SubMenuBuilder.AddMenuEntry(FStylizedActionPluginCommands::Get().ShowBoneDrawSelectedAndParents);
						SubMenuBuilder.AddMenuEntry(FStylizedActionPluginCommands::Get().ShowBoneDrawSelectedAndChildren);
						SubMenuBuilder.AddMenuEntry(FStylizedActionPluginCommands::Get().ShowBoneDrawSelectedAndParentsAndChildren);
						SubMenuBuilder.AddMenuEntry(FStylizedActionPluginCommands::Get().ShowBoneDrawNone);
					}
					SubMenuBuilder.EndSection();
				})
				);
		}
		InMenuBuilder.EndSection();
	}
	InMenuBuilder.PopExtender();

	return InMenuBuilder.MakeWidget();
}

// void FSAEditorViewportToolbarCommads::RegisterCommands()
// {
// 	UI_COMMAND(ShowBoneDrawNone, "None", "Hide bone selection", EUserInterfaceActionType::RadioButton, FInputChord());
// 	UI_COMMAND( ShowBoneDrawSelected, "Selected Only", "Show only the selected bone", EUserInterfaceActionType::RadioButton, FInputChord());
// 	UI_COMMAND( ShowBoneDrawSelectedAndParents, "Selected and Parents", "Show the selected bone and its parents, to the root", EUserInterfaceActionType::RadioButton, FInputChord());
// 	UI_COMMAND( ShowBoneDrawSelectedAndChildren, "Selected and Children", "Show the selected bone and its children", EUserInterfaceActionType::RadioButton, FInputChord());
// 	UI_COMMAND( ShowBoneDrawSelectedAndParentsAndChildren, "Selected and Parents and Children", "Show the selected bone and its parents and children", EUserInterfaceActionType::RadioButton, FInputChord());
// 	UI_COMMAND( ShowBoneDrawAll, "All Hierarchy", "Show all hierarchy joints", EUserInterfaceActionType::RadioButton, FInputChord());
// 	UE_LOG(SALog,Log,TEXT("FSAEditorViewportToolbarCommads::RegisterCommands"));
// }

#undef LOCTEXT_NAMESPACE
