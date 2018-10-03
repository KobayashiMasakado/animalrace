#pragma once

#include "pch.h" 

#include "GameCamera.h"
#include "Utility.h"


class GameCamera : public SingletonBase<GameCamera>
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
		DirectX::SimpleMath::Matrix m_view; 
		m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, DirectX::SimpleMath::Vector3(0,1,0));
		return m_view;
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