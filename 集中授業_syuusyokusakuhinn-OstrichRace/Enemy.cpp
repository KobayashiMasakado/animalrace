#include "pch.h"
#include "Enemy.h"
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	m_move = 0;
	m_dir = 0.0f;
	m_itemCPUCheck = false;
}
/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy()
{
}
/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
/// <returns></returns>
bool Enemy::Update(float elapsedTime)
{
	Vector3 vec(0, 0, 0);
	if (m_move & (1 << NONE))
	{
		vec.z = 0.0f;
	}
	//前進
	if (m_move & (1 << FRONT))
	{
		vec.z = 0.48f;
		//vec.z = 0.8f;
	}
	//前進(アイテム獲得で速度は速い)
	else if (m_move & (1 << FRONT_ITEMGET))
	{
		vec.z = 0.65f;
	}
	//後進
	if (m_move & (1 << BACK))
	{
		m_dir = XMConvertToRadians(180.0f);
	}
	//右ナナメ前
	if (m_move & (1 << RIGHT_OBLF))
	{
		m_dir = XMConvertToRadians(40.0f);
	}
	//左ナナメ前
	else if (m_move & (1 << LEFT_OBLF))
	{
		m_dir = XMConvertToRadians(-45.0f);
	}
	if (m_move & (1 << RIGHT_OBLF40))
	{
		m_dir = XMConvertToRadians(30.0f);
	}
	//右横
	if (m_move & (1 << RIGHT_SIDE))
	{
		m_dir = XMConvertToRadians(90.0f);
	}
	//左横
	else if (m_move & (1 << LEFT_SIDE))
	{
		m_dir = XMConvertToRadians(-90.0f);
	}
	//右ナナメ後ろ
	if (m_move & (1 << RIGHT_OBLB))
	{
		m_dir = XMConvertToRadians(135.0f);
	}
	//左ナナメ後ろ
	else if (m_move & (1 << LEFT_OBLB))
	{
		m_dir = XMConvertToRadians(-135.0f);
	}
	//前進
	if (m_move & (1 << FRONT_SECOND))
	{
		m_dir = XMConvertToRadians(0.0f);
	}
	//ビットフラグをリセット
	m_move = 0;

	//オブジェクトを移動する
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);
	vec = Vector3::Transform(vec, m_rotation);
	m_position += vec;

	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// 描画
/// </summary>
void Enemy::Render()
{
	
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(), *m_game->GetState(),
			m_world, m_game->GetView(), m_game->GetProjection());
	
		//デバッグ用コリジョンモデルの描画
		//DrawCollision();
	}
}
/// <summary>
/// 
/// </summary>
void Enemy::CPUCreate()
{
	Collision::Capsule capsuleCPU;
	
	ModelDate* modelDate = ModelDate::GetInstance();

	SetPosition(Vector3(-97.5f, 0, 1.5f));
	SetGame(m_game);
	SetModel(modelDate->GetCPU());
	// カプセル型のコリジョンをつける
	capsuleCPU.start = Vector3(0.3f, 0.0f, 0.2f);           //境界球の中心
	capsuleCPU.end = Vector3(0.3f, 3.0f, 0.2f);		        //境界球の中心
	capsuleCPU.r = 0.6f;                                    //半径
	SetCollision(capsuleCPU);
}
/// <summary>
/// CPUが走る
/// </summary>
/// <param name="dir"></param>
void Enemy::EnemyChangeAngle(Direction dir)
{
	//ビットフラグ
	m_move |= (1 << dir);
}

void Enemy::EnemyDirection()
{
	//アイテム取得時の移動速度
	if (m_itemCPUCheck == true)
	{
		EnemyChangeAngle(Enemy::FRONT_ITEMGET);
	}//通常の移動速度
	else if (m_itemCPUCheck == false)
	{
		EnemyChangeAngle(Enemy::FRONT);
	}
	//当たった場所によってCPUの方向を変える
	for (int i = 0; i < ScenePlay::ENEMY_HITCHECK_NUM; i++)
	{
		if (Collision::HitCheck_Capsule2Capsule(GetCollision(), GetCollision()))
		{
			EnemyChangeAngle(static_cast<Enemy::Direction>(i));
		}
	}
}

void Enemy::CPUItemGet(std::unique_ptr<Item> m_itemCPU[2], std::unique_ptr<Item> m_itemCPUErase[2])
{
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		//CPUアイテム取得
		if (Collision::HitCheck_Capsule2Capsule(m_itemCPU[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUCheck = true;
		}

		if (Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[0]->GetCollision(), GetCollision()))
		{
			m_itemCPUCheck = false;
		}

	}
}