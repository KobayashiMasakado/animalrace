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

class Root : public CollisionCapsule
{
private:

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
	void Root::EnemyHitMoveCreate(int course);
};