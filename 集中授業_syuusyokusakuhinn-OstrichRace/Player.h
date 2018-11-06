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

#include "SceneSelect.h"

#include "CollisionCapsule.h"
#include "Item.h"

#include "InputHandler.h"

class Player : public CollisionCapsule
{
public:
	// �ړ�
	enum Direction
	{
		NONE,            // �ړ����Ȃ�
		FRONT,           // �O�i�@
		BACK,	         // ��i
		LEFT_TURN,       // �E����
		RIGHT_TURN,      // ������
		UP_ANGLE,        // ������Ɋp�x��ς���
		DOWN_ANGLE,      // �������Ɋp�x��ς���
		GRAVITY,         // �d��
	};

	enum State
	{
		STATE_NONE = 1,      // �ړ����Ȃ�
		BACK_OUTCOURSE = 1 << 1,	 // ��i(�ʏ��葬�x�͒x��)
		FRONT_ITEMGET = 1 << 2,   // �O�i(�ʏ��葬��)
		FRONT_OUTCOURSE = 1 << 3, // �O�i(�ʏ���x��)
		FRONT_FUNGET = 1 << 4,    // �O�i(�ʏ���x��)
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
	bool m_courseOut;

	Direction m_direction;
	int m_state;

	InputHandler m_inputHandle;

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
	void PlayerState(State state);
	void PlayerDeleteState(State state);

	void PlayerState();

	void PlayerDirection();

	void PlayerCreate();

	void PlayerItemGet(std::unique_ptr<Item> itemPlayer[2], 
		               std::unique_ptr<Item> itemPlayerErase[2],
		               std::unique_ptr<Item> itemCPU[2], 
		               std::unique_ptr<Item> itemCPUErase[2],
	                   std::unique_ptr<Item> itemFun[2],
	                   std::unique_ptr<Item> itemFunErase[2]);

	bool GetItemPlayer() { return m_itemPlayerCheck; }
	bool GetItemPlayerBad() { return m_itemPlayerBadCheck; }
	bool GetItemFun() { return m_itemFunCheck; }

	float GetDirection(){ return m_dir;}

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

	DirectX::SimpleMath::Vector3 GetVector()
	{
		return this->m_vec;
	}
	
	void SetVector(DirectX::SimpleMath::Vector3 vec)
	{
		this->m_vec = vec;
	}

	void SetVectorZ(DirectX::SimpleMath::Vector3 vecZ)
	{
		this->m_vecZ = vecZ;
	}

	float GetDir()
	{
		return m_dir;
	}

	void SetDir(float dir)
	{
		this->m_dir = dir;
	}

	void SetCourseOut(bool flag)
	{
		m_courseOut = flag;
	}
};