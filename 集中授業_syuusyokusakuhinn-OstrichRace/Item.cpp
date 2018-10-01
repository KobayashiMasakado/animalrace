#include "pch.h"
#include "Item.h"

#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
Item::Item()
{
}
/// <summary>
/// デストラクタ
/// </summary>
Item::~Item()
{
}
/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTIme"></param>
/// <returns></returns>
bool Item::Update(float elapsedTIme)
{
	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// 描画
/// </summary>
void Item::Render()
{
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//デバッグ用コリジョンモデルの描画
	//	DrawCollision();
	}
	
}

void Item::SetUpEffect()
{
	m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetPerPixelLighting(true);
		}
	});
}

//アイテム作成(プレイヤー)
void Item::ItemPlayerCreate(int item)
{
	Collision::Capsule capsule;
	capsule.r = 1.5f;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetItemPlayer());
	SetUpEffect();
	switch (item)
	{
	case 0:
		SetPosition(Vector3(-93.5f, 0, 40.0f));
		capsule.start = Vector3(0.5f, 0.5f, 0.5f);       //境界球の中心
		capsule.end = Vector3(0.5f, 0.5f, 0.5f);		    //境界球の中心

		break;
	case 1:
		SetPosition(Vector3(94.0f, 0, 10.0f));
		capsule.start = Vector3(1.0f, 1.0f, 1.0f);           //境界球の中心
		capsule.end = Vector3(1.0f, 1.0f, 1.0f);		    //境界球の中心

		break;
	}
	SetCollision(capsule);
}
//アイテム効果切れ(プレイヤー)
void Item::ItemPlayerEraseCreate(int item)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	capsule.r = 1.5f;                                    //半径
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		SetModel(modelDate->GetItemErasePlayer());
   
		switch (item)
		{
		case 0:
			SetPosition(Vector3(0.0f, 14, 95.0f));
			capsule.start = Vector3(0.5f, 0.5f, 7.0f);           //境界球の中心
			capsule.end = Vector3(-0.5f, 0.5f, -7.0f);		    //境界球の中心
			break;
		case 1:
			SetPosition(Vector3(30.0f, 0, -75.0f));
			capsule.start = Vector3(3.5f, 0.5f, 6.0f);           //境界球の中心
			capsule.end = Vector3(-3.5f, 0.5f, -6.0f);		    //境界球の中心
			break;
		}
		SetCollision(capsule);
	}
}
//アイテム作成(CPU)
void Item::ItemCPUCreate(int item)
{
	Collision::Capsule capsule;
	capsule.r = 1.5f;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetItemCPU());
	SetUpEffect();
	
	switch (item)
	{
	case 0:
		SetPosition(Vector3(-98.5f, 0, 40.0f));
		capsule.start = Vector3(0.5f, 0.5f, 0.5f);       //境界球の中心
		capsule.end = Vector3(0.5f, 0.5f, 0.5f);		    //境界球の中心
		break;
	case 1:
		SetPosition(Vector3(88.0f, 0, 10.0f));
		capsule.start = Vector3(1.0f, 1.0f, 1.0f);           //境界球の中心
		capsule.end = Vector3(1.0f, 1.0f, 1.0f);		    //境界球の中心
		break;
	}
	SetCollision(capsule);
	
}
//アイテム効果切れ(CPU)
void Item::ItemCPUEraseCreate(int item)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetItemEraseCPU());

	capsule.r = 1.5f;                  //半径
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		
		                                   
		switch (item)
		{
		case 0:
			SetPosition(Vector3(0.0f, 14, 95.0f));
			capsule.start = Vector3(0.5f, 0.5f, 15.0f);           //境界球の中心
			capsule.end = Vector3(0.5f, 0.5f, -15.0f);		    //境界球の中心
			break;
		case 1:
			SetPosition(Vector3(30.0f, 0, -75.0f));
			capsule.start = Vector3(3.5f, 0.5f, 5.0f);           //境界球の中心
			capsule.end = Vector3(-3.5f, 0.5f, -5.0f);		    //境界球の中心
			break;
		}
		SetCollision(capsule);
	}
}
