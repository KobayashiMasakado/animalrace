#include "ObjectCreate.h"

void ObjectCreate::PlayerCreate(Player* player, std::unique_ptr<DirectX::Model> playerModel)
{
	Collision::Capsule capsulePlayer;

	player = m_taskManager.AddTask<Player>();
	player->SetPosition(Vector3(-93.5f, 0, 1.5f));
	player->SetGame(m_game);
	player->SetModel(playerModel.get());
	player->SetUpEffect();
	// カプセル型のコリジョンをつける
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//境界球の中心
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		//境界球の中心
	capsulePlayer.r = 0.6f;							     	//半径
	player->SetCollision(capsulePlayer);
}
