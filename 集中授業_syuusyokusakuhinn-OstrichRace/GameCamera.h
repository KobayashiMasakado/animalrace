#pragma once

#include "pch.h" 

#include "GameCamera.h"
#include "Utility.h"


class GameCamera : public SingletonBase<GameCamera>
{
private:
	//��
	DirectX::SimpleMath::Vector3 m_eye;
	//�^�[�Q�b�g�̏ꏊ
	DirectX::SimpleMath::Vector3 m_target;
public:
	//�R���X�g���N�^
	GameCamera();
	//�Q�b�^�[�֐�
	DirectX::SimpleMath::Matrix GetViewMatrix()
	{
		//�r���[
		DirectX::SimpleMath::Matrix m_view; 
		m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, DirectX::SimpleMath::Vector3(0,1,0));
		return m_view;
	}
	//�Z�b�^�[�֐�
	void SetEye(DirectX::SimpleMath::Vector3 eye)
	{
		this->m_eye = eye;
	}
	void SetTarget(DirectX::SimpleMath::Vector3 target)
	{
		this->m_target = target;
	}

};