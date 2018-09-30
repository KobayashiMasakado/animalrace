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

class Enemy : public CollisionCapsule
{
public:
	enum Direction
	{
		NONE,         //�ړ����Ȃ�
		FRONT,        //�@�O�i�@
		BACK,	      //�@��i
		LEFT_OBLF,    //�@���i�i���O
		RIGHT_OBLF,   //�@�E�i�i���O
		LEFT_SIDE,    //�@����
		RIGHT_SIDE,   //�@�E��
		LEFT_OBLB,    //�@���i�i�����
		RIGHT_OBLB,   //�@�E�i�i�����
		FRONT_SECOND, //�@�O�i�@
		RIGHT_OBLF40, //�@�E�i�i���O(40)
		FRONT_ITEMGET,//�O�i(�A�C�e���l���ő��x�͑���)
	};
private:
	//����
	float m_dir;
	//�ړ����i�r�b�g�j
	int m_move;

public:
	//�R���X�g���N�^
	Enemy();
	~Enemy();
	//�X�V
	bool Update(float elapsedTime);
	//�`��
	void Render();
	void CPUCreate();
	//CPU������
	void EnemyChangeAngle(Direction dir);

	
};