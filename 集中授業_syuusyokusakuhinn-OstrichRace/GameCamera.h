#pragma once
#include "pch.h" 

class GameCamera
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
		DirectX::SimpleMath::Matrix view; 
		view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, DirectX::SimpleMath::Vector3(0,1,0));
		return view;
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