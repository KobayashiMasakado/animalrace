#include "pch.h"
#include "Item.h"

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
Item::Item()
{
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
Item::~Item()
{
}
/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTIme"></param>
/// <returns></returns>
bool Item::Update(float elapsedTIme)
{
	//���[���h�s����쐬����
	m_world = Matrix::CreateFromQuaternion(m_rotation) * Matrix::CreateTranslation(m_position);

	return true;
}
/// <summary>
/// �`��
/// </summary>
void Item::Render()
{
	if (m_game && m_model)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(),
			*m_game->GetState(),
			m_world, m_game->GetView(),
			m_game->GetProjection());
		//�f�o�b�O�p�R���W�������f���̕`��
	//	DrawCollision();
	}
	
}

void Item::SetUpEffect()
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

//�A�C�e���쐬(�v���C���[)
void Item::ItemPlayerCreate(int item)
{
	Collision::Capsule capsule;
	capsule.r = 1.5f;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetItemPlayer());
	SetUpEffect();
	switch (item)
	{
	case 0:
		SetPosition(Vector3(-93.5f, 0, 40.0f));
		capsule.start = Vector3(0.5f, 0.5f, 0.5f);       //���E���̒��S
		capsule.end = Vector3(0.5f, 0.5f, 0.5f);		    //���E���̒��S

		break;
	case 1:
		SetPosition(Vector3(94.0f, 0, 10.0f));
		capsule.start = Vector3(1.0f, 1.0f, 1.0f);           //���E���̒��S
		capsule.end = Vector3(1.0f, 1.0f, 1.0f);		    //���E���̒��S

		break;
	}
	SetCollision(capsule);
}
//�A�C�e�����ʐ؂�(�v���C���[)
void Item::ItemPlayerEraseCreate(int item)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	capsule.r = 1.5f;                                    //���a
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		SetModel(modelDate->GetItemErasePlayer());
   
		switch (item)
		{
		case 0:
			SetPosition(Vector3(0.0f, 14, 95.0f));
			capsule.start = Vector3(0.5f, 0.5f, 7.0f);           //���E���̒��S
			capsule.end = Vector3(-0.5f, 0.5f, -7.0f);		    //���E���̒��S
			break;
		case 1:
			SetPosition(Vector3(30.0f, 0, -75.0f));
			capsule.start = Vector3(3.5f, 0.5f, 6.0f);           //���E���̒��S
			capsule.end = Vector3(-3.5f, 0.5f, -6.0f);		    //���E���̒��S
			break;
		}
		SetCollision(capsule);
	}
}
//�A�C�e���쐬(CPU)
void Item::ItemCPUCreate(int item)
{
	Collision::Capsule capsule;
	capsule.r = 1.5f;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetItemCPU());
	SetUpEffect();
	
	switch (item)
	{
	case 0:
		SetPosition(Vector3(-98.5f, 0, 40.0f));
		capsule.start = Vector3(0.5f, 0.5f, 0.5f);       //���E���̒��S
		capsule.end = Vector3(0.5f, 0.5f, 0.5f);		    //���E���̒��S
		break;
	case 1:
		SetPosition(Vector3(88.0f, 0, 10.0f));
		capsule.start = Vector3(1.0f, 1.0f, 1.0f);           //���E���̒��S
		capsule.end = Vector3(1.0f, 1.0f, 1.0f);		    //���E���̒��S
		break;
	}
	SetCollision(capsule);
	
}
//�A�C�e�����ʐ؂�(CPU)
void Item::ItemCPUEraseCreate(int item)
{
	Collision::Capsule capsule;
	ModelDate* modelDate = ModelDate::GetInstance();
	SetModel(modelDate->GetItemEraseCPU());

	capsule.r = 1.5f;                  //���a
	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
	{
		
		                                   
		switch (item)
		{
		case 0:
			SetPosition(Vector3(0.0f, 14, 95.0f));
			capsule.start = Vector3(0.5f, 0.5f, 15.0f);           //���E���̒��S
			capsule.end = Vector3(0.5f, 0.5f, -15.0f);		    //���E���̒��S
			break;
		case 1:
			SetPosition(Vector3(30.0f, 0, -75.0f));
			capsule.start = Vector3(3.5f, 0.5f, 5.0f);           //���E���̒��S
			capsule.end = Vector3(-3.5f, 0.5f, -5.0f);		    //���E���̒��S
			break;
		}
		SetCollision(capsule);
	}
}
