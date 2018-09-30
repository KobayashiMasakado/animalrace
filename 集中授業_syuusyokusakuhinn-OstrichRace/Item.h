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
	//�A�C�e���쐬(�v���C���[)
	void ItemPlayerCreate();
	////�A�C�e�����ʐ؂�(�v���C���[)
	//void ItemPlayerEraseCreate();
	//�A�C�e���쐬(CPU)
	void ItemCPUCreate();
	////�A�C�e�����ʐ؂�(CPU)
	//void ItemCPUEraseCreate();
};