#pragma once
#include "Command.h"

class Player;
class LeftSideCommand : public Command
{
public:
	virtual void execute(Player* actor)override;
};