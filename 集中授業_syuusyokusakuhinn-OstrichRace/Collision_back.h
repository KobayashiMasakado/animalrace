#pragma once
/// <summary>
/// Collision.h
/// 
/// �����蔻��̔�������邽�߂̃N���X
/// 
/// Day.7/5
/// Masakado�@Kobayashi
/// </summary>
#include "pch.h"
class Collision
{
public:
	//�J�v�Z���̍\����
	struct Capsule
	{
		DirectX::SimpleMath::Vector3 start;   //���ԕ��̐����̊J�n�_
		DirectX::SimpleMath::Vector3 end;     //���ԕ��̐����̏I���_
		float r;                              //���̔��a
	};

	//�J�v�Z���ƃJ�v�Z���̓����蔻��֐�
	static bool HitCheck_Capsule(Capsule capsule1, Capsule capsule2)
	{
		return 0;
	}


};