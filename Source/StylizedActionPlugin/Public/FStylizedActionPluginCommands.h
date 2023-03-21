#pragma once
#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "FStylizedActionPluginStyle.h"

class FStylizedActionPluginCommands : public TCommands<FStylizedActionPluginCommands>
{
public:

	FStylizedActionPluginCommands()
		: TCommands<FStylizedActionPluginCommands>(TEXT("StylizedActionEditor"), NSLOCTEXT("Contexts", "StylizedActionEditor", "StylizedActionEditor Plugin"), NAME_None, FStylizedActionPluginStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
