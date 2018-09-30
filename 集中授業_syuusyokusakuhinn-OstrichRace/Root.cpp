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
/// �R���X�g���N�^
/// </summary>
Root::Root()
{
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Root::~Root()
{
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTIme"></param>
/// <returns></returns>
bool Root::Update(float elapsedTIme)
{
	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// �`��
/// </summary>
void Root::Render()
{
	CourseCreate();
	if (m_game && m_model)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//�f�o�b�O�p�R���W�������f���̕`��
		//DrawCollision();
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

void Root::CourseCreate()
{
	ModelDate* modelDate = ModelDate::GetInstance();

	//���̍쐬												      
	SetGame(m_game);
	SetModel(modelDate->GetRoot());
}
