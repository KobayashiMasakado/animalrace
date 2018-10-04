//----------------------------------------
// MyEffect.h
//----------------------------------------
#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include <vector>

class MyEffect 
{
public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
	};
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;
	void Create(DX::DeviceResources* deviceResources, ID3D11ShaderResourceView* texture);
	
	void Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity);
	void Update(DX::StepTimer timer);
	void Render();

	void SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);
	
private:

	void Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	DX::StepTimer                           m_timer;
	DX::DeviceResources*			m_deviceResources;
	DirectX::SimpleMath::Matrix m_world;
	DirectX::SimpleMath::Matrix m_view;
	DirectX::SimpleMath::Matrix m_proj;
	//// �G�t�F�N�g
	//std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;
	// �v���~�e�B�u�o�b�`
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	std::unique_ptr<DirectX::CommonStates> m_states;
	// �e�N�X�`���n���h��
	ID3D11ShaderResourceView* m_texture;

	DirectX::SimpleMath::Vector3		m_camera;

	DirectX::SimpleMath::Vector3		m_gravity;
	DirectX::SimpleMath::Vector3		m_position;
	DirectX::SimpleMath::Vector3		m_velocity;
	float								m_life;

	DirectX::SimpleMath::Vector3		m_startPosition;
	DirectX::SimpleMath::Vector3		m_startVelocity;
	float								m_startLife;

	// ���_�V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_VertexShader;
	// �s�N�Z���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_PixelShader;
	// �W�I���g���V�F�[�_
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_GeometryShader;


	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

};