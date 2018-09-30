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
#include "Goal.h"

#include "ObjectCreate.h"

#include "Number.h"


class ScenePlay : public SceneBase
{

public:
	static const int ENEMY_HITCHECK_NUM = 19;
	static const int GOAL_SET_NUM = 6;
	static const int ITEM_SET_NUM = 2;
	static const int TIME_SET_NUM = 3;
	static const int TIME_TYPE_NUM = 10;
	static const int GAME_START_TIME = 180;
	static const int TIME_MINUTE = 60;
	static const int TIME_MIRI = 100;
	static const int GROUND_POSY = -0.3f;
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

	ObjectCreate* m_objCreate;

	//�v���C���[
	Player* m_player;
	//std::unique_ptr<DirectX::Model> m_itemPlayerModel;
	//CPU
	Enemy* m_cpu;
//	std::unique_ptr<DirectX::Model> m_itemCPUModel;

	std::unique_ptr<CollisionCapsule> m_box[ENEMY_HITCHECK_NUM];
	std::unique_ptr<DirectX::Model> m_boxModel[ENEMY_HITCHECK_NUM];

	//Root* m_root;
	//���̃��f��
	std::unique_ptr<DirectX::Model> m_rootModel;
	//�S�[��
	std::unique_ptr<Goal> m_goal[GOAL_SET_NUM];
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
	std::unique_ptr<Item> m_itemPlayerErase[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemPlayerEraseModel;
	//CPU�p
	std::unique_ptr<Item> m_itemCPUErase[ITEM_SET_NUM];
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
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[TIME_TYPE_NUM];

	Number m_number[TIME_SET_NUM];

	//�^�C��
	int m_time;
	int m_timeS;
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
	int m_count;
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

	void Finalize() override { delete m_objCreate; }
	void CreateDeviceDependentResources();

	//�v���C���[����
	void PlayerOperation(DirectX::Keyboard::State &kb);

	//�v���C���[����(�R�[�X�O)
	void PlayerOperationwOutSide(DirectX::Keyboard::State &kb);

	//�R�[�X�ƃL�����̓����蔻��
	void HitCourseCheck();

	//�S�[���ƃL�����̓����蔻��
	void HitGoalCheck();

	//�A�C�e���擾
	//�v���C���[�p
	void PlayerItemGet();
	//CPU�p
	void CPUItemGet();

	//�J�E���g�_�E��
	void CountDownStart();

	//���[�X����
	void RaceEnd();

	//�Q�[����Set
	void SetGame2();

	//CPU�̊p�x��ς���
	void EnemyDirection();;

	
	//�A�C�e���쐬(CPU)
	void ItemCPUCreate();
	//�A�C�e�����ʐ؂�(CPU)
	void ItemCPUEraseCreate();
	//�R�[�X�쐬
	void CourseCreate();
	//�S�[���쐬
	void GoalCreate();
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