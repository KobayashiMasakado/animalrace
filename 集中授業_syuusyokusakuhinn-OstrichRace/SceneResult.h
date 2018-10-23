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

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	// �f�o�b�O�J����
	std::unique_ptr<DebugCamera> m_debugCamera;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;


	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tResult1;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tResult2;



public:
	SceneResult();
	~SceneResult();

	//������
	void Initialize() override;
		//�X�V
	void Update(DX::StepTimer timer) override;
		//�`��;
	void Render() override;

	void CreateDeviceDependentResources();

		//�I������
	void Finalize() override;

	//Set�֐�
	//�Q�b�^�[�֐�
	//�f�o�C�X���擾����֐�
	ID3D11Device* GetDevice()
	{
		return m_deviceResources->GetD3DDevice();
	}

	//�R���e�L�X�g���擾����֐�
	ID3D11DeviceContext* GetContext()
	{
		return m_deviceResources->GetD3DDeviceContext();
	}
	//�R�����X�e�[�g���擾����֐�
	DirectX::CommonStates* GetState()
	{
		return m_states.get();
	}
	//�r���[�s����擾����֐�
	const DirectX::SimpleMath::Matrix& GetView()
	{
		return m_view;
	}
	//�ˉe�s����擾����֐�
	const DirectX::SimpleMath::Matrix& GetProjection()
	{
		return m_projection;
	}
	//Set�֐�
	void SetDeviceResources(DX::DeviceResources* deviceResources)
	{
		this->m_deviceResources = deviceResources;
	}
	void SetProjection(DirectX::SimpleMath::Matrix projection)
	{
		this->m_projection = projection;
	}
};