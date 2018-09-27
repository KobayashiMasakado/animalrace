#include "pch.h"
#include "CollisionCapsule.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void CollisionCapsule::SetCollision(Collision::Capsule capsule)
{
	//コリジョン情報の設定
	m_collision = capsule;
	if (m_game)
	{
		//デバッグ用コリジョンモデルの作成
		m_obj = std::make_unique<DebugCapsule>
			(m_game->GetDevice(),
				m_collision.start, 	//芯線の開始点 
				m_collision.end,	//芯線の終了点
				m_collision.r);		//半径
	}
}

Collision::Capsule CollisionCapsule::GetCollision()
{
	Collision::Capsule capsule;

	//コリジョン情報をワールド行列を使って移動させる
	capsule.start = Vector3::Transform(m_collision.start, m_world);
	capsule.end   = Vector3::Transform(m_collision.end,   m_world);
	capsule.r = m_collision.r;
	
	return capsule;
}

void CollisionCapsule::DrawCollision()
{
	if (m_game)
	{
		//デバッグ用コリジョンの描画
		m_obj->Draw(m_game->GetContext(), *m_game->GetState()
			, m_world, m_game->GetView(), m_game->GetProjection());
	}
}
