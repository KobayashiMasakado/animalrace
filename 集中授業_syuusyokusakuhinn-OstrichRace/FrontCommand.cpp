#include "pch.h"
#include "Player.h"
#include "FrontCommand.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void FrontCommand::execute(Player * actor)
{
	actor->PlayerMove(Player::Direction::FRONT);
	Vector3 vec = actor->GetVector();
	vec.z = 0.45f;
	actor->SetVector(vec);
}