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
#include "EffectManager.h"

class Item : public CollisionCapsule
{
	public:
	static const int ITEM_SET_NUM = 2;
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
	//アイテム作成(フン)
	void ItemFunCreate(int item);
	//アイテム効果切れ(CPU)
	void ItemFunEraseCreate(int item);

	void EffectCreate(EffectManager* m_effectManager);
};