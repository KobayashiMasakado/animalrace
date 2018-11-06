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
	m_itemFunCheck = false;
	m_state = State::STATE_NONE;
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

	std::list<Command*> command = m_inputHandle.HandleInput();
	for (std::list<Command*>::iterator ite = command.begin(); ite != command.end(); ite++)
	{
		(*ite)->execute(this);
	}

	if (m_move == (1 << NONE))
	{
		m_vec.z = 0.0f;
	}
	
	//後進
	else if (m_move & (1 << BACK))
	{
		m_vec.z = -0.15f;
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

	PlayerState();

	//重力
	if (m_move & (1 << GRAVITY))
	{
		m_vec.y -= 0.1f;
	}

	//ビットフラグをリセットする
	m_move = 0;

	//オブジェクトを移動する
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_dir);
	m_vec = Vector3::Transform(m_vec, m_rotation);
	
	m_position += (m_vec);

	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	// フラグを伏せる
	m_courseOut = false;

	return true;
}
/// <summary>
/// 描画
/// </summary>
void Player::Render()
{
	
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(),*m_game->GetState(),m_world, m_game->GetView(), m_game->GetProjection());
	
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

void Player::PlayerState(State state)
{
	m_state |= state;
}

void Player::PlayerDeleteState(State state)
{
	int buf = !m_state;
	buf |= state;
	m_state = !buf;
}

void Player::PlayerState()
{
	if (m_itemPlayerCheck == true)
	{
		PlayerState(State::FRONT_ITEMGET);
	}
	else
	{
		PlayerDeleteState(State::FRONT_ITEMGET);
	}
	if (m_itemFunCheck == true)
	{
		PlayerState(State::FRONT_FUNGET);
	}
	else
	{
		PlayerDeleteState(State::FRONT_FUNGET);
	}

	if (m_itemPlayerBadCheck == true)
	{
		PlayerState(State::BACK_OUTCOURSE);
	}
	else
	{
		PlayerDeleteState(State::BACK_OUTCOURSE);
	}
	if (m_courseOut == true)
	{
		PlayerState(State::FRONT_OUTCOURSE);
	}
	else
	{
		PlayerDeleteState(State::FRONT_OUTCOURSE);
	}

	//前進(通常より速度は速い)
	if ((m_state & (FRONT_ITEMGET)) == State::FRONT_ITEMGET)
	{
		m_vec.z *= 2.0f;
	}
	//前進(通常より速度は遅い)
	if ((m_state & (FRONT_OUTCOURSE)) == State::FRONT_OUTCOURSE)
	{
		m_vec.z *= 0.13f;
	}
	//前進(通常より速度は遅い)
	if ((m_state & (FRONT_FUNGET)) == State::FRONT_FUNGET)
	{
		m_vec.z *= 0.5f;
	}
}

void Player::PlayerDirection()
{
}

void Player::PlayerCreate()
{
	Collision::Capsule capsulePlayer;

	ModelDate* modelDate = ModelDate::GetInstance();

	SetPosition(Vector3(-93.5f, 0, 1.5f));
	SceneSelect* sceneSelect = m_game->GetSceneSelect();
	if (sceneSelect->GetCharaSelect() == 1)
	{
		SetModel(modelDate->GetPlayer());
	}

	if (sceneSelect->GetCharaSelect() == 2)
	{
		SetModel(modelDate->GetCPU());
	}
//	SetModel(modelDate->GetPlayer());
	SetUpEffect();
	// カプセル型のコリジョンをつける
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//境界球の中心
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		    //境界球の中心
	capsulePlayer.r = 0.6f;							     	//半径
	SetCollision(capsulePlayer);
	Update(0);
}

void Player::PlayerItemGet(std::unique_ptr<Item> itemPlayer[2],
                           std::unique_ptr<Item> itemPlayerErase[2],
                           std::unique_ptr<Item> itemCPU[2],
                           std::unique_ptr<Item> itemCPUErase[2],
						   std::unique_ptr<Item> itemFun[2],
						   std::unique_ptr<Item> itemFunErase[2])
{
	//プレイヤーのアイテム取得
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		//プレイヤー用のアイテム取得
		if (Collision::HitCheck_Capsule2Capsule(itemPlayer[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerCheck = true;
			m_itemPlayerBadCheck = false;
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
			m_itemPlayerCheck = false;
		}
		//CPU用のアイテム効果切れ
		else if (Collision::HitCheck_Capsule2Capsule(itemCPUErase[i]->GetCollision(), GetCollision()))
		{
			m_itemPlayerBadCheck = false;
		}
		//フンアイテム取得
		if (Collision::HitCheck_Capsule2Capsule(itemFun[i]->GetCollision(), GetCollision()))
		{
			m_itemFunCheck = true;
		}
		//フンアイテム効果切れ
		else if (Collision::HitCheck_Capsule2Capsule(itemFunErase[i]->GetCollision(), GetCollision()))
		{
			m_itemFunCheck = false;
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
