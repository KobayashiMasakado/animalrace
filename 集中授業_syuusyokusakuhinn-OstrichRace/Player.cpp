#include "pch.h"
#include "Player.h"
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Player::Player()
{
	m_move = 0;
	m_dir = 0.0f;
	m_z = 0.0f;
	m_itemPlayerCheck = false;
	m_itemPlayerBadCheck = false;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
	
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
/// <returns></returns>
bool Player::Update(float elapsedTime)
{
	m_vec = Vector3(0, 0, 0);

	if (m_move & (1 << NONE))
	{
		m_vec.z = 0.0f;
	}
	//�O�i
	if (m_move & (1 << FRONT))
	{
		m_vec.z = 0.25f;
	}
	//�O�i(�ʏ��葬�x�͑���)
	else if (m_move & (1 << FRONT_ITEMGET))
	{
		m_vec.z = 0.4f;
	}
	//�O�i(�ʏ��葬�x�͒x��)
	else if (m_move & (1 << FBONT_SPEEDDOWN))
	{
		m_vec.z = 0.05f;
	}
	//��i
	else if (m_move & (1 << BACK))
	{
		m_vec.z = -0.5f;
	}
	//�E����
	if (m_move & (1 << RIGHT_TURN))
	{
		m_dir -= XMConvertToRadians(1.0f);
	}
	//������
	else if (m_move & (1 << LEFT_TURN))
	{
		m_dir += XMConvertToRadians(1.0f);
	}

	//��
	if (m_move & (1 << UP_ANGLE))
	{
		m_z = XMConvertToRadians(-65.0f);
	}
	//��
	else if (m_move & (1 << DOWN_ANGLE))
	{
		m_z = XMConvertToRadians(1.0f);
	}

	if (m_move & (1 << GRAVITY))
	{
		m_vec.y -= 0.1f;
	}
	
	//�r�b�g�t���O�����Z�b�g����
	m_move = 0;

	//�I�u�W�F�N�g���ړ�����
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);/*
	m_rotationZ = Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), m_z);*/
	m_vec = Vector3::Transform(m_vec, m_rotation);/*
	m_vecZ = Vector3::Transform(m_vec, m_rotationZ);*/
	
	m_position += (m_vec);

	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// �`��
/// </summary>
void Player::Render()
{
	PlayerCreate();
	if (m_game && m_model)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(),*m_game->GetState(),m_world, m_game->GetView(), m_game->GetProjection());
		//�f�o�b�O�p�R���W�������f���̕`��
	//	DrawCollision();
		
	}
}
/// <summary>
/// �v���C���[������
/// </summary>
/// <param name="dir"></param>
void Player::PlayerMove(Direction dir)
{
	//�r�b�g�t���O
	m_move |= (1 << dir);
}

void Player::PlayerCreate()
{
	Collision::Capsule capsulePlayer;

	ModelDate* modelDate = ModelDate::GetInstance();

	SetPosition(Vector3(-93.5f, 0, 1.5f));
	SetGame(m_game);
	SetModel(modelDate->GetPlayer());
	SetUpEffect();
	// �J�v�Z���^�̃R���W����������
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//���E���̒��S
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		    //���E���̒��S
	capsulePlayer.r = 0.6f;							     	//���a
	SetCollision(capsulePlayer);
}

void Player::PlayerOperation(DirectX::Keyboard::State &kb)
{
	//��L�[�������ꂽ��
	if (kb.Up || kb.W)
	{
		if (m_itemPlayerCheck == true)
		{
			PlayerMove(Player::FRONT_ITEMGET);
		}
		else if (m_itemPlayerCheck == false)
		{
			PlayerMove(Player::FRONT);
		}
	}
	//���L�[�������ꂽ��
	if (kb.Down || kb.S)
	{
		//	m_player->PlayerMove(Player::UP_ANGLE);
	}
	//�E�L�[�������ꂽ��
	if (kb.Right || kb.D)
	{
		PlayerMove(Player::RIGHT_TURN);
	}
	//���L�[�������ꂽ��
	if (kb.Left || kb.A)
	{
		PlayerMove(Player::LEFT_TURN);
	}
}

//�v���C���[����(�R�[�X�O)
void Player::PlayerOperationwOutSide(DirectX::Keyboard::State & kb)
{
	//��L�[�������ꂽ��
	if (kb.Up || kb.W)
	{
		PlayerMove(Player::FBONT_SPEEDDOWN);
	}
	//�E�L�[�������ꂽ��
	if (kb.Right || kb.D)
	{
		PlayerMove(Player::RIGHT_TURN);
	}
	//���L�[�������ꂽ��
	if (kb.Left || kb.A)
	{
		PlayerMove(Player::LEFT_TURN);
	}
}

void Player::PlayerItemGet(std::unique_ptr<Item> itemPlayer[2],
                           std::unique_ptr<Item> itemPlayerErase[2],
                           std::unique_ptr<Item> itemCPU[2],
                           std::unique_ptr<Item> itemCPUErase[2])
{
	//�v���C���[�̃A�C�e���擾
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		//�v���C���[�p�̃A�C�e���擾
		if (Collision::HitCheck_Capsule2Capsule(itemPlayer[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerCheck = true;
		}
		//�v���C���[�p�̃A�C�e�����ʐ؂�
		else if (Collision::HitCheck_Capsule2Capsule(itemPlayerErase[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerCheck = false;
		}
		//CPU�p�̃A�C�e���擾
		if (Collision::HitCheck_Capsule2Capsule(itemCPU[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerBadCheck = true;
		}
		//CPU�p�̃A�C�e�����ʐ؂�
		else if (Collision::HitCheck_Capsule2Capsule(itemCPUErase[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerBadCheck = false;
		}
	}

}

void Player::SetUpEffect()
{
	m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetPerPixelLighting(true);
		}
	});
}
