#include "pch.h"
#include "Item.h"
#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"

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
		DrawCollision();
	}
}