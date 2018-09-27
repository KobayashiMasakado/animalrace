#pragma once
/// /// <summary>
/// Obj3D
/// 
/// 3D�I�u�W�F�N�g��`�悷�邽�߂̃N���X
/// Day.6/256/25
/// Masakado Kobayashi
#include "pch.h"
class Game;
#include "TaskManager.h"

class Obj3D : public Task
{
protected:
	//�Q�[���I�u�W�F�N�g�ւ̃|�C���^
	Game* m_game;
	//���f���n���h��
	DirectX::Model* m_model;

	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//��]
	DirectX::SimpleMath::Quaternion m_rotation;

	//��]
	DirectX::SimpleMath::Quaternion m_rotationZ;

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

public:
	//�R���X�g���N�^
	Obj3D();
	//�X�V
	virtual bool Update(float elapsedTime);

	//�`��
	virtual void Render();

	// �Z�b�^�[�֐�
	//�Q�[���I�u�W�F�N�g��ݒ肷��֐�
	void SetGame(Game* game)
	{
		m_game = game;
	}

	//���f���n���h����ݒ肷��֐�
	void SetModel(DirectX::Model* model)
	{
		m_model = model;
	}

	//�ʒu�ݒ肷��֐�
	void SetPosition(DirectX::SimpleMath::Vector3 position)
	{
		m_position = position;
	}

	//��]�ݒ肷��֐�
	void SetRotation(DirectX::SimpleMath::Quaternion rotation)
	{
		m_rotation = rotation;
	}

};