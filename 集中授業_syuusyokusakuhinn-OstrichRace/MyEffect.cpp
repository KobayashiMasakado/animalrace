//----------------------------------------
// MyEffect.cpp
//----------------------------------------

#include "pch.h"
#include "Myeffect.h"

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "BinaryFile.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const std::vector<D3D11_INPUT_ELEMENT_DESC> MyEffect::INPUT_LAYOUT =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};
void MyEffect::Create(DX::DeviceResources* deviceResources, ID3D11ShaderResourceView* texture)
{
	m_deviceResources = deviceResources;
	auto device = m_deviceResources->GetD3DDevice();

	// コンパイルされたシェーダファイルを読み込み
	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");

	device->CreateInputLayout(&INPUT_LAYOUT[0],
		INPUT_LAYOUT.size(),
		VSData.GetData(), VSData.GetSize(),
		m_inputLayout.GetAddressOf());
	// 頂点シェーダ作成
	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_VertexShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
		return;
	}
	// ジオメトリシェーダ作成
	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_GeometryShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
		return;
	}
	// ピクセルシェーダ作成
	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_PixelShader.ReleaseAndGetAddressOf())))
	{// エラー
		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
		return;
	}
	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(m_deviceResources->GetD3DDeviceContext());

	m_states = std::make_unique<CommonStates>(device);
	// テクスチャのロード
	//CreateWICTextureFromFile(device, L"Resources\\Textures\\image01.png", nullptr, m_texture.GetAddressOf());
	m_texture = texture;


	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_CBuffer);

	m_world = Matrix::Identity;

}
void MyEffect::Initialize(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 velocity)
{
	m_startPosition = m_position = pos;
	m_startVelocity = m_velocity = velocity;
	m_startLife = m_life = life;
	m_gravity = Vector3(0, 0.001f, 0);
}

void MyEffect::Update(DX::StepTimer timer)
{
	float time = float(m_timer.GetElapsedSeconds());
	m_timer = timer;
	if (m_startVelocity.Length() > 0.02f) {
		m_velocity -= m_gravity;
	}
	m_position += m_velocity;

	m_life -= time*m_position.Length();
	if ((m_position-m_startPosition).Length() > 10)
	{
		m_life = m_startLife;
		m_position = m_startPosition;
		m_velocity = m_startVelocity;
	}
	if (m_life < 0)
	{
		m_life = m_startLife;
		m_position = m_startPosition;
		m_velocity = m_startVelocity;
	}
}

void MyEffect::Render()
{

	m_world = Matrix::CreateBillboard(m_position, m_camera, Vector3::UnitY);
	Draw(m_world, m_view, m_proj);

}

void MyEffect::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	m_camera = camera;
	m_view = view;
	m_proj = proj;
}

void MyEffect::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	// 頂点情報（ここは自分で設定してください。）
	VertexPositionColorTexture vertex[4] =
	{
		VertexPositionColorTexture(Vector3(0.5f, 0.5f, 0.0f),Vector4::One, Vector2(0.0f, 0.0f)),
		VertexPositionColorTexture(Vector3(-0.5f, 0.5f, 0.0f),Vector4::One, Vector2(1.0f, 0.0f)),
		VertexPositionColorTexture(Vector3(-0.5f, -0.5f, 0.0f),Vector4::One, Vector2(1.0f, 1.0f)),
		VertexPositionColorTexture(Vector3(0.5f,-0.5f, 0.0f),Vector4::One, Vector2(0.0f, 1.0f)),
	};


	ConstBuffer cbuff;

	cbuff.matView = view.Transpose();
	cbuff.matProj = proj.Transpose();
	cbuff.matWorld = world.Transpose();
	cbuff.Diffuse = Vector4(1, 1, 1, 1);

	//定数バッファの内容更新
	context->UpdateSubresource(m_CBuffer.Get(), 0, NULL, &cbuff, 0, 0);



	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);
	// カリングは左周り
	context->RSSetState(m_states->CullNone());

	ID3D11Buffer* cb[1] = { m_CBuffer.Get() };
	context->VSSetConstantBuffers(0, 1, cb);
	context->GSSetConstantBuffers(0, 1, cb);
	context->PSSetConstantBuffers(0, 1, cb);


	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	context->PSSetSamplers(0, 1, sampler);

	context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
	context->PSSetShaderResources(0, 1, &m_texture);
	//context->PSSetShaderResources(1, 1, m_texture2.GetAddressOf());


	context->IASetInputLayout(m_inputLayout.Get());

	// 半透明部分を描画
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();






}