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
	ItemPlayerCreate();
	//ItemCPUCreate();
	//ItemPlayerEraseCreate();
	//ItemCPUEraseCreate();
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

void Item::ItemPlayerCreate()
{
	Collision::Capsule capsuleItemPlayer[ScenePlay::ITEM_SET_NUM];

	ModelDate* modelDate = ModelDate::GetInstance();

	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
	
		SetModel(modelDate->GetItemPlayer());
		// カプセル型のコリジョンをつける
		capsuleItemPlayer[i].r = 1.5f;                                    //半径
		switch (i)
		{
		case 0:
			SetPosition(Vector3(-93.5f, 0, 40.0f));
			capsuleItemPlayer[0].start = Vector3(0.5f, 0.5f, 0.5f);       //境界球の中心
			capsuleItemPlayer[0].end = Vector3(0.5f, 0.5f, 0.5f);		    //境界球の中心
			break;
		case 1:
			SetPosition(Vector3(94.0f, 0, 10.0f));
			capsuleItemPlayer[1].start = Vector3(1.0f, 1.0f, 1.0f);           //境界球の中心
			capsuleItemPlayer[1].end = Vector3(1.0f, 1.0f, 1.0f);		    //境界球の中心
			break;
		}
		SetCollision(capsuleItemPlayer[i]);
	}
}
////アイテム効果切れ(プレイヤー)
//void Item::ItemPlayerEraseCreate()
//{
//	Collision::Capsule capsuleItemPlayerErase[ScenePlay::ITEM_SET_NUM];
//
//	ModelDate* modelDate = ModelDate::GetInstance();
//
//	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
//	{
//		SetModel(modelDate->GetItemErasePlayer());
//		capsuleItemPlayerErase[i].r = 1.5f;                                    //半径
//		switch (i)
//		{
//		case 0:
//			SetPosition(Vector3(0.0f, 14, 95.0f));
//			capsuleItemPlayerErase[0].start = Vector3(0.5f, 0.5f, 5.0f);           //境界球の中心
//			capsuleItemPlayerErase[0].end = Vector3(0.5f, 0.5f, -5.0f);		    //境界球の中心
//			break;
//		case 1:
//			SetPosition(Vector3(30.0f, 0, -75.0f));
//			capsuleItemPlayerErase[1].start = Vector3(3.5f, 0.5f, 5.0f);           //境界球の中心
//			capsuleItemPlayerErase[1].end = Vector3(-3.5f, 0.5f, -5.0f);		    //境界球の中心
//			break;
//		}
//		SetCollision(capsuleItemPlayerErase[i]);
//	}
//}
//アイテム作成(CPU)
void Item::ItemCPUCreate()
{
	Collision::Capsule capsuleItemCPU[ScenePlay::ITEM_SET_NUM];

	ModelDate* modelDate = ModelDate::GetInstance();

	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		SetModel(modelDate->GetItemCPU());
		capsuleItemCPU[i].r = 1.5f;                                    //半径
		switch (i)
		{
		case 0:
			SetPosition(Vector3(-98.5f, 0, 40.0f));
			capsuleItemCPU[0].start = Vector3(0.5f, 0.5f, 0.5f);       //境界球の中心
			capsuleItemCPU[0].end = Vector3(0.5f, 0.5f, 0.5f);		    //境界球の中心
			break;
		case 1:
			SetPosition(Vector3(88.0f, 0, 10.0f));
			capsuleItemCPU[1].start = Vector3(1.0f, 1.0f, 1.0f);           //境界球の中心
			capsuleItemCPU[1].end = Vector3(1.0f, 1.0f, 1.0f);		    //境界球の中心
			break;
		}
		SetCollision(capsuleItemCPU[i]);
	}
}
////アイテム効果切れ(CPU)
//void Item::ItemCPUEraseCreate()
//{
//	Collision::Capsule capsuleItemCPUErase[ScenePlay::ITEM_SET_NUM];
//
//	ModelDate* modelDate = ModelDate::GetInstance();
//
//	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
//	{
//		SetModel(modelDate->GetItemEraseCPU());
//		capsuleItemCPUErase[i].r = 1.5f;                                    //半径
//		switch (i)
//		{
//		case 0:
//			SetPosition(Vector3(0.0f, 14, 95.0f));
//			capsuleItemCPUErase[0].start = Vector3(0.5f, 0.5f, 5.0f);           //境界球の中心
//			capsuleItemCPUErase[0].end = Vector3(0.5f, 0.5f, -5.0f);		    //境界球の中心
//			break;
//		case 1:
//			SetPosition(Vector3(30.0f, 0, -75.0f));
//			capsuleItemCPUErase[1].start = Vector3(3.5f, 0.5f, 5.0f);           //境界球の中心
//			capsuleItemCPUErase[1].end = Vector3(-3.5f, 0.5f, -5.0f);		    //境界球の中心
//			break;
//		}
//		SetCollision(capsuleItemCPUErase[i]);
//	}
//}
