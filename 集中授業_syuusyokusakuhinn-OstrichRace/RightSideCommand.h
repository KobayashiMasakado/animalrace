#pragma once
#include "Command.h"


class RightSideCommand : public Command
{
public:
	virtual void execute(Player* actor) override;
};