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
#include "EffectManager.h"

class Item : public CollisionCapsule
{
	public:
	static const int ITEM_SET_NUM = 2;
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
	//�A�C�e�����ʐ؂�(�v���C���[)
	void ItemPlayerEraseCreate(int item);
	//�A�C�e���쐬(CPU)
	void ItemCPUCreate(int item);
	//�A�C�e�����ʐ؂�(CPU)
	void ItemCPUEraseCreate(int item);
	//�A�C�e���쐬(�t��)
	void ItemFunCreate(int item);
	//�A�C�e�����ʐ؂�(CPU)
	void ItemFunEraseCreate(int item);

	void EffectCreate(EffectManager* m_effectManager);
};