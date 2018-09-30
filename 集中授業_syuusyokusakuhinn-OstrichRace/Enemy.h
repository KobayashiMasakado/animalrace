#pragma once
///-------------------------------------------- 
/// Enemy.h
/// 
/// 敵を司るクラス
/// Day.7/4
/// MasakadoKobayashi
///-------------------------------------------
#include "pch.h"
#include "DeviceResources.h"
#include "CollisionCapsule.h"

class Enemy : public CollisionCapsule
{
public:
	enum Direction
	{
		NONE,         //移動しない
		FRONT,        //　前進　
		BACK,	      //　後進
		LEFT_OBLF,    //　左ナナメ前
		RIGHT_OBLF,   //　右ナナメ前
		LEFT_SIDE,    //　左横
		RIGHT_SIDE,   //　右横
		LEFT_OBLB,    //　左ナナメ後ろ
		RIGHT_OBLB,   //　右ナナメ後ろ
		FRONT_SECOND, //　前進　
		RIGHT_OBLF40, //　右ナナメ前(40)
		FRONT_ITEMGET,//前進(アイテム獲得で速度は速い)
	};
private:
	//向き
	float m_dir;
	//移動情報（ビット）
	int m_move;

public:
	//コンストラクタ
	Enemy();
	~Enemy();
	//更新
	bool Update(float elapsedTime);
	//描画
	void Render();
	void CPUCreate();
	//CPUが走る
	void EnemyChangeAngle(Direction dir);

	
};