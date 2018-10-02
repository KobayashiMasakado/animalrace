#pragma once
///------------------------------------------- 
/// Player.h
/// 
/// �v���C���[���i��N���X
/// Day.6/27
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"
#include "Item.h"

class Player : public CollisionCapsule
{
public:
	//
	enum Direction
	{
		NONE,       // �ړ����Ȃ�
		FRONT,      // �O�i�@
		BACK,	    // ��i
		LEFT_TURN,  // �E����
		RIGHT_TURN, // ������
		UP_ANGLE,   // ������Ɋp�x��ς���
		DOWN_ANGLE,  // �������Ɋp�x��ς���
		FRONT_ITEMGET,//�O�i(�ʏ��葬��)
		FRONT_OUTCOURSE,//�O�i(�ʏ���x��)
		FRONT_FUNGET,//�O�i(�ʏ���x��)
		GRAVITY,       //�d��
	};
private:
	//���x
	DirectX::SimpleMath::Vector3 m_vec;
	DirectX::SimpleMath::Vector3 m_vecZ;
	//����
	float m_dir;
	float m_z;

	// �ړ����i�r�b�g�j
	int m_move;

	bool m_itemPlayerCheck;
	bool m_itemPlayerBadCheck;
	bool m_itemFunCheck;

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//�X�V
	bool Update(float elapsedTime);
	//�`��
	void Render();

	//�G�t�F�N�g�̐ݒ�֐�
	void SetUpEffect();

	//�v���C���[������
	void PlayerMove(Direction dir);

	void PlayerCreate();

	void PlayerOperation(DirectX::Keyboard::State &kb);

	void PlayerOperationwOutSide(DirectX::Keyboard::State &kb);

	void PlayerItemGet(std::unique_ptr<Item> itemPlayer[2], 
		               std::unique_ptr<Item> itemPlayerErase[2],
		               std::unique_ptr<Item> itemCPU[2], 
		               std::unique_ptr<Item> itemCPUErase[2],
	                   std::unique_ptr<Item> itemFun[2],
	                   std::unique_ptr<Item> itemFunErase[2]);

	float GetDirection()
	{
		return m_dir;
	}

	//�v���C���[�̈ړ���Get�֐�
	DirectX::SimpleMath::Vector3 GetPlayer()
	{
		return m_position;
	}
	//�v���C���[�̉�]��Get�֐�
	DirectX::SimpleMath::Quaternion GetRot()
	{
		return m_rotation;
	}

	DirectX::SimpleMath::Quaternion GetRotZ()
	{
		return m_rotationZ;
	}
	
	void SetVector(DirectX::SimpleMath::Vector3 vec)
	{
		this->m_vec = vec;
	}

	void SetVectorZ(DirectX::SimpleMath::Vector3 vecZ)
	{
		this->m_vecZ = vecZ;
	}
};