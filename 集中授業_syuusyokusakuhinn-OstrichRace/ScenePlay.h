#pragma once

#include "SceneBase.h"

#include "Obj3D.h"
#include "CollisionCapsule.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Root.h" 
#include "DebugCamera.h"
#include "GameCamera.h"
#include "TaskManager.h"
#include "CollisionMesh.h"


#include "Number.h"


class ScenePlay : public SceneBase
{

private:
	static const int ENEMY_HITCHECK_NUM = 19;
	static const int GOAL_SET_NUM = 6;
	static const int ITEM_SET_NUM = 2;
	static const int TIME_SET_NUM = 3;
private:

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

	// �Q�[���J����
	std::unique_ptr<GameCamera> m_gameCamera;

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//// �X�v���C�g�o�b�`
	//std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	//3D�X�v���C�g///////////////////////////////////////////
	//��
	std::unique_ptr<DirectX::Model> m_skydome;

	// ����
	std::unique_ptr<DirectX::Model> m_prairie;

	//�v���C���[
//	std::unique_ptr<Player> m_player;
	Player* m_player;
	//�v���C���[�̃��f��
	std::unique_ptr<DirectX::Model> m_playerModel;

	//CPU
	std::unique_ptr<Enemy> m_cpu;
	//CPU�̃��f��
	std::unique_ptr<DirectX::Model> m_cpuModel;

	std::unique_ptr<CollisionCapsule> m_box[ENEMY_HITCHECK_NUM];
	std::unique_ptr<DirectX::Model> m_boxModel[ENEMY_HITCHECK_NUM];
	//��
	//std::unique_ptr<Root> m_root;
	Obj3D* m_root;
	//���̃��f��
	std::unique_ptr<DirectX::Model> m_rootModel;
	//�S�[��
	std::unique_ptr<CollisionCapsule> m_goal[GOAL_SET_NUM];
	std::unique_ptr<DirectX::Model> m_goalModel;
	//�A�C�e��
	//�v���C���[�p
	std::unique_ptr<Item> m_itemPlayer[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemPlayerModel;
	//CPU�p
	std::unique_ptr<Item> m_itemCPU[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemCPUModel;
	//�A�C�e������
	//�v���C���[�p
	std::unique_ptr<CollisionCapsule> m_itemPlayerErase[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemPlayerEraseModel;
	//CPU�p
	std::unique_ptr<CollisionCapsule> m_itemCPUErase[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemCPUEraseModel;
	//2D�X�v���C�g/////////////////////////////
	//�e�N�X�`���n���h��
	//��������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTime;
	//����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLap;
	//�X�s�[�h���[�^�[
	//�L����
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tHO;
	//�L�����[�g��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tKm;
	//GOAL!!
	//�v���C���[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUGoal;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tFlipGoal;;
	//�J�E���g�_�E��
	//GO!
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCGo;
	//����
	//0
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCZero;
//	ID3D11ShaderResourceView* m_tCZero;
	//1
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCOne;
	//2
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCTwo;
	//3
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCThree;
	//4
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCFour;
	//5
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCFive;
	//6
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCSix;
	//7
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCSeven;
	//8
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCEight;
	//9
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNine;

	Number m_number[TIME_SET_NUM];

	//�^�C��
	float m_time;
	float m_timeS;
	//�Փ˂������ǂ�������
	bool m_hitPlayerFlag;
	bool m_hitCpuFlag;

	//�S�[���ɒH�蒅�������ǂ�������
	bool m_goalPlayerFlag[GOAL_SET_NUM];
	bool m_goalCPUFlag[GOAL_SET_NUM];
	
	//�A�C�e���擾
	bool m_itemPlayerCheck;
	bool m_itemCPUCheck;

	bool m_itemPlayerBadCheck;
	bool m_itemCPUBadCheck;

	//�J�E���g�_�E��
	float m_count;
	//�A�C�e��
	//int m_itemCount;
	
	//�S�[���̃`�F�b�N�|�C���g
	int m_checkPoint;

	//�^�X�N�}�l�[�W���[
	TaskManager m_taskManager;

	std::unique_ptr<CollisionMesh> m_floorMesh;

	
public:
	//������
	void Initialize() override;
	//�X�V
	void Update(float elapsedTime) override;
	//�`��
	void Render() override;

	void Finalize() override {}
	void CreateDeviceDependentResources();

	//CPU�̊p�x��ς���
	void EnemyDirection();
	//�v���C���[�쐬
	void PlayerCreate(Collision::Capsule capsulePlayer);
	//CPU�쐬
	void CPUCreate(Collision::Capsule capsuleCPU);
	//�A�C�e���쐬(�v���C���[)
	void ItemPlayerCreate(Collision::Capsule capsuleItemPlayer[ITEM_SET_NUM]);
	//�A�C�e�����ʐ؂�(�v���C���[)
	void ItemPlayerEraseCreate(Collision::Capsule capsuleItemPlayerErase[ITEM_SET_NUM]);
	//�A�C�e���쐬(CPU)
	void ItemCPUCreate(Collision::Capsule capsuleItemCPU[ITEM_SET_NUM]);
	//�A�C�e�����ʐ؂�(CPU)
	void ItemCPUEraseCreate(Collision::Capsule capsuleItemCPUErase[ITEM_SET_NUM]);
	//�R�[�X�쐬
	void CourseCreate();
	//�S�[���쐬
	void GoalCreate(Collision::Capsule capsuleGoal[GOAL_SET_NUM]);
	//CPU�̈ړ��p�̓����蔻��
	void EnemyHitMoveCreate();


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