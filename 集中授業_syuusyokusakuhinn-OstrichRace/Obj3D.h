#pragma once
/// /// <summary>
/// Obj3D
/// 
/// 3Dオブジェクトを描画するためのクラス
/// Day.6/256/25
/// Masakado Kobayashi
#include "pch.h"
class Game;
#include "TaskManager.h"

class Obj3D : public Task
{
protected:
	//ゲームオブジェクトへのポインタ
	Game* m_game;
	//モデルハンドル
	DirectX::Model* m_model;

	//位置
	DirectX::SimpleMath::Vector3 m_position;

	//回転
	DirectX::SimpleMath::Quaternion m_rotation;

	//回転
	DirectX::SimpleMath::Quaternion m_rotationZ;

	//ワールド行列
	DirectX::SimpleMath::Matrix m_world;

public:
	//コンストラクタ
	Obj3D();
	//更新
	virtual bool Update(float elapsedTime);

	//描画
	virtual void Render();

	// セッター関数
	//ゲームオブジェクトを設定する関数
	void SetGame(Game* game)
	{
		m_game = game;
	}

	//モデルハンドルを設定する関数
	void SetModel(DirectX::Model* model)
	{
		m_model = model;
	}

	//位置設定する関数
	void SetPosition(DirectX::SimpleMath::Vector3 position)
	{
		m_position = position;
	}

	//回転設定する関数
	void SetRotation(DirectX::SimpleMath::Quaternion rotation)
	{
		m_rotation = rotation;
	}

};