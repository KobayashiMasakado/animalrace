#pragma once
///-------------------------------------------------
/// CollisionCapsule.h
/// 
/// �J�v�Z�����������N���X
/// 
/// Day.7/5
/// Masakado Kobayashi
///-------------------------------------------------

#include "Obj3D.h"
#include "Collision.h"
#include "DebugCapsule.h"

class CollisionCapsule : public Obj3D
{
private:
	//�R���W�������
	Collision::Capsule m_collision;

	//�R���W�����\���p�I�u�W�F�N�g
	std::unique_ptr<DebugCapsule> m_obj;

public:
	//�R���W��������Set�֐�
	void SetCollision(Collision::Capsule capsule);

	//�R���W��������Get�֐�
	Collision::Capsule GetCollision();

	//�f�o�b�O�p�R���W�����\���֐�
	void DrawCollision();
};