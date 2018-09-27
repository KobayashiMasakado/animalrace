#pragma once
#include "pch.h" 

class GameCamera
{
private:
	//目
	DirectX::SimpleMath::Vector3 m_eye;
	//ターゲットの場所
	DirectX::SimpleMath::Vector3 m_target;
public:
	//コンストラクタ
	GameCamera();
	//ゲッター関数
	DirectX::SimpleMath::Matrix GetViewMatrix()
	{
		//ビュー
		DirectX::SimpleMath::Matrix view; 
		view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, DirectX::SimpleMath::Vector3(0,1,0));
		return view;
	}
	//セッター関数
	void SetEye(DirectX::SimpleMath::Vector3 eye)
	{
		this->m_eye = eye;
	}
	void SetTarget(DirectX::SimpleMath::Vector3 target)
	{
		this->m_target = target;
	}

};