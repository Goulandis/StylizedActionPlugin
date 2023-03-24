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

	/** Hide all bones */
	TSharedPtr< FUICommandInfo > ShowBoneDrawNone;

	/** Show only selected bones */
	TSharedPtr< FUICommandInfo > ShowBoneDrawSelected;

	/** Show only selected bones and their parents */
	TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndParents;

	/** Show only selected bones and their children */
	TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndChildren;

	/** Show only selected bones and their parents and children */
	TSharedPtr< FUICommandInfo > ShowBoneDrawSelectedAndParentsAndChildren;

	/** Show all bones */
	TSharedPtr< FUICommandInfo > ShowBoneDrawAll;
};
