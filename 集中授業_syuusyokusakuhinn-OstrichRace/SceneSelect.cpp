#include "pch.h"
#include "SceneSelect.h"
#include <iostream>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

SceneSelect::SceneSelect()
{
}

SceneSelect::~SceneSelect()
{
}

void SceneSelect::Initialize()
{
	m_x = 0;
	m_y = 100;
	m_flag = 0;
}

void SceneSelect::Update(DX::StepTimer timer)
{
	// �L�[�{�[�h�̏�Ԃ��擾����
	Keyboard::State kb = Keyboard::Get().GetState();
	if (kb.Up)
	{
		m_y -= 50;
	}

	if (kb.Down)
	{
		m_y += 50;
	}

	/*if (m_y < 50)
	{
		m_y = 50;
	}

	if (m_y > 150)
	{
		m_y = 150;
	}*/
}

void SceneSelect::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	//2D�X�v���C�g�̕`��
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_sprites->Draw(m_tSelect1.Get(), Vector2(0, 0));
	m_sprites->Draw(m_tSelect2.Get(), Vector2(0, 300));
	m_sprites->Draw(m_tSelectPointer.Get(), Vector2(m_x, m_y));
	m_sprites->End();
}

void SceneSelect::CreateDeviceDependentResources()
{
	//�X�v���C�g�o�b�`�̍쐬
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();
	
	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);

	// �X�v���C�g�o�b�`�̍쐬
	m_sprites = std::make_unique<SpriteBatch>(context);
	
	CreateWICTextureFromFile(device, L"Textures\\Datyou.png", nullptr, m_tSelect1.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Tiger.png", nullptr, m_tSelect2.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Pointer.png", nullptr, m_tSelectPointer.GetAddressOf());
	
}

void SceneSelect::Finalize()
{

}

