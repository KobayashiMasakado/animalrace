#include "pch.h"
#include "SceneResult.h"
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

SceneResult::SceneResult()
{
}

SceneResult::~SceneResult()
{
}

void SceneResult::Initialize()
{
}

void SceneResult::Update(DX::StepTimer timer)
{
}

void SceneResult::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_sprites->Draw(m_tResult1.Get(), Vector2(300, 250));
	m_sprites->Draw(m_tResult2.Get(), Vector2(300, 50));
	m_sprites->End();
}

void SceneResult::CreateDeviceDependentResources()
{
	//スプライトバッチの作成
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);

	CreateWICTextureFromFile(device, L"Textures\\Datyou.png", nullptr, m_tResult1.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouWin.png", nullptr, m_tResult2.GetAddressOf());


}

void SceneResult::Finalize()
{
}
