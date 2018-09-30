#pragma once
///------------------------------------------- 
/// Item.h
/// 
/// �A�C�e���i��N���X
/// Day.7/5
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"

class Item : public CollisionCapsule
{
private:

public:
	//�R���X�g���N�^
	Item();
	//�f�X�g���N�^
	~Item();
	//�X�V
	bool Update(float elapsedTIme);
	//�`��
	void Render();
	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();

	//�A�C�e���쐬(�v���C���[)
	void ItemPlayerCreate(int item);
	////�A�C�e�����ʐ؂�(�v���C���[)
	//void ItemPlayerEraseCreate();
	//�A�C�e���쐬(CPU)
	void ItemCPUCreate(int item);
	////�A�C�e�����ʐ؂�(CPU)
	//void ItemCPUEraseCreate();
};