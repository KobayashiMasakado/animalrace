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

};