#include "pch.h"
#include "Goal.h"

#include <Effects.h> 
#include <PrimitiveBatch.h>
#include <VertexTypes.h> 
#include <SimpleMath.h>
#include "Game.h"

#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Goal::Goal()
{
}

Goal::~Goal()
{
}

bool Goal::Update(float elapsedTIme)
{
	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}

void Goal::Render()
{
	if (m_game && m_model)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//�f�o�b�O�p�R���W�������f���̕`��
		DrawCollision();
	}
}

void Goal::SetUpEffect()
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

//�S�[���쐬
void Goal::GoalCreate(int goal)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetGoal());
	capsule.r = 0.6f;
	// �J�v�Z���^�̃R���W����������
	switch (goal)
	{
	case 0:
		SetPosition(Vector3(-96.0f, 0, 5.0f));
		capsule.start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 1:
		SetPosition(Vector3(0, 10, 95.0f));
		capsule.start = Vector3(0.0f, 0.0f, 5.5f);           //���E���̒��S
		capsule.end = Vector3(0.0f, 0.0f, -5.5f);		    //���E���̒��S
		break;
	case 2:
		SetPosition(Vector3(93.0f, 0, 0.0f));
		capsule.start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 3:
		SetPosition(Vector3(10.0f, 0, 0));
		capsule.start = Vector3(6.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end = Vector3(-6.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 4:
		SetPosition(Vector3(-40.0f, 10, 0));
		capsule.start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	case 5:
		SetPosition(Vector3(-96.0f, 0, -3.0f));
		capsule.start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
		capsule.end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
		break;
	}

	SetCollision(capsule);
	
}

