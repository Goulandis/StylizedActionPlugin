#include "FStylizedActionPluginCommands.h"
#include "../Asset/SAData.h"

#define LOCTEXT_NAMESPACE "FStylizedActionEditorModule"

void FStylizedActionPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "StylizedActionPlugin", "动作风格化UI", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ShowBoneDrawNone, "None", "Hide bone selection", EUserInterfaceActionType::RadioButton, FInputChord());
	UI_COMMAND( ShowBoneDrawSelected, "Selected Only", "Show only the selected bone", EUserInterfaceActionType::RadioButton, FInputChord());
	UI_COMMAND( ShowBoneDrawSelectedAndParents, "Selected and Parents", "Show the selected bone and its parents, to the root", EUserInterfaceActionType::RadioButton, FInputChord());
	UI_COMMAND( ShowBoneDrawSelectedAndChildren, "Selected and Children", "Show the selected bone and its children", EUserInterfaceActionType::RadioButton, FInputChord());
	UI_COMMAND( ShowBoneDrawSelectedAndParentsAndChildren, "Selected and Parents and Children", "Show the selected bone and its parents and children", EUserInterfaceActionType::RadioButton, FInputChord());
	UI_COMMAND( ShowBoneDrawAll, "All Hierarchy", "Show all hierarchy joints", EUserInterfaceActionType::RadioButton, FInputChord());
	UE_LOG(SALog,Log,TEXT("FStylizedActionPluginCommands::RegisterCommands"));
}

#undef LOCTEXT_NAMESPACE