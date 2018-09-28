#include "ObjectCreate.h"

void ObjectCreate::PlayerCreate(Player* player, std::unique_ptr<DirectX::Model> playerModel)
{
	Collision::Capsule capsulePlayer;

	player = m_taskManager.AddTask<Player>();
	player->SetPosition(Vector3(-93.5f, 0, 1.5f));
	player->SetGame(m_game);
	player->SetModel(playerModel.get());
	player->SetUpEffect();
	// �J�v�Z���^�̃R���W����������
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//���E���̒��S
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		//���E���̒��S
	capsulePlayer.r = 0.6f;							     	//���a
	player->SetCollision(capsulePlayer);
}
