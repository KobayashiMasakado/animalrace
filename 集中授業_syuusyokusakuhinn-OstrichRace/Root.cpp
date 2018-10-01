#include "pch.h"
#include "Root.h"

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
Root::Root()
{
	m_hitPlayerFlag = false;
}
/// <summary>
/// デストラクタ
/// </summary>
Root::~Root()
{
}
/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTIme"></param>
/// <returns></returns>
bool Root::Update(float elapsedTIme)
{
	//ワールド行列を作成する
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// 描画
/// </summary>
void Root::Render()
{
	if (m_game && m_model)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//デバッグ用コリジョンモデルの描画
		DrawCollision();
	}
}

void Root::SetUpEffect()
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

//CPUの移動用の当たり判定
void Root::EnemyHitMoveCreate(int course)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	capsule.r = 5.0f;
	switch (course)
	{
	case 0:
		SetPosition(Vector3(-96.0f, 0.0f, 0.0f));
		capsule.start = Vector3(0.0f, 0.0f, 80.0f);
		capsule.end = Vector3(0.0f, 0.0f, -80.0f);
		break;
	case 1:
		SetPosition(Vector3(-85.0f, 0.0f, 87.0f));
		capsule.start = Vector3(7.0f, 0.0f, 7.0f);
		capsule.end = Vector3(-10.0f, 0.0f, -10.0f);
		capsule.r = 5.5f;
		break;
	case 2:
		SetPosition(Vector3(0.0f, 0.0f, 95.0f));
		capsule.start = Vector3(70.0f, 0.0f, 0.0f);
		capsule.end = Vector3(-75.0f, 0.0f, 0.0f);
		break;
	case 3:
		SetPosition(Vector3(84.0f, 0.0f, 85.0f));
		capsule.start = Vector3(5.0f, 0.0f, -5.0f);
		capsule.end = Vector3(-8.0f, 0.0f, 8.0f);
		capsule.r = 5.5f;
		break;
	case 4:
		SetPosition(Vector3(92.0f, 0.0f, 0.0f));
		capsule.start = Vector3(0.0f, 0.0f, 75.0f);
		capsule.end = Vector3(0.0f, 0.0f, -80.0f);
		break;
	case 5:
		SetPosition(Vector3(86.0f, 0.0f, -90.0f));
		capsule.start = Vector3(10.0f, 0.0f, 10.0f);
		capsule.end = Vector3(-8.0f, 0.0f, -8.0f);
		break;
	case 6:
		SetPosition(Vector3(70.0f, 0.0f, -100.0f));
		capsule.start = Vector3(10.0f, 0.0f, 0.0f);
		capsule.end = Vector3(-13.0f, 0.0f, 0.0f);
		break;
	case 7:
		SetPosition(Vector3(25.0f, 0.0f, -70.0f));
		capsule.start = Vector3(30.0f, 0.0f, -30.0f);
		capsule.end = Vector3(-25.0f, 0.0f, 25.0f);
		break;
	case 8:
		SetPosition(Vector3(-5.0f, 0.0f, -25.0f));
		capsule.start = Vector3(-0.0f, 0.0f, 3.0f);
		capsule.end = Vector3(0.0f, 0.0f, -15.0f);
		capsule.r = 5.5f;
		break;
	case 9:
		SetPosition(Vector3(17.0f, 0.0f, 7.0f));
		capsule.start = Vector3(18.0f, 0.0f, 18.0f);
		capsule.end = Vector3(-25.0f, 0.0f, -25.0f);
		break;
	case 10:
	    SetPosition(Vector3(40.0f, 0.0f, 33.0f));
		capsule.start = Vector3(0.0f, 0.0f, 5.0f);
		capsule.end = Vector3(-4.0f, 0.0f, -7.0f);
		break;
	case 11:
		SetPosition(Vector3(40.0f, 0.0f, 43.0f));
		capsule.start = Vector3(0.0f, 0.0f, 7.0f);
		capsule.end = Vector3(1.0f, 0.0f, -5.0f);
		break;
	case 12:
		SetPosition(Vector3(33.0f, 0.0f, 60.0f));
		capsule.start = Vector3(7.0f, 0.0f, -7.0f);
		capsule.end = Vector3(-7.0f, 0.0f, 7.0f);
		capsule.r = 5.5f;
		break;
	case 13:
		SetPosition(Vector3(0.0f, 0.0f, 70.0f));
		capsule.start = Vector3(20.0f, 0.0f, 0.0f);
		capsule.end = Vector3(-20.0f, 0.0f, 0.0f);
		break;
	case 14:
		SetPosition(Vector3(-30.0f, 0.0f, 65.0f));
		capsule.start = Vector3(5.0f, 0.0f, 5.0f);
		capsule.end = Vector3(-8.0f, 0.0f, -8.0f);
		break;
	case 15:
		SetPosition(Vector3(-40.0f, 0.0f, -10.0f));
		capsule.start = Vector3(0.0f, 0.0f, 70.0f);
		capsule.end = Vector3(0.0f, 0.0f, -68.0f);
		break;
	case 16:
		SetPosition(Vector3(-50.0f, 0.0f, -95.0f));
		capsule.start = Vector3(7.0f, 0.0f, 10.0f);
		capsule.end = Vector3(-10.0f, 0.0f, -5.0f);
		capsule.r = 5.5f;
		break;
	case 17:
		SetPosition(Vector3(-70.0f, 0.0f, -100.0f));
		capsule.start = Vector3(3.0f, 0.0f, 0.0f);
		capsule.end = Vector3(-3.0f, 0.0f, 0.0f);
		capsule.r = 6.5f;
		break;
	case 18:
		SetPosition(Vector3(-88.0f, 0.0f, -90.0f));
		capsule.start = Vector3(10.0f, 0.0f, -10.0f);
		capsule.end = Vector3(-7.0f, 0.0f, 7.0f);
		capsule.r = 5.5f;
		break;
	case 19:
		SetPosition(Vector3(-93.5f, 0, 9.0f));
		capsule.start = Vector3(0.5f, 0.5f, 0.5f);
		capsule.end = Vector3(0.5f, 0.5f, 0.5f);
		capsule.r = 3.5f;
		break;
	}

	SetCollision(capsule);

}
