#include "pch.h"
#include "Enemy.h"
#include "Game.h"
#include <time.h>
#include "ModelDate.h"
#include "Root.h"

#include<stdio.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy()
{
	m_move = 0;
	m_moveW = 0;
	m_dir = 0.0f;
	m_count = 0;
	//m_startTime = 0;
	m_itemCPUCheck = false;

	ftime(&m_startTime);

	//m_startTime = time(NULL);

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
	m_startPos = Vector3(0, 0, 0);
	m_targetPos = Vector3(0, 0, 0);
	for (int i = 0; i < 5; i++)
	{
		m_CPUPoint[i] = Vector3(0, 0, 0);
	}
	time_t t = time(NULL);

	timeb timebuffer;
	int sec, millisec;
	float time;

	ftime(&timebuffer);
	sec = timebuffer.time - m_startTime.time;
	millisec = timebuffer.millitm - m_startTime.millitm;
	millisec += sec * 1000;
	time = (double)millisec / 10000;

	if (m_move & (1 << NONE))
	{
		/*m_vec.z = 0.0f;
		m_vec2.z = 0.0f;*/
	}
	////前進
	//if (m_move & (1 << FRONT))
	//{
	//m_vec.z = 0.35;
	//m_vec.z = 0.01;
	//}
	////前進(アイテム獲得で速度は速い)
	//if (m_move & (1 << FRONT_ITEMGET))
	//{
	//	m_vec.z = 0.80f;
	//}
	////前進(アイテム獲得で速度は遅い)
	//if (m_move & (1 << FRONT_FUNGET))
	//{
	//	m_vec.z = 0.1f;
	//}
	////後進
	//if (m_move & (1 << BACK))
	//{
	//	m_dir = XMConvertToRadians(180.0f);
	//}
	////右ナナメ前
	//if (m_move & (1 << RIGHT_OBLF))
	//{
	//	m_dir = XMConvertToRadians(40.0f);
	//}
	////左ナナメ前
	//else if (m_move & (1 << LEFT_OBLF))
	//{
	//	m_dir = XMConvertToRadians(-45.0f);
	//}
	//if (m_move & (1 << RIGHT_OBLF40))
	//{
	//	m_dir = XMConvertToRadians(30.0f);
	//}
	////右横
	//if (m_move & (1 << RIGHT_SIDE))
	//{
	//	m_dir = XMConvertToRadians(90.0f);
	//}
	////左横
	//else if (m_move & (1 << LEFT_SIDE))
	//{
	//	m_dir = XMConvertToRadians(-90.0f);
	//}
	////右ナナメ後ろ
	//if (m_move & (1 << RIGHT_OBLB))
	//{
	//	m_dir = XMConvertToRadians(135.0f);
	//}
	////左ナナメ後ろ
	//else if (m_move & (1 << LEFT_OBLB))
	//{
	//	m_dir = XMConvertToRadians(-135.0f);
	//}
	////前進
	//if (m_move & (1 << FRONT_SECOND))
	//{
	//	m_dir = XMConvertToRadians(0.0f);
	//}
	//if (m_move & (1 << UP_ANGLE))
	//{
	//	m_vec.y = 0.07f;
	//}
	//if (m_move & (1 << DOWN_ANGLE))
	//{
	//	m_vec.y = -0.08f;
	//}
	//
	if (m_moveW & (1 << ZERO))
	{
		m_cpuSetPos[0] = (Vector3(-97.5f, 0, 1.5f));
	}
	if (m_moveW & (1 << ONE))
	{
		m_cpuSetPos[1] = (Vector3(0, 10, 95.0f));
	}
	if (m_moveW & (1 << TWO))
	{
		m_cpuSetPos[2] = (Vector3(93.0f, 0, 0.0f));
	}
	if (m_moveW & (1 << THREE))
	{
		m_cpuSetPos[3] = (Vector3(10.0f, 0, 0));
	}
	if (m_moveW & (1 << FORE))
	{
		m_cpuSetPos[4] = (Vector3(-40.0f, 10, 0));
	}
	if (m_moveW & (1 << FIVE))
	{
		m_cpuSetPos[5] = (Vector3(-96.0f, 0, -3.0f));
	}
	for (int i = 0; i < 5; i++)
	{
		switch (i)
		{
		case 0:
			m_CPUPoint[i] = Vector3(-96.0f, 0, 1.5f);
			break;
		case 1:
			m_CPUPoint[i] = Vector3(0, 10, 95.0f);
			break;
		case 2:
			m_CPUPoint[i] = Vector3(93.0f, 0, 0.0f);
			break;
		case 3:
			m_CPUPoint[i] = Vector3(10.0f, 0, 0);
			break;
		case 4:
			m_CPUPoint[i] = Vector3(-40.0f, 10, 0);
			break;
		case 5:
			m_CPUPoint[i] = Vector3(-96.0f, 0, -3.0f);
			break;
		}
	}

	//ビットフラグをリセット
	m_move = 0;
	m_moveW = 0;

	//オブジェクトを移動する
	//	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);

	//	m_vec = Vector3::Transform(m_vec, m_rotation);
	//	lerp((double)m_vec.x, (double)m_vec.y, (double)m_vec.x+10.0, (double)m_vec.y+10.0, (double)m_vec.z);
	/*double x0 = -97.5;
	double y0 = 0.0;
	double x1 = 0.0;
	double y1 = 10.0;
	double x  = -75.0;

	m_vec.x = x0;
	m_vec.y = y0;
	m_vec2.x = x1;
	m_vec2.y = y1;*/

	m_startPos = (Vector3(-97.5f, 0, 1.5f));
	m_targetPos = (Vector3(-97.5f, 0, 10.5f));

	float timeStep;
	m_count = 10.8f;
	if (m_count > 0.0f)
	{
		timeStep = time / m_count;
	}
	else
	{
		timeStep = 1.0f;
	}

	Vector3 vec = lerp(m_CPUPoint[0], m_CPUPoint[1], timeStep);
	//m_position += vec;


	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(vec);

	//敵がワープする
	/*if (m_count % 60 == 0)
	{
	int a = (m_count / 60) % 6;
	m_world = Matrix::CreateTranslation(m_cpuSetPos[a]);
	}

	m_count++;*/
	//////////

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

void Enemy::EnemyDirection(std::unique_ptr<Root> box[ENEMY_HITCHECK_NUM])
{
	//アイテム取得時の移動速度
	if (GetItemCPU() == true)
	{
		EnemyChangeAngle(Enemy::FRONT_ITEMGET);
	}
	else if (GetItemCPUBad() == true ||
		GetItemCPUFun() == true)
	{
		EnemyChangeAngle(Enemy::FRONT_FUNGET);
	}
	//通常の移動速度
	else
	{
		EnemyChangeAngle(Enemy::FRONT);
	}

	if (Collision::HitCheck_Capsule2Capsule(box[2]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::UP_ANGLE);
		EnemyChangeAngle(Enemy::RIGHT_SIDE);
	}
	else	if (Collision::HitCheck_Capsule2Capsule(box[1]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::RIGHT_OBLF);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[3]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::RIGHT_SIDE);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[4]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::DOWN_ANGLE);
		EnemyChangeAngle(Enemy::RIGHT_SIDE);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[5]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::RIGHT_OBLB);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[6]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::BACK);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[7]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_OBLB);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[8]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_SIDE);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[9]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_OBLF);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[10]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::FRONT_SECOND);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[11]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::RIGHT_OBLF);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[12]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::RIGHT_OBLF);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[13]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::FRONT_SECOND);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[14]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_OBLF);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[15]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_SIDE);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[16]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_OBLB);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[17]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::UP_ANGLE);
		EnemyChangeAngle(Enemy::BACK);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[18]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::BACK);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[19]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::DOWN_ANGLE);
		EnemyChangeAngle(Enemy::BACK);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[20]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_OBLB);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[21]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_SIDE);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[0]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::FRONT_SECOND);
	}
	else if (Collision::HitCheck_Capsule2Capsule(box[22]->GetCollision(), GetCollision()) == true)
	{
		EnemyChangeAngle(Enemy::LEFT_OBLF);
	}
	////当たった場所によってCPUの方向を変える
	//for (int i = 0; i < ScenePlay::ENEMY_HITCHECK_NUM; i++)
	//{
	//	if (Collision::HitCheck_Capsule2Capsule(GetCollision(), GetCollision()))
	//	{
	//		EnemyChangeAngle(static_cast<Enemy::Direction>(i));
	//	}
	//}
}

void Enemy::CPUWarp(Warp warp)
{
	//ビットフラグ
	m_moveW |= (1 << warp);
}

void Enemy::CPUItemGet(std::unique_ptr<Item> itemCPU[ITEM_SET_NUM],
	std::unique_ptr<Item> itemCPUErase[ITEM_SET_NUM],
	std::unique_ptr<Item> itemCPUBad[ITEM_SET_NUM],
	std::unique_ptr<Item> itemCPUBadErase[ITEM_SET_NUM],
	std::unique_ptr<Item> itemCPUFun[ITEM_SET_NUM],
	std::unique_ptr<Item> itemCPUFunErase[ITEM_SET_NUM])
{
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		//CPUアイテム取得
		if (Collision::HitCheck_Capsule2Capsule(itemCPU[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUCheck = true;
		}
		if (Collision::HitCheck_Capsule2Capsule(itemCPUErase[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUCheck = false;
		}
		if (Collision::HitCheck_Capsule2Capsule(itemCPUBad[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUBadCheck = true;
		}
		if (Collision::HitCheck_Capsule2Capsule(itemCPUBadErase[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUBadCheck = false;
		}

		if (Collision::HitCheck_Capsule2Capsule(itemCPUFun[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUFunCheck = true;
		}
		if (Collision::HitCheck_Capsule2Capsule(itemCPUFunErase[i]->GetCollision(), GetCollision()))
		{
			m_itemCPUFunCheck = false;
		}
	}
}

DirectX::SimpleMath::Vector3 Enemy::lerp(DirectX::SimpleMath::Vector3 startPos, DirectX::SimpleMath::Vector3 targetPos, float time)
{
	Vector3 lerpPos = Vector3(0, 0, 0);
	lerpPos = (1 - time) * startPos + time * targetPos;
	return lerpPos;

}
