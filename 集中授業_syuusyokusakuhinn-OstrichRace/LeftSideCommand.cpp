#include "pch.h"
#include "Player.h"
#include "LeftSideCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void LeftSideCommand::execute(Player * actor)
{
	actor->PlayerMove(Player::Direction::LEFT_TURN);
	float dir = actor->GetDir();
	dir += XMConvertToRadians(1.0f);
	actor->SetDir(dir);
}