#include "pch.h"
#include "Enemy.h"
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// �R���X�g���N�^
/// </summary>
Enemy::Enemy()
{
	m_move = 0;
	m_dir = 0.0f;
	m_itemCPUCheck = false;
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Enemy::~Enemy()
{
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
/// <returns></returns>
bool Enemy::Update(float elapsedTime)
{
	m_vec  = Vector3(0, 0, 0);
	m_vecZ = Vector3(0, 0, 0);
	if (m_move & (1 << NONE))
	{
		m_vec.z = 0.0f;
	}
	//�O�i
	if (m_move & (1 << FRONT))
	{
		m_vec.z = 0.48f;
	}
	//�O�i(�A�C�e���l���ő��x�͑���)
	else if (m_move & (1 << FRONT_ITEMGET))
	{
		m_vec.z = 0.65f;
	}
	//��i
	if (m_move & (1 << BACK))
	{
		m_dir = XMConvertToRadians(180.0f);
	}
	//�E�i�i���O
	if (m_move & (1 << RIGHT_OBLF))
	{
		m_dir = XMConvertToRadians(40.0f);
	}
	//���i�i���O
	else if (m_move & (1 << LEFT_OBLF))
	{
		m_dir = XMConvertToRadians(-45.0f);
	}
	if (m_move & (1 << RIGHT_OBLF40))
	{
		m_dir = XMConvertToRadians(30.0f);
	}
	//�E��
	if (m_move & (1 << RIGHT_SIDE))
	{
		m_dir = XMConvertToRadians(90.0f);
	}
	//����
	else if (m_move & (1 << LEFT_SIDE))
	{
		m_dir = XMConvertToRadians(-90.0f);
	}
	//�E�i�i�����
	if (m_move & (1 << RIGHT_OBLB))
	{
		m_dir = XMConvertToRadians(135.0f);
	}
	//���i�i�����
	else if (m_move & (1 << LEFT_OBLB))
	{
		m_dir = XMConvertToRadians(-135.0f);
	}
	//�O�i
	if (m_move & (1 << FRONT_SECOND))
	{
		m_dir = XMConvertToRadians(0.0f);
	}

	if (m_move & (1 << UP_ANGLE))
	{
		m_vec.y = 0.07f;
	}
	if (m_move & (1 << DOWN_ANGLE))
	{
		m_vec.y = -0.07f;
	}
	
	//�r�b�g�t���O�����Z�b�g
	m_move = 0;

	//�I�u�W�F�N�g���ړ�����
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);
	m_rotationZ = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), m_z);

	m_vec = Vector3::Transform(m_vec, m_rotation);
	m_vecZ = Vector3::Transform(m_vecZ, m_rotationZ);
	m_position += (m_vec + m_vecZ);

	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// �`��
/// </summary>
void Enemy::Render()
{
	
	if (m_game && m_model)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(), *m_game->GetState(),
			m_world, m_game->GetView(), m_game->GetProjection());
	
		//�f�o�b�O�p�R���W�������f���̕`��
		//DrawCollision();
	}
}
/// <summary>
/// 
/// </summary>
void Enemy::CPUCreate()
{
	Collision::Capsule capsuleCPU;
	
	ModelDate* modelDate = ModelDate::GetInstance();

	SetPosition(Vector3(-97.5f, 0, 1.5f));
	SetGame(m_game);
	SetModel(modelDate->GetCPU());
	// �J�v�Z���^�̃R���W����������
	capsuleCPU.start = Vector3(0.3f, 0.0f, 0.2f);           //���E���̒��S
	capsuleCPU.end = Vector3(0.3f, 3.0f, 0.2f);		        //���E���̒��S
	capsuleCPU.r = 0.3f;                                    //���a
	SetCollision(capsuleCPU);
}
/// <summary>
/// CPU������
/// </summary>
/// <param name="dir"></param>
void Enemy::EnemyChangeAngle(Direction dir)
{
	//�r�b�g�t���O
	m_move |= (1 << dir);
}

//void Enemy::EnemyDirection(std::unique_ptr<Root> box[ENEMY_HITCHECK_NUM])
//{
	////�A�C�e���擾���̈ړ����x
	//if (m_itemCPUCheck == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_ITEMGET);
	//}//�ʏ�̈ړ����x
	//else if (m_itemCPUCheck == false)
	//{
	//	EnemyChangeAngle(Enemy::FRONT);
	//}
	//
	//if (Collision::HitCheck_Capsule2Capsule(box[2]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_SIDE);
	//}
	//else	if (Collision::HitCheck_Capsule2Capsule(box[1]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[3]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[4]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[5]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[6]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_SIDE);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[7]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[8]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_SECOND);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[9]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[10]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[11]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_SECOND);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[12]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[13]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_SIDE);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[14]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[16]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[15]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::BACK);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[17]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_SIDE);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[0]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_SECOND);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[18]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLF);
	//}
	////���������ꏊ�ɂ����CPU�̕�����ς���
	//for (int i = 0; i < ScenePlay::ENEMY_HITCHECK_NUM; i++)
	//{
	//	if (Collision::HitCheck_Capsule2Capsule(GetCollision(), GetCollision()))
	//	{
	//		EnemyChangeAngle(static_cast<Enemy::Direction>(i));
	//	}
	//}
//}

void Enemy::CPUItemGet(std::unique_ptr<Item> m_itemCPU[ITEM_SET_NUM], std::unique_ptr<Item> m_itemCPUErase[ITEM_SET_NUM])
{
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		//CPU�A�C�e���擾
		if (Collision::HitCheck_Capsule2Capsule(m_itemCPU[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUCheck = true;
		}

		if (Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[0]->GetCollision(), GetCollision()))
		{
			m_itemCPUCheck = false;
		}

	}
}