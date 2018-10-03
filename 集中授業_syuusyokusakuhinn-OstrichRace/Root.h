#pragma once
///------------------------------------------- 
/// Root.h
/// 
/// ルートを司るクラス
/// Day.7/5
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"
#include "Player.h"
#include "Enemy.h"

class Root : public CollisionCapsule
{
private:
	bool m_hitPlayerFlag;
public:
	//コンストラクタ
	Root();
	//デストラクタ
	~Root();
	//更新
	bool Update(float elapsedTIme);
	//描画
	void Render();
	//エフェクトの設定関数
	void SetUpEffect();
	void EnemyHitMoveCreate(int course);


};