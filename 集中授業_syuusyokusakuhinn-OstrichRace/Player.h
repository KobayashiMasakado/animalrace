#pragma once
///------------------------------------------- 
/// Player.h
/// 
/// プレイヤーを司るクラス
/// Day.6/27
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"

class Player : public CollisionCapsule
{
public:
	//
	enum Direction
	{
		NONE,       // 移動しない
		FRONT,      // 前進　
		BACK,	    // 後進
		LEFT_TURN,  // 右旋回
		RIGHT_TURN, // 左旋回
		UP_ANGLE,   // 上向きに角度を変える
		DOWN_ANGLE,  // 下向きに角度を変える
		FRONT_ITEMGET,//前進(通常より速い)
		FBONT_SPEEDDOWN,//前進(通常より遅い)
		GRAVITY,       //重力
	};
private:
	//速度
	DirectX::SimpleMath::Vector3 m_vec;
	DirectX::SimpleMath::Vector3 m_vecZ;
	//向き
	float m_dir;
	float m_z;

	// 移動情報（ビット）
	int m_move;

public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//更新
	bool Update(float elapsedTime);
	//描画
	void Render();

	//エフェクトの設定関数
	void SetUpEffect();

	//プレイヤーが走る
	void PlayerMove(Direction dir);

	void PlayerCreate(/*Player* player, DirectX::Model* playerModel, TaskManager& taskManager*/);
	
	float GetDirection()
	{
		return m_dir;
	}

	//プレイヤーの移動のGet関数
	DirectX::SimpleMath::Vector3 GetPlayer()
	{
		return m_position;
	}
	//プレイヤーの回転のGet関数
	DirectX::SimpleMath::Quaternion GetRot()
	{
		return m_rotation;
	}

	DirectX::SimpleMath::Quaternion GetRotZ()
	{
		return m_rotationZ;
	}
	
	void SetVector(DirectX::SimpleMath::Vector3 vec)
	{
		this->m_vec = vec;
	}

	void SetVectorZ(DirectX::SimpleMath::Vector3 vecZ)
	{
		this->m_vecZ = vecZ;
	}
};