#include "pch.h"
#include "Goal.h"

#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"

#include "ModelDate.h"
Goal::Goal()
{
}

Goal::~Goal()
{
}

bool Goal::Update(float elapsedTIme)
{
	////���[���h�s����쐬����
	//m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}

void Goal::Render()
{
	//if (m_game && m_model)
	//{
	//	//���f���̕`��
	//	m_model->Draw(m_game->GetContext(),
	//		*m_game->GetState(),
	//		m_world, m_game->GetView(),
	//		m_game->GetProjection());
	//	//�f�o�b�O�p�R���W�������f���̕`��
	//	//DrawCollision();
	//}
}

void Goal::SetUpEffect()
{
	/*m_model->UpdateEffects([&](IEffect* effect)
	{
		auto lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetPerPixelLighting(true);
		}
	});*/
}

