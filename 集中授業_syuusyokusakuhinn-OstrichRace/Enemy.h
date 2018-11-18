#pragma once
///-------------------------------------------- 
/// Enemy.h
/// 
/// �G���i��N���X
/// Day.7/4
/// MasakadoKobayashi
///-------------------------------------------
#include "pch.h"

#include <sys/timeb.h>
#include "DeviceResources.h"
#include "CollisionCapsule.h"

#include "Item.h"
class Root;

class Enemy : public CollisionCapsule
{
public:
	static const int ITEM_SET_NUM = 2;
	static const int ENEMY_HITCHECK_NUM = 23;
public:
	enum Direction
	{
		NONE,          //�ړ����Ȃ�
		FRONT,         //�@�O�i�@
		LEFT_OBLF,     //�@���i�i���O
		RIGHT_OBLF,    //�@�E�i�i���O
		BACK,	       //�@��i
		LEFT_SIDE,     //�@����
		RIGHT_SIDE,    //�@�E��
		LEFT_OBLB,     //�@���i�i�����
		RIGHT_OBLB,    //�@�E�i�i�����
		FRONT_SECOND,  //�@�O�i�@
		RIGHT_OBLF40,  //�@�E�i�i���O(40)
		UP_ANGLE,      // ������Ɋp�x��ς���
		DOWN_ANGLE,    // �������Ɋp�x��ς���
		FRONT_ITEMGET, //�O�i(�A�C�e���l���ő��x�͑���)
		FRONT_FUNGET,  // �O�i(�ʏ���x��)
	};

	enum Warp
	{
		ZERO,
		ONE,
		TWO,
		THREE,
		FORE,
		FIVE
	};
private:
	//aa������
	DirectX::SimpleMath::Vector3 m_startPos;
	DirectX::SimpleMath::Vector3 m_targetPos;

	DirectX::SimpleMath::Vector3 m_CPUPoint[5];

	//����
	float m_dir;
	//�ړ����i�r�b�g�j
	int m_move;

	int m_moveW;

	bool m_itemCPUCheck;
	bool m_itemCPUBadCheck;
	bool m_itemCPUFunCheck;

	//CPU�����[�v����ꏊ
	DirectX::SimpleMath::Vector3 m_cpuSetPos[6];

	//	DirectX::SimpleMath::Vector3 m_vec;

	timeb m_startTime;
	//
	float m_count;

	/*float xn[100];
	float yn[100];
	int x;*/

public:
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();
	//�X�V
	bool Update(float elapsedTime);
	//�`��
	void Render();
	//CPU�쐬
	void CPUCreate();
	//CPU������
	void EnemyChangeAngle(Direction dir);
	void EnemyDirection(std::unique_ptr<Root> box[ENEMY_HITCHECK_NUM]);
	//CPU�����[�v����
	void CPUWarp(Warp warp);

	void CPUItemGet(std::unique_ptr<Item> itemCPU[ITEM_SET_NUM],
		std::unique_ptr<Item> itemCPUErase[ITEM_SET_NUM],
		std::unique_ptr<Item> itemCPUBad[ITEM_SET_NUM],
		std::unique_ptr<Item> itemCPUBadErase[ITEM_SET_NUM],
		std::unique_ptr<Item> itemFun[ITEM_SET_NUM],
		std::unique_ptr<Item> itemFunErase[ITEM_SET_NUM]);

	bool GetItemCPU() { return m_itemCPUCheck; }
	bool GetItemCPUBad() { return m_itemCPUBadCheck; }
	bool GetItemCPUFun() { return m_itemCPUFunCheck; }

	DirectX::SimpleMath::Vector3 lerp(DirectX::SimpleMath::Vector3 startPos, DirectX::SimpleMath::Vector3 targetPos, float time);

	//�v���C���[�̈ړ���Get�֐�
	DirectX::SimpleMath::Vector3 GetCPUPosition()
	{
		return m_position;
	}

};