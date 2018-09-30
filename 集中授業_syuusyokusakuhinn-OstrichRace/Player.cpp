#include "pch.h"
#include "Player.h"
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;
/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
{
	m_move = 0;
	m_dir = 0.0f;
	m_z = 0.0f;
	m_itemPlayerCheck = false;
	m_itemPlayerBadCheck = false;
}
/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	
}
/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime"></param>
/// <returns></returns>
bool Player::Update(float elapsedTime)
{
	m_vec = Vector3(0, 0, 0);

	if (m_move & (1 << NONE))
	{
		m_vec.z = 0.0f;
	}
	//前進
	if (m_move & (1 << FRONT))
	{
		m_vec.z = 0.25f;
	}
	//前進(通常より速度は速い)
	else if (m_move & (1 << FRONT_ITEMGET))
	{
		m_vec.z = 0.4f;
	}
	//前進(通常より速度は遅い)
	else if (m_move & (1 << FBONT_SPEEDDOWN))
	{
		m_vec.z = 0.05f;
	}
	//後進
	else if (m_move & (1 << BACK))
	{
		m_vec.z = -0.5f;
	}
	//右旋回
	if (m_move & (1 << RIGHT_TURN))
	{
		m_dir -= XMConvertToRadians(1.0f);
	}
	//左旋回
	else if (m_move & (1 << LEFT_TURN))
	{
		m_dir += XMConvertToRadians(1.0f);
	}

	//上
	if (m_move & (1 << UP_ANGLE))
	{
		m_z = XMConvertToRadians(-65.0f);
	}
	//下
	else if (m_move & (1 << DOWN_ANGLE))
	{
		m_z = XMConvertToRadians(1.0f);
	}

	if (m_move & (1 << GRAVITY))
	{
		m_vec.y -= 0.1f;
	}
	
	//ビットフラグをリセットする
	m_move = 0;

	//オブジェクトを移動する
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);/*
	m_rotationZ = Quaternion::CreateFromAxisAngle(Vector3(1.0f, 0.0f, 0.0f), m_z);*/
	m_vec = Vector3::Transform(m_vec, m_rotation);/*
	m_vecZ = Vector3::Transform(m_vec, m_rotationZ);*/
	
	m_position += (m_vec);

	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// 描画
/// </summary>
void Player::Render()
{
	PlayerCreate();
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(),*m_game->GetState(),m_world, m_game->GetView(), m_game->GetProjection());
		//デバッグ用コリジョンモデルの描画
	//	DrawCollision();
		
	}
}
/// <summary>
/// プレイヤーが走る
/// </summary>
/// <param name="dir"></param>
void Player::PlayerMove(Direction dir)
{
	//ビットフラグ
	m_move |= (1 << dir);
}

void Player::PlayerCreate()
{
	Collision::Capsule capsulePlayer;

	ModelDate* modelDate = ModelDate::GetInstance();

	SetPosition(Vector3(-93.5f, 0, 1.5f));
	SetGame(m_game);
	SetModel(modelDate->GetPlayer());
	SetUpEffect();
	// カプセル型のコリジョンをつける
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//境界球の中心
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		    //境界球の中心
	capsulePlayer.r = 0.6f;							     	//半径
	SetCollision(capsulePlayer);
}

void Player::PlayerOperation(DirectX::Keyboard::State &kb)
{
	//上キーが押されたら
	if (kb.Up || kb.W)
	{
		if (m_itemPlayerCheck == true)
		{
			PlayerMove(Player::FRONT_ITEMGET);
		}
		else if (m_itemPlayerCheck == false)
		{
			PlayerMove(Player::FRONT);
		}
	}
	//下キーが押されたら
	if (kb.Down || kb.S)
	{
		//	m_player->PlayerMove(Player::UP_ANGLE);
	}
	//右キーが押されたら
	if (kb.Right || kb.D)
	{
		PlayerMove(Player::RIGHT_TURN);
	}
	//左キーが押されたら
	if (kb.Left || kb.A)
	{
		PlayerMove(Player::LEFT_TURN);
	}
}

//プレイヤー操作(コース外)
void Player::PlayerOperationwOutSide(DirectX::Keyboard::State & kb)
{
	//上キーが押されたら
	if (kb.Up || kb.W)
	{
		PlayerMove(Player::FBONT_SPEEDDOWN);
	}
	//右キーが押されたら
	if (kb.Right || kb.D)
	{
		PlayerMove(Player::RIGHT_TURN);
	}
	//左キーが押されたら
	if (kb.Left || kb.A)
	{
		PlayerMove(Player::LEFT_TURN);
	}
}

void Player::PlayerItemGet(std::unique_ptr<Item> itemPlayer[2],
                           std::unique_ptr<Item> itemPlayerErase[2],
                           std::unique_ptr<Item> itemCPU[2],
                           std::unique_ptr<Item> itemCPUErase[2])
{
	//プレイヤーのアイテム取得
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		//プレイヤー用のアイテム取得
		if (Collision::HitCheck_Capsule2Capsule(itemPlayer[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerCheck = true;
		}
		//プレイヤー用のアイテム効果切れ
		else if (Collision::HitCheck_Capsule2Capsule(itemPlayerErase[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerCheck = false;
		}
		//CPU用のアイテム取得
		if (Collision::HitCheck_Capsule2Capsule(itemCPU[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerBadCheck = true;
		}
		//CPU用のアイテム効果切れ
		else if (Collision::HitCheck_Capsule2Capsule(itemCPUErase[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerBadCheck = false;
		}
	}

}

void Player::SetUpEffect()
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
