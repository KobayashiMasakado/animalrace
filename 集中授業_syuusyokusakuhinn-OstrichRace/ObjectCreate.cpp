#include "pch.h"
#include "ObjectCreate.h"

using namespace DirectX;

using namespace DirectX::SimpleMath;

void ObjectCreate::PlayerCreate(Player* player, DirectX::Model* playerModel, TaskManager& taskManager)
{
	Collision::Capsule capsulePlayer;

	player = taskManager.AddTask<Player>();
	player->SetPosition(Vector3(-93.5f, 0, 1.5f));
	player->SetGame(m_game);
	player->SetModel(playerModel);
	player->SetUpEffect();
	// ÉJÉvÉZÉãå^ÇÃÉRÉäÉWÉáÉìÇÇ¬ÇØÇÈ
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//ã´äEãÖÇÃíÜêS
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		    //ã´äEãÖÇÃíÜêS
	capsulePlayer.r = 0.6f;							     	//îºåa
	player->SetCollision(capsulePlayer);
}

//CPUçÏê¨
void ObjectCreate::CPUCreate(Enemy* cpu, DirectX::Model* cpuModel, TaskManager& taskManager)
{
	Collision::Capsule capsuleCPU;
	cpu = taskManager.AddTask<Enemy>();
	cpu->SetPosition(Vector3(-97.5f, 0, 1.5f));
	cpu->SetGame(m_game);
	cpu->SetModel(cpuModel);
	// ÉJÉvÉZÉãå^ÇÃÉRÉäÉWÉáÉìÇÇ¬ÇØÇÈ
	capsuleCPU.start = Vector3(0.3f, 0.0f, 0.2f);           //ã´äEãÖÇÃíÜêS
	capsuleCPU.end = Vector3(0.3f, 3.0f, 0.2f);		        //ã´äEãÖÇÃíÜêS
	capsuleCPU.r = 0.6f;                                    //îºåa
	cpu->SetCollision(capsuleCPU);
}
