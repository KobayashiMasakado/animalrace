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

};