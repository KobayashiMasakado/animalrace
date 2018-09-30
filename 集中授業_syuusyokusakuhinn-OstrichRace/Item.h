#pragma once
///------------------------------------------- 
/// Item.h
/// 
/// アイテム司るクラス
/// Day.7/5
/// MasakadoKobayashi
///------------------------------------------- 
#include "pch.h"

#include "DeviceResources.h"

#include "CollisionCapsule.h"

class Item : public CollisionCapsule
{
private:

public:
	//コンストラクタ
	Item();
	//デストラクタ
	~Item();
	//更新
	bool Update(float elapsedTIme);
	//描画
	void Render();
	//エフェクトの設定関数
	void SetUpEffect();

	//アイテム作成(プレイヤー)
	void ItemPlayerCreate(int item);
	//アイテム効果切れ(プレイヤー)
	void ItemPlayerEraseCreate(int item);
	//アイテム作成(CPU)
	void ItemCPUCreate(int item);
	//アイテム効果切れ(CPU)
	void ItemCPUEraseCreate(int item);
};