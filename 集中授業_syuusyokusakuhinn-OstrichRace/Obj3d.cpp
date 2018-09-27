#include "pch.h"
#include "Obj3D.h"
#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


Obj3D::Obj3D()
	:
	m_game(nullptr),
	m_model(nullptr)
{
}

bool Obj3D::Update(float elapsedTime)
{
	//ワールド行列を作成
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}

void Obj3D::Render()
{
	if (m_model && m_game)
	{
		//モデルの描画
		m_model->Draw(m_game->GetContext(), *m_game->GetState(),
			m_world, m_game->GetView(), m_game->GetProjection());
	}
}

