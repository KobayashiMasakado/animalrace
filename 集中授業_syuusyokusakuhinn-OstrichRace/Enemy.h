#pragma once
///-------------------------------------------- 
/// Enemy.h
/// 
/// 敵を司るクラス
/// Day.7/4
/// MasakadoKobayashi
///-------------------------------------------
#include "pch.h"

#include <sys/timeb.h>
#include "DeviceResources.h"
#include "CollisionCapsule.h"

#include "Item.h"
class Root;

class Enemy : public CollisionCapsule
{
public:
	static const int ITEM_SET_NUM = 2;
	static const int ENEMY_HITCHECK_NUM = 23;
public:
	enum Direction
	{
		NONE,          //移動しない
		FRONT,         //　前進　
		LEFT_OBLF,     //　左ナナメ前
		RIGHT_OBLF,    //　右ナナメ前
		BACK,	       //　後進
		LEFT_SIDE,     //　左横
		RIGHT_SIDE,    //　右横
		LEFT_OBLB,     //　左ナナメ後ろ
		RIGHT_OBLB,    //　右ナナメ後ろ
		FRONT_SECOND,  //　前進　
		RIGHT_OBLF40,  //　右ナナメ前(40)
		UP_ANGLE,      // 上向きに角度を変える
		DOWN_ANGLE,    // 下向きに角度を変える
		FRONT_ITEMGET, //前進(アイテム獲得で速度は速い)
		FRONT_FUNGET,  // 前進(通常より遅い)
	};

	enum Warp
	{
		ZERO,
		ONE,
		TWO,
		THREE,
		FORE,
		FIVE
	};
private:
	//aa鎮魂歌
	DirectX::SimpleMath::Vector3 m_startPos;
	DirectX::SimpleMath::Vector3 m_targetPos;

	DirectX::SimpleMath::Vector3 m_CPUPoint[5];

	//向き
	float m_dir;
	//移動情報（ビット）
	int m_move;

	int m_moveW;

	bool m_itemCPUCheck;
	bool m_itemCPUBadCheck;
	bool m_itemCPUFunCheck;

	//CPUがワープする場所
	DirectX::SimpleMath::Vector3 m_cpuSetPos[6];

	//	DirectX::SimpleMath::Vector3 m_vec;

	timeb m_startTime;
	//
	float m_count;

	/*float xn[100];
	float yn[100];
	int x;*/

public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	//更新
	bool Update(float elapsedTime);
	//描画
	void Render();
	//CPU作成
	void CPUCreate();
	//CPUが走る
	void EnemyChangeAngle(Direction dir);
	void EnemyDirection(std::unique_ptr<Root> box[ENEMY_HITCHECK_NUM]);
	//CPUがワープする
	void CPUWarp(Warp warp);

	void CPUItemGet(std::unique_ptr<Item> itemCPU[ITEM_SET_NUM],
		std::unique_ptr<Item> itemCPUErase[ITEM_SET_NUM],
		std::unique_ptr<Item> itemCPUBad[ITEM_SET_NUM],
		std::unique_ptr<Item> itemCPUBadErase[ITEM_SET_NUM],
		std::unique_ptr<Item> itemFun[ITEM_SET_NUM],
		std::unique_ptr<Item> itemFunErase[ITEM_SET_NUM]);

	bool GetItemCPU() { return m_itemCPUCheck; }
	bool GetItemCPUBad() { return m_itemCPUBadCheck; }
	bool GetItemCPUFun() { return m_itemCPUFunCheck; }

	DirectX::SimpleMath::Vector3 lerp(DirectX::SimpleMath::Vector3 startPos, DirectX::SimpleMath::Vector3 targetPos, float time);

	//プレイヤーの移動のGet関数
	DirectX::SimpleMath::Vector3 GetCPUPosition()
	{
		return m_position;
	}

};