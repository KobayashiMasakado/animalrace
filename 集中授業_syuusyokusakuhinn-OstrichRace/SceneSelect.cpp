#include "pch.h"
#include "SceneSelect.h"
#include <iostream>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"
#include "Game.h"

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
	m_charaSerect = 1;
	m_y = CURSOR_MIX;
}

void SceneSelect::Update(DX::StepTimer timer)
{
	// キーボードの状態を取得する
	Keyboard::State kb = Keyboard::Get().GetState();

	Keyboard::KeyboardStateTracker stateTriger;

	stateTriger.Update(kb);
	
	if (stateTriger.pressed.Up)
	{
		m_y -= CURSOR_MOVE;
		m_charaSerect = 1;
		ModelDate* modelDate = ModelDate::GetInstance();

		ScenePlay* scenePlay = m_game->GetScenePlay();
		Player* player = scenePlay->GetPlayer();
		player->SetModel(modelDate->GetPlayer());
	}

	if (stateTriger.pressed.Down)
	{
		m_y += CURSOR_MOVE;
		m_charaSerect = 2;
		ModelDate* modelDate = ModelDate::GetInstance();
		ScenePlay* scenePlay = m_game->GetScenePlay();
		Player* player = scenePlay->GetPlayer();
		player->SetModel(modelDate->GetCPU());
	}

	if (m_y < CURSOR_MIX)
	{
		m_y = CURSOR_MIX;
	}

	if (m_y > CURSOR_MAX)
	{
		m_y = CURSOR_MAX;
	}
}

void SceneSelect::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_sprites->Draw(m_tSelect1.Get(), Vector2(0, 50));
	m_sprites->Draw(m_tSelect2.Get(), Vector2(0, 300));
	m_sprites->Draw(m_tSelectPointer.Get(), Vector2(m_x, m_y));
	m_sprites->End();
}

void SceneSelect::CreateDeviceDependentResources()
{
	//スプライトバッチの作成
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();
	
	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);
	
	CreateWICTextureFromFile(device, L"Textures\\Datyou.png", nullptr, m_tSelect1.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Tiger.png", nullptr, m_tSelect2.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\kakko.png", nullptr, m_tSelectPointer.GetAddressOf());
	
}

void SceneSelect::Finalize()
{

}

