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
	//ItemPlayerEraseCreate();
	//ItemCPUEraseCreate();
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
////�A�C�e�����ʐ؂�(�v���C���[)
//void Item::ItemPlayerEraseCreate()
//{
//	Collision::Capsule capsuleItemPlayerErase[ScenePlay::ITEM_SET_NUM];
//
//	ModelDate* modelDate = ModelDate::GetInstance();
//
//	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
//	{
//		SetModel(modelDate->GetItemErasePlayer());
//      SetUpEffect();
//		capsuleItemPlayerErase[i].r = 1.5f;                                    //���a
//		switch (i)
//		{
//		case 0:
//			SetPosition(Vector3(0.0f, 14, 95.0f));
//			capsuleItemPlayerErase[0].start = Vector3(0.5f, 0.5f, 5.0f);           //���E���̒��S
//			capsuleItemPlayerErase[0].end = Vector3(0.5f, 0.5f, -5.0f);		    //���E���̒��S
//			break;
//		case 1:
//			SetPosition(Vector3(30.0f, 0, -75.0f));
//			capsuleItemPlayerErase[1].start = Vector3(3.5f, 0.5f, 5.0f);           //���E���̒��S
//			capsuleItemPlayerErase[1].end = Vector3(-3.5f, 0.5f, -5.0f);		    //���E���̒��S
//			break;
//		}
//		SetCollision(capsuleItemPlayerErase[i]);
//	}
//}
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
////�A�C�e�����ʐ؂�(CPU)
//void Item::ItemCPUEraseCreate()
//{
//	Collision::Capsule capsuleItemCPUErase[ScenePlay::ITEM_SET_NUM];
//
//	ModelDate* modelDate = ModelDate::GetInstance();
//
//	for (int i = 0; i < ScenePlay::ITEM_SET_NUM; i++)
//	{
//		SetModel(modelDate->GetItemEraseCPU());
//      SetUpEffect();
//		capsuleItemCPUErase[i].r = 1.5f;                                    //���a
//		switch (i)
//		{
//		case 0:
//			SetPosition(Vector3(0.0f, 14, 95.0f));
//			capsuleItemCPUErase[0].start = Vector3(0.5f, 0.5f, 5.0f);           //���E���̒��S
//			capsuleItemCPUErase[0].end = Vector3(0.5f, 0.5f, -5.0f);		    //���E���̒��S
//			break;
//		case 1:
//			SetPosition(Vector3(30.0f, 0, -75.0f));
//			capsuleItemCPUErase[1].start = Vector3(3.5f, 0.5f, 5.0f);           //���E���̒��S
//			capsuleItemCPUErase[1].end = Vector3(-3.5f, 0.5f, -5.0f);		    //���E���̒��S
//			break;
//		}
//		SetCollision(capsuleItemCPUErase[i]);
//	}
//}
