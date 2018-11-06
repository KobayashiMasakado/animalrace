#pragma once
#include "Command.h"
class Player;

class FrontCommand : public Command
{
public:
	virtual void execute(Player* actor)override;
};