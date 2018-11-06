#pragma once

class Player;

class Command
{
public:
	virtual ~Command() {}
	virtual void execute(Player* actor) = 0;
};


