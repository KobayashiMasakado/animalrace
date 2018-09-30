#pragma once
///------------------------------------------- 
/// Root.h
/// 
/// ���[�g���i��N���X
/// Day.7/5
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"

class Root : public CollisionCapsule
{
private:

public:
	//�R���X�g���N�^
	Root();
	//�f�X�g���N�^
	~Root();
	//�X�V
	bool Update(float elapsedTIme);
	//�`��
	void Render();
	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();
	void Root::EnemyHitMoveCreate(int course);
};