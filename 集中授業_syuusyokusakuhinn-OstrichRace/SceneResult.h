#pragma once

#include "SceneBase.h"

#include "DeviceResources.h"
#include "DebugCamera.h"

class SceneResult : public SceneBase
{
private:
	DX::StepTimer                           m_timer;

	// Device resources.
	DX::DeviceResources* m_deviceResources;

	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;

	// 射影行列
	DirectX::SimpleMath::Matrix m_projection;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tResult1;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tResult2;



public:
	SceneResult();
	~SceneResult();

	//初期化
	void Initialize() override;
		//更新
	void Update(DX::StepTimer timer) override;
		//描画;
	void Render() override;

	void CreateDeviceDependentResources();

		//終了処理
	void Finalize() override;

	//Set関数
	//ゲッター関数
	//デバイスを取得する関数
	ID3D11Device* GetDevice()
	{
		return m_deviceResources->GetD3DDevice();
	}

	//コンテキストを取得する関数
	ID3D11DeviceContext* GetContext()
	{
		return m_deviceResources->GetD3DDeviceContext();
	}
	//コモンステートを取得する関数
	DirectX::CommonStates* GetState()
	{
		return m_states.get();
	}
	//ビュー行列を取得する関数
	const DirectX::SimpleMath::Matrix& GetView()
	{
		return m_view;
	}
	//射影行列を取得する関数
	const DirectX::SimpleMath::Matrix& GetProjection()
	{
		return m_projection;
	}
	//Set関数
	void SetDeviceResources(DX::DeviceResources* deviceResources)
	{
		this->m_deviceResources = deviceResources;
	}
	void SetProjection(DirectX::SimpleMath::Matrix projection)
	{
		this->m_projection = projection;
	}
};