#pragma once
///-------------------------------------------- 
/// Enemy.h
/// 
/// �G���i��N���X
/// Day.7/4
/// MasakadoKobayashi
///-------------------------------------------
#include "pch.h"
#include "DeviceResources.h"
#include "CollisionCapsule.h"

#include "Item.h"
#include "Root.h"

class Enemy : public CollisionCapsule
{
public:
	static const int ITEM_SET_NUM = 2;
	static const int ENEMY_HITCHECK_NUM = 23;
public:
	enum Direction
	{
		NONE,         //�ړ����Ȃ�
		FRONT,        //�@�O�i�@
		LEFT_OBLF,    //�@���i�i���O
		RIGHT_OBLF,   //�@�E�i�i���O
		BACK,	      //�@��i
		LEFT_SIDE,    //�@����
		RIGHT_SIDE,   //�@�E��
		LEFT_OBLB,    //�@���i�i�����
		RIGHT_OBLB,   //�@�E�i�i�����
		FRONT_SECOND, //�@�O�i�@
		RIGHT_OBLF40, //�@�E�i�i���O(40)
		UP_ANGLE,   // ������Ɋp�x��ς���
		DOWN_ANGLE,  // �������Ɋp�x��ς���
		FRONT_ITEMGET,//�O�i(�A�C�e���l���ő��x�͑���)
	};
private:
	//���x
	DirectX::SimpleMath::Vector3 m_vec;
	DirectX::SimpleMath::Vector3 m_vecZ;

	//����
	float m_dir;
	float m_z;
	//�ړ����i�r�b�g�j
	int m_move;

	bool m_itemCPUCheck;
public:
	//�R���X�g���N�^
	Enemy();
	~Enemy();
	//�X�V
	bool Update(float elapsedTime);
	//�`��
	void Render();
	//CPU�쐬
	void CPUCreate();
	//CPU������
	void EnemyChangeAngle(Direction dir);

	void CPUItemGet(std::unique_ptr<Item> itemCPU[ITEM_SET_NUM], std::unique_ptr<Item> itemCPUErase[ITEM_SET_NUM]);
};