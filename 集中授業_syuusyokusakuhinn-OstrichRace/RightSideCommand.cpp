#include "pch.h"
#include "Player.h"
#include "RightSideCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void RightSideCommand::execute(Player * actor)
{
	actor->PlayerMove(Player::Direction::LEFT_TURN);
	float dir = actor->GetDir();
	dir -= XMConvertToRadians(1.0f);
	actor->SetDir(dir);
}