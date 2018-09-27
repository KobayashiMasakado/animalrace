#pragma once
/// <summary>
/// Collision.h
/// 
/// 当たり判定の判定をするためのクラス
/// 
/// Day.7/5
/// Masakado　Kobayashi
/// </summary>
#include "pch.h"
class Collision
{
public:
	//カプセルの構造体
	struct Capsule
	{
		DirectX::SimpleMath::Vector3 start;   //中間部の線分の開始点
		DirectX::SimpleMath::Vector3 end;     //中間部の線分の終了点
		float r;                              //球の半径
	};

	//カプセルとカプセルの当たり判定関数
	static bool HitCheck_Capsule(Capsule capsule1, Capsule capsule2)
	{
		return 0;
	}


};