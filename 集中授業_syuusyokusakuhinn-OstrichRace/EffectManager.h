#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include "MyEffect.h"

#include <list>

class EffectManager
{
public:
	void Create(DX::DeviceResources* deviceResources, const wchar_t* name,int count);
	void Initialize(float life,DirectX::SimpleMath::Vector3 pos);
	void InitializeNormal(float life, DirectX::SimpleMath::Vector3 pos);
	void InitializeCorn(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir);
	void Update(DX::StepTimer timer);
	void Render();
	void Lost();

	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	
private:
	//MyEffect*					m_myEffect[10];
	std::list<MyEffect*>		m_effectList;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
};