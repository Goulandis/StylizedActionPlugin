#include "FStylizedActionPluginCommands.h"

#define LOCTEXT_NAMESPACE "FStylizedActionEditorModule"

void FStylizedActionPluginCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "StylizedActionPlugin", "动作风格化UI", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE