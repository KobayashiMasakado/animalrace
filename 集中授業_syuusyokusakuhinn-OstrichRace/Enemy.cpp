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
	m_vec  = Vector3(0, 0, 0);
	m_vecZ = Vector3(0, 0, 0);
	if (m_move & (1 << NONE))
	{
		m_vec.z = 0.0f;
	}
	//前進
	if (m_move & (1 << FRONT))
	{
		m_vec.z = 0.48f;
	}
	//前進(アイテム獲得で速度は速い)
	else if (m_move & (1 << FRONT_ITEMGET))
	{
		m_vec.z = 0.65f;
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

	if (m_move & (1 << UP_ANGLE))
	{
		m_vec.y = 0.07f;
	}
	if (m_move & (1 << DOWN_ANGLE))
	{
		m_vec.y = -0.07f;
	}
	
	//ビットフラグをリセット
	m_move = 0;

	//オブジェクトを移動する
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);
	m_rotationZ = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 0.0f, 1.0f), m_z);

	m_vec = Vector3::Transform(m_vec, m_rotation);
	m_vecZ = Vector3::Transform(m_vecZ, m_rotationZ);
	m_position += (m_vec + m_vecZ);

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
	capsuleCPU.r = 0.3f;                                    //半径
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

//void Enemy::EnemyDirection(std::unique_ptr<Root> box[ENEMY_HITCHECK_NUM])
//{
	////アイテム取得時の移動速度
	//if (m_itemCPUCheck == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_ITEMGET);
	//}//通常の移動速度
	//else if (m_itemCPUCheck == false)
	//{
	//	EnemyChangeAngle(Enemy::FRONT);
	//}
	//
	//if (Collision::HitCheck_Capsule2Capsule(box[2]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_SIDE);
	//}
	//else	if (Collision::HitCheck_Capsule2Capsule(box[1]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[3]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[4]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[5]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[6]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_SIDE);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[7]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[8]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_SECOND);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[9]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[10]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::RIGHT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[11]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_SECOND);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[12]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLF);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[13]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_SIDE);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[14]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[16]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLB);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[15]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::BACK);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[17]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_SIDE);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[0]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::FRONT_SECOND);
	//}
	//else if (Collision::HitCheck_Capsule2Capsule(box[18]->GetCollision(), GetCollision()) == true)
	//{
	//	EnemyChangeAngle(Enemy::LEFT_OBLF);
	//}
	////当たった場所によってCPUの方向を変える
	//for (int i = 0; i < ScenePlay::ENEMY_HITCHECK_NUM; i++)
	//{
	//	if (Collision::HitCheck_Capsule2Capsule(GetCollision(), GetCollision()))
	//	{
	//		EnemyChangeAngle(static_cast<Enemy::Direction>(i));
	//	}
	//}
//}

void Enemy::CPUItemGet(std::unique_ptr<Item> m_itemCPU[ITEM_SET_NUM], std::unique_ptr<Item> m_itemCPUErase[ITEM_SET_NUM])
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