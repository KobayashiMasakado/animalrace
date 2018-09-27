#include "pch.h"
#include "CollisionCapsule.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CollisionCapsule::SetCollision(Collision::Capsule capsule)
{
	//�R���W�������̐ݒ�
	m_collision = capsule;
	if (m_game)
	{
		//�f�o�b�O�p�R���W�������f���̍쐬
		m_obj = std::make_unique<DebugCapsule>
			(m_game->GetDevice(),
				m_collision.start, 	//�c���̊J�n�_ 
				m_collision.end,	//�c���̏I���_
				m_collision.r);		//���a
	}
}

Collision::Capsule CollisionCapsule::GetCollision()
{
	Collision::Capsule capsule;

	//�R���W�����������[���h�s����g���Ĉړ�������
	capsule.start = Vector3::Transform(m_collision.start, m_world);
	capsule.end   = Vector3::Transform(m_collision.end,   m_world);
	capsule.r = m_collision.r;
	
	return capsule;
}

void CollisionCapsule::DrawCollision()
{
	if (m_game)
	{
		//�f�o�b�O�p�R���W�����̕`��
		m_obj->Draw(m_game->GetContext(), *m_game->GetState()
			, m_world, m_game->GetView(), m_game->GetProjection());
	}
}
