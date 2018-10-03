#pragma once

#include "Obj3D.h"
#include "pch.h"
#include "Player.h"
#include "Enemy.h"

#include "TaskManager.h"
class ObjectCreate : public Obj3D
{
private:
	TaskManager m_taskManager;

public:
	void PlayerCreate(Player* player, DirectX::Model* playerModel, TaskManager& taskManager);

	void CPUCreate(Enemy* cpu, DirectX::Model* cpuModel, TaskManager& taskManager);
};