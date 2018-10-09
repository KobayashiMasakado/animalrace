#pragma once

#include "SceneBase.h"

#include "DeviceResources.h"
#include "DebugCamera.h"
#include "Player.h"

class SceneSelect : public SceneBase
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

	int m_x;
	int m_y;

	int m_flag;

	//�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelect1;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelect2;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tSelectPointer;

	//�v���C���[
	Player* m_player;
public:
	SceneSelect();
	~SceneSelect();

	//������
	void Initialize() override;
	//�X�V
	void Update(DX::StepTimer timer) override;
	//�`��
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