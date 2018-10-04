#include "pch.h"
#include "EffectManager.h"
#include <WICTextureLoader.h>

using namespace DirectX::SimpleMath;

void EffectManager::Create(DX::DeviceResources * deviceResources, const wchar_t* name,int count)
{
	//const wchar_t* name = L"Resources\\Textures\\image01.png";
	DirectX::CreateWICTextureFromFile(deviceResources->	GetD3DDevice(), name , nullptr, m_texture.GetAddressOf());

	for (int i = 0; i < count; i++) {
		MyEffect* effect = new MyEffect();
		effect->Create(deviceResources,m_texture.Get());
		//effect->Initialize(3, Vector3(0, 0, 0), Vector3((rand() % 20)*0.01f, (rand() % 20)*0.01f, 0));
		m_effectList.push_back(effect);
	}
}

void EffectManager::Lost() {
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		delete (*itr);
	}
}
void EffectManager::Initialize(float life, DirectX::SimpleMath::Vector3 pos)
{
	int range = 100;
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		Vector3 vel = Vector3(((rand() % (range * 2)) - range)*0.1f / range, ((rand() % (range * 2)) - range)*0.1f / range, 0);
		while (vel.Length() < 0.0001f) 
		{
			vel = Vector3(((rand() % (range * 2)) - range)*0.1f / range, ((rand() % (range * 2)) - range)*0.1f / range, 0);
		}
		(*itr)->Initialize(life,pos,vel);
	}
}
void EffectManager::InitializeNormal(float life, DirectX::SimpleMath::Vector3 pos)
{
	int range = 1000;
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		Vector3 vel = Vector3(((rand() % (range * 2)) - range)*0.1f / range, ((rand() % (range * 2)) - range)*0.1f / range, 0);
		vel.Normalize();
		vel *= 0.1f;
		(*itr)->Initialize(life, pos, vel);
	}
}
void EffectManager::InitializeCorn(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir)
{
	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		Vector3 vel = dir;
		vel.Normalize();

		vel *= sin(rand()) + 1.0f;
		Vector3 raff = Vector3(vel.y, vel.x, 0);
		raff *= sin(rand())*0.5f;
		vel = vel + raff;

		vel *= 0.5f;
	
		(*itr)->Initialize(life, pos, (vel));
	}
}

void EffectManager::Update(DX::StepTimer timer)
{
	for(std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end();itr++)
	{
		(*itr)->Update(timer);
	}
}

void EffectManager::Render()
{

	for (auto itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		(*itr)->Render();
	}
}

void EffectManager::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{

	for (auto itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
	{
		(*itr)->SetRenderState(camera, view, proj);
	}
}
