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

#include "SceneSelect.h"

#include "CollisionCapsule.h"
#include "Item.h"

#include "InputHandler.h"

class Player : public CollisionCapsule
{
public:
	// 移動
	enum Direction
	{
		NONE,            // 移動しない
		FRONT,           // 前進　
		BACK,	         // 後進
		LEFT_TURN,       // 右旋回
		RIGHT_TURN,      // 左旋回
		UP_ANGLE,        // 上向きに角度を変える
		DOWN_ANGLE,      // 下向きに角度を変える
		GRAVITY,         // 重力
	};

	enum State
	{
		STATE_NONE = 1,      // 移動しない
		BACK_OUTCOURSE = 1 << 1,	 // 後進(通常より速度は遅い)
		FRONT_ITEMGET = 1 << 2,   // 前進(通常より速い)
		FRONT_OUTCOURSE = 1 << 3, // 前進(通常より遅い)
		FRONT_FUNGET = 1 << 4,    // 前進(通常より遅い)
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

	bool m_itemPlayerCheck;
	bool m_itemPlayerBadCheck;
	bool m_itemFunCheck;
	bool m_courseOut;

	Direction m_direction;
	int m_state;

	InputHandler m_inputHandle;

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
	void PlayerState(State state);
	void PlayerDeleteState(State state);

	void PlayerState();

	void PlayerDirection();

	void PlayerCreate();

	void PlayerItemGet(std::unique_ptr<Item> itemPlayer[2], 
		               std::unique_ptr<Item> itemPlayerErase[2],
		               std::unique_ptr<Item> itemCPU[2], 
		               std::unique_ptr<Item> itemCPUErase[2],
	                   std::unique_ptr<Item> itemFun[2],
	                   std::unique_ptr<Item> itemFunErase[2]);

	bool GetItemPlayer() { return m_itemPlayerCheck; }
	bool GetItemPlayerBad() { return m_itemPlayerBadCheck; }
	bool GetItemFun() { return m_itemFunCheck; }

	float GetDirection(){ return m_dir;}

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

	DirectX::SimpleMath::Vector3 GetVector()
	{
		return this->m_vec;
	}
	
	void SetVector(DirectX::SimpleMath::Vector3 vec)
	{
		this->m_vec = vec;
	}

	void SetVectorZ(DirectX::SimpleMath::Vector3 vecZ)
	{
		this->m_vecZ = vecZ;
	}

	float GetDir()
	{
		return m_dir;
	}

	void SetDir(float dir)
	{
		this->m_dir = dir;
	}

	void SetCourseOut(bool flag)
	{
		m_courseOut = flag;
	}
};