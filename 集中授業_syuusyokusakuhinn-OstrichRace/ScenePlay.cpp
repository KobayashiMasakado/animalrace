#include "pch.h"
#include "ScenePlay.h"

#include <time.h>

using namespace DirectX;
using namespace DirectX::SimpleMath;

void ScenePlay::Initialize()
{
	//�S�[���t���O�̏�����
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goalPlayerFlag[i] = false;
		m_goalCPUFlag[i] = false;
	}
	m_itemPlayerCheck = false;
	m_itemCPUCheck = false;
	m_itemPlayerBadCheck = false;
	m_itemCPUBadCheck = false;
	//�J�E���g�_�E���̏�����
	m_count = 0.0f;

	m_checkPoint = 0;
	
	m_time = 0.0f;
	m_timeS = 0.0f;

	m_debugCamera = std::make_unique<DebugCamera>(800, 600);
//	m_gameCamera = std::make_unique<GameCamera>();
}

void ScenePlay::Update(float elapsedTime)
{
	// �f�o�b�O�J�����̍X�V
	m_debugCamera->Update();

	// �L�[�{�[�h�̏�Ԃ��擾����
	Keyboard::State kb = Keyboard::Get().GetState();

    //�J�E���g�_�E���i�����̓J�E���g�A�b�v�j
	m_count += 1.0f;
	
	///�X�V/////////////////////
	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);
	//CPU�̍X�V
	m_cpu->Update(elapsedTime);
	//�A�C�e���̍X�V
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i]->Update(elapsedTime);
		m_itemPlayerErase[i]->Update(elapsedTime);
		m_itemCPU[i]->Update(elapsedTime);
		m_itemCPUErase[i]->Update(elapsedTime);
	}

	//�S�[���̍X�V
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Update(elapsedTime);
	}
	//�R�[�X�̓����蔻��̍X�V
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i]->Update(elapsedTime);
	}
	
	///////////////////////////////
	//�����蔻��t���O������������
	m_hitPlayerFlag = false;
	m_hitCpuFlag = false;
	///�����蔻��////////////
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		if (Collision::HitCheck_Capsule2Capsule(m_box[i]->GetCollision()
			, m_player->GetCollision()) == true)
		{
			m_hitPlayerFlag = true;
		}
	}
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		if (Collision::HitCheck_Capsule2Capsule(m_box[i]->GetCollision()
			, m_cpu->GetCollision()) == true)
		{
			m_hitCpuFlag = true;
		}
	}
	//�S�[���ƃL�����̓����蔻��////////////////////////////////////
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		//�S�[���ƃv���C���[�̓����蔻�������
		if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
			, m_player->GetCollision()) == true)
		{
			if (m_checkPoint == i)
			{
				m_goalPlayerFlag[i] = true;
				m_checkPoint = i+1;
			}
		}
		//�S�[����CPU�̓����蔻�������
		if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
			, m_cpu->GetCollision()) == true)
		{
			m_goalCPUFlag[i] = true;
		}
	}
	/////////
	//�J�E���g�_�E�����I�������
	if (m_count > 180)
	{
		m_time += 1.0f;
		m_timeS += 1.0f;
		//�v���C���[�̈ړ�
		for (int i = 0; i < GOAL_SET_NUM; i++)
		{
			if (m_goalCPUFlag[i] == true)
			{
				m_player->PlayerMove(Player::NONE);
			}
			else if (m_hitPlayerFlag == true)
			{
				//�v���C���[����
				PlayerOperation(kb);
			}
			else if (m_hitPlayerFlag == false)
			{
				//�v���C���[����(�R�[�X�O)
				PlayerOperationwOutSide(kb);
				
			}
			//�A�C�e���擾
			PlayerItemGet();

			//�S�[��������
			if (m_goalPlayerFlag[i] == true)
			{
				m_cpu->EnemyChangeAngle(Enemy::NONE);
			}
			//�S�[�����ĂȂ��Ȃ�
			else if (m_hitCpuFlag == true)
			{
				//CPU�̕�����ς��Ĉړ�������
				EnemyDirection();
			}
			//������
			else if (m_hitCpuFlag == false)
			{
				m_cpu->EnemyChangeAngle(Enemy::BACK);
			}
			//CPU�A�C�e���擾
			CPUItemGet();
			////CPU�A�C�e���擾
			//if (Collision::HitCheck_Capsule2Capsule(m_itemCPU[0]->GetCollision(), m_cpu->GetCollision()) == true ||
			//	Collision::HitCheck_Capsule2Capsule(m_itemCPU[1]->GetCollision(), m_cpu->GetCollision()) == true)
			//{
			//	m_itemCPUCheck = true;
			//}

			//if (Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[0]->GetCollision(), m_cpu->GetCollision()) == true ||
			//	Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[1]->GetCollision(), m_cpu->GetCollision()) == true)
			//{
			//	m_itemCPUCheck = false;
			//}
		}
	}
	//�v���C���[�ƃR�[�X�̓����蔻��
	static int id;
	Vector3 s;
	Vector3 playerPos = m_player->GetPlayer();
	Vector3 v[2] = { Vector3(playerPos.x,100,playerPos.z),Vector3(playerPos.x,-1,playerPos.z) };
	if (m_floorMesh->HitCheck_Segment(v[0], v[1], &id, &s))
	{
		s.y -= 0.1f;
		m_player->SetPosition(s);
	}
	//�d��
	if (m_player->GetPlayer().y >= -0.3f)
	{
		m_player->PlayerMove(Player::GRAVITY);
	}
}

void ScenePlay::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	//�Ǐ]�J����
	// �r���[�s��̍쐬
	//Vector3 cameraPos = Vector3(0.0f, 10.0f, -20.0f); //�J�����̌Œ肷��ʒu
	//Vector3 target;

	//Matrix rotY = Matrix::CreateFromQuaternion(m_player->GetRot());
	//cameraPos = Vector3::Transform(cameraPos, rotY);
	//target = m_player->GetPlayer();
	//m_gameCamera->SetTarget(target);
	//m_gameCamera->SetEye(target + cameraPos);
	//m_view = m_gameCamera->GetViewMatrix();

	m_view = m_debugCamera->GetCameraMatrix();

	///�`��///////////////////
	//�v���C���[�̕`��
	m_player->Render();
	//CPU�̕`��
	m_cpu->Render();
	//�A�C�e���̕`��
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i]->Render();
		m_itemPlayerErase[i]->Render();
//		m_itemPlayerErase[i]->DrawCollision();
		m_itemCPU[i]->Render();
		m_itemCPUErase[i]->Render();
//		m_itemCPUErase[i]->DrawCollision();
	}
	//���̕`��
//	m_root->Render();
//���̃R���W�������b�V���̕`��
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_floorMesh->DrawCollision(context, m_view, m_projection);
	}
	//�S�[���̕`��
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Render();
		m_goal[i]->DrawCollision();
	}
	//�����蔻��̕`��
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i]->Render();
		m_box[i]->DrawCollision();
	}
	////////////////////////////
	//3D�X�v���C�g 
	//����
	Matrix worldPra;
	Matrix transPra = Matrix::CreateTranslation(Vector3(0.0f, -0.3f, 0.0f));
	worldPra = transPra;
	m_prairie->Draw(context, *m_states.get(), worldPra, m_view, m_projection);

	///////////////////////////////////////
	// ��
	Matrix worldSky;
	Matrix transSky = Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));
	Matrix scaleSky = Matrix::CreateScale(3.0f);
	worldSky = transSky * scaleSky;
	m_skydome->Draw(context, *m_states.get(), worldSky, m_view, m_projection);

	//2D�X�v���C�g�̕`��
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_sprites->Draw(m_tLap.Get(), Vector2(550, 1));
	m_sprites->Draw(m_tHO.Get(), Vector2(15, 250));
	m_sprites->Draw(m_tKm.Get(), Vector2(10, 500));
	//�J�E���g�_�E���̕`��-----------------------
	if (m_count > 0 && m_count < 59)
	{
		m_sprites->Draw(m_tCNum[3].Get(), Vector2(380, 220));
	}
	if (m_count > 60 && m_count <119)
	{
		m_sprites->Draw(m_tCNum[2].Get(), Vector2(380, 220));
	}
	if (m_count > 120 && m_count < 179)
	{
		m_sprites->Draw(m_tCNum[1].Get(), Vector2(380, 220));
	}
	if (m_count > 180 && m_count < 200)
	{
		m_sprites->Draw(m_tCGo.Get(), Vector2(320, 200));
	}

	//�^�C��--------------------------------------
	//�~���b
	float miri = m_time;
	
	//�b
	float sec = (int)(miri) / 100;

	//��
	float min = (int)(sec) / 60;

	if (sec >=59)
	{
		m_number[0].SetNum(min);
		m_time = 0;
	}
	m_number[0].SetPos(Vector2(20, 0));
	m_number[0].Draw(m_sprites.get());
	
	if (miri > 99)
	{
		m_number[1].SetNum(sec);
	}
	m_number[1].SetPos(Vector2(100, 0));
	m_number[1].Draw(m_sprites.get());

	m_number[2].SetNum(m_timeS);
	m_number[2].SetPos(Vector2(180, 0));
	m_number[2].Draw(m_sprites.get());
	if (m_timeS >= 100)
	{
		m_timeS = 0;
	}
	
	/////////////////////////////////////
	//�v���C���[���S�[��������
	if (m_goalPlayerFlag[0] == true && m_goalPlayerFlag[1] == true && m_goalPlayerFlag[2] == true &&
		m_goalPlayerFlag[3] == true && m_goalPlayerFlag[4] == true && m_goalPlayerFlag[5] == true)
	{
		//YOU WIN!�摜�\��
		m_sprites->Draw(m_tPlayerGoal.Get(), Vector2(200, 200));
	}

	//CPU���S�[��������
	else if (m_goalCPUFlag[0] == true && m_goalCPUFlag[1] == true && m_goalCPUFlag[2] == true &&
		m_goalCPUFlag[3] == true && m_goalCPUFlag[4] == true && m_goalCPUFlag[5] == true)
	{
		//YOU LOSE...�摜�\��
		m_sprites->Draw(m_tCPUGoal.Get(), Vector2(200, 200));
	}

	m_sprites->End();
}

void ScenePlay::CreateDeviceDependentResources()
{
	//�X�v���C�g�o�b�`�̍쐬
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();

	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<CommonStates>(device);

	// �X�v���C�g�o�b�`�̍쐬
	m_sprites = std::make_unique<SpriteBatch>(context);

	//2D�X�v���C�g�̕`��f��
	CreateWICTextureFromFile(device, L"Textures\\savanna_time.png", nullptr, m_tTime.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Lap.png",          nullptr, m_tLap.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Human&Datyou.png", nullptr, m_tHO.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\km.png",           nullptr, m_tKm.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouWin.png",       nullptr, m_tPlayerGoal.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouLose.png",      nullptr, m_tCPUGoal.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\0_red.png", nullptr, m_tCNum[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\1_red.png", nullptr, m_tCNum[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\2_red.png", nullptr, m_tCNum[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\3_red.png", nullptr, m_tCNum[3].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\4_red.png", nullptr, m_tCNum[4].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\5_red.png", nullptr, m_tCNum[5].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\6_red.png", nullptr, m_tCNum[6].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\7_red.png", nullptr, m_tCNum[7].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\8_red.png", nullptr, m_tCNum[8].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\9_red.png", nullptr, m_tCNum[9].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\GO.png",           nullptr, m_tCGo.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Waening.png",      nullptr, m_tFlipGoal.GetAddressOf());
	
	//�����̕`��--------------------------------
	for (int i = 0; i < TIME_SET_NUM; i++)
	{
		for (int j = 0; j < TIME_TYPE_NUM; j++)
		{
			m_number[i].SetTexture(j, m_tCNum[j].Get());
		}
	}
	//-------------------------------------------

	// ���f����ǂݍ���
	// �G�t�F�N�g�t�@�N�g���[ 
	EffectFactory fx(device);
	// ���f���̃e�N�X�`���̓����Ă���t�H���_���w�肷�� 
	fx.SetDirectory(L"Resources\\Models");      //�e�N�X�`���t����cmo������ꍇ��Ɏ����Ă���
	m_playerModel = Model::CreateFromCMO(device, L"Resources\\Models\\Ostrich&Human.cmo", fx);
	m_cpuModel  = Model::CreateFromCMO(device, L"Resources\\Models\\Tiger.cmo", fx);
	m_itemPlayerModel = Model::CreateFromCMO(device, L"Resources\\Models\\Item.cmo", fx);
	m_itemCPUModel = Model::CreateFromCMO(device, L"Resources\\Models\\esaC.cmo", fx);
	m_rootModel = Model::CreateFromCMO(device, L"Resources\\Models\\Root.cmo", fx);

	//�v���C���[�쐬
	PlayerCreate();

	//CPU�쐬
	CPUCreate();
	
	//�A�C�e���쐬(�v���C���[)
	ItemPlayerCreate();

	//�A�C�e�����ʐ؂�(�v���C���[)
	ItemPlayerEraseCreate();

	//�A�C�e���쐬(CPU)
	ItemCPUCreate();

	//�A�C�e�����ʐ؂�(CPU)
	ItemCPUEraseCreate();

	//�S�[���쐬
	GoalCreate();

	//���̍쐬
	CourseCreate();

	////���̃R���W�������b�V�����쐬
	m_floorMesh = std::make_unique<CollisionMesh>(device, L"Root.obj");

	//CPU�̈ړ��p�̓����蔻��
	EnemyHitMoveCreate();

	// ���f�������[�h���ă��f���n���h�����擾���� 
	//��
	m_skydome = Model::CreateFromCMO(device, L"Resources\\Models\\savanna.cmo", fx);
	m_skydome->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	//�n��
	m_prairie = Model::CreateFromCMO(device, L"Resources\\Models\\newSavanna.cmo", fx);
	m_prairie->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ���C�g�̉e�����Ȃ���
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// �G�~�b�V�����F�𔒂ɐݒ肷�� 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
}
//�v���C���[����
void ScenePlay::PlayerOperation(Keyboard::State &kb)
{
	//��L�[�������ꂽ��
	if (kb.Up || kb.W)
	{
		if (m_itemPlayerCheck == true)
		{
			m_player->PlayerMove(Player::FRONT_ITEMGET);
		}
		else if (m_itemPlayerCheck == false)
		{
			m_player->PlayerMove(Player::FRONT);
		}
	}
	//���L�[�������ꂽ��
	if (kb.Down || kb.S)
	{
		//	m_player->PlayerMove(Player::UP_ANGLE);
	}
	//�E�L�[�������ꂽ��
	if (kb.Right || kb.D)
	{
		m_player->PlayerMove(Player::RIGHT_TURN);
	}
	//���L�[�������ꂽ��
	if (kb.Left || kb.A)
	{
		m_player->PlayerMove(Player::LEFT_TURN);
	}
}
//�v���C���[����(�R�[�X�O)
void ScenePlay::PlayerOperationwOutSide(DirectX::Keyboard::State & kb)
{
	//��L�[�������ꂽ��
	if (kb.Up || kb.W)
	{
		m_player->PlayerMove(Player::FBONT_SPEEDDOWN);
	}
	//�E�L�[�������ꂽ��
	if (kb.Right || kb.D)
	{
		m_player->PlayerMove(Player::RIGHT_TURN);
	}
	//���L�[�������ꂽ��
	if (kb.Left || kb.A)
	{
		m_player->PlayerMove(Player::LEFT_TURN);
	}
}
//�A�C�e���擾
void ScenePlay::PlayerItemGet()
{
	//�v���C���[�̃A�C�e���擾
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		//�v���C���[�p�̃A�C�e���擾
		if (Collision::HitCheck_Capsule2Capsule(m_itemPlayer[i]->GetCollision(), m_player->GetCollision()))
		{
			m_itemPlayerCheck = true;
		}
		//�v���C���[�p�̃A�C�e�����ʐ؂�
		else if (Collision::HitCheck_Capsule2Capsule(m_itemPlayerErase[i]->GetCollision(), m_player->GetCollision()))
		{
			m_itemPlayerCheck = false;
		}
		//CPU�p�̃A�C�e���擾
		if (Collision::HitCheck_Capsule2Capsule(m_itemCPU[i]->GetCollision(), m_player->GetCollision()))
		{
			m_itemPlayerBadCheck = true;
		}
		//CPU�p�̃A�C�e�����ʐ؂�
		else if (Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[i]->GetCollision(), m_player->GetCollision()))
		{
			m_itemPlayerBadCheck = false;
		}
	}

}
void ScenePlay::CPUItemGet()
{
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		//CPU�A�C�e���擾
		if (Collision::HitCheck_Capsule2Capsule(m_itemCPU[i]->GetCollision(), m_cpu->GetCollision()))
		{
			m_itemCPUCheck = true;
		}

		if (Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[0]->GetCollision(), m_cpu->GetCollision()))
		{
			m_itemCPUCheck = false;
		}
	
	}
	//CPU�A�C�e���擾
	/*if (Collision::HitCheck_Capsule2Capsule(m_itemCPU[0]->GetCollision(), m_cpu->GetCollision()) == true ||
		Collision::HitCheck_Capsule2Capsule(m_itemCPU[1]->GetCollision(), m_cpu->GetCollision()) == true)
	{
		m_itemCPUCheck = true;
	}

	if (Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[0]->GetCollision(), m_cpu->GetCollision()) == true ||
		Collision::HitCheck_Capsule2Capsule(m_itemCPUErase[1]->GetCollision(), m_cpu->GetCollision()) == true)
	{
		m_itemCPUCheck = false;
	}*/
}
//CPU�̕�����ς��Ĉړ�������
void ScenePlay::EnemyDirection()
{
	//�A�C�e���擾���̈ړ����x
	if (m_itemCPUCheck == true)
	{
		m_cpu->EnemyChangeAngle(Enemy::FRONT_ITEMGET);
	}//�ʏ�̈ړ����x
	else if (m_itemCPUCheck == false)
	{
		m_cpu->EnemyChangeAngle(Enemy::FRONT);
	}
	//���������ꏊ�ɂ����CPU�̕�����ς���
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		if (Collision::HitCheck_Capsule2Capsule(m_box[i]->GetCollision(), m_cpu->GetCollision()))
		{
			m_cpu->EnemyChangeAngle(static_cast<Enemy::Direction>(i));
		}
	}
}
//�v���C���[���쐬
void ScenePlay::PlayerCreate()
{
	Collision::Capsule capsulePlayer;

	m_player = m_taskManager.AddTask<Player>();
	m_player->SetPosition(Vector3(-93.5f, 0, 1.5f));
	m_player->SetGame(m_game);
	m_player->SetModel(m_playerModel.get());
	m_player->SetUpEffect();
	// �J�v�Z���^�̃R���W����������
	capsulePlayer.start = Vector3(0.3f, 0.0f, 0.2f); 		//���E���̒��S
	capsulePlayer.end = Vector3(0.3f, 3.0f, 0.2f); 		//���E���̒��S
	capsulePlayer.r = 0.6f;							     	//���a
	m_player->SetCollision(capsulePlayer);
}
//CPU�쐬
void ScenePlay::CPUCreate()
{
	Collision::Capsule capsuleCPU;
	m_cpu = std::make_unique<Enemy>();
	m_cpu->SetPosition(Vector3(-97.5f, 0, 1.5f));
	m_cpu->SetGame(m_game);
	m_cpu->SetModel(m_cpuModel.get());
	// �J�v�Z���^�̃R���W����������
	capsuleCPU.start = Vector3(0.3f, 0.0f, 0.2f);           //���E���̒��S
	capsuleCPU.end = Vector3(0.3f, 3.0f, 0.2f);		        //���E���̒��S
	capsuleCPU.r = 0.6f;                                    //���a
	m_cpu->SetCollision(capsuleCPU);
}
//�A�C�e���쐬(�v���C���[)
void ScenePlay::ItemPlayerCreate()
{
	Collision::Capsule capsuleItemPlayer[ITEM_SET_NUM];

	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i] = std::make_unique<Item>();
		m_itemPlayer[i]->SetGame(m_game);
		m_itemPlayer[i]->SetModel(m_itemPlayerModel.get());
		// �J�v�Z���^�̃R���W����������
		capsuleItemPlayer[i].r = 1.5f;                                    //���a
		switch (i)
		{
		case 0:
			m_itemPlayer[0]->SetPosition(Vector3(-93.5f, 0, 40.0f));
			capsuleItemPlayer[0].start = Vector3(0.5f, 0.5f, 0.5f);       //���E���̒��S
			capsuleItemPlayer[0].end = Vector3(0.5f, 0.5f, 0.5f);		    //���E���̒��S
			break;
		case 1:
			m_itemPlayer[1]->SetPosition(Vector3(94.0f, 0, 10.0f));
			capsuleItemPlayer[1].start = Vector3(1.0f, 1.0f, 1.0f);           //���E���̒��S
			capsuleItemPlayer[1].end = Vector3(1.0f, 1.0f, 1.0f);		    //���E���̒��S
			break;
		}
		m_itemPlayer[i]->SetCollision(capsuleItemPlayer[i]);
	}
}
//�A�C�e�����ʐ؂�(�v���C���[)
void ScenePlay::ItemPlayerEraseCreate()
{
	Collision::Capsule capsuleItemPlayerErase[ITEM_SET_NUM];

	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayerErase[i] = std::make_unique<CollisionCapsule>();
		m_itemPlayerErase[i]->SetGame(m_game);
		m_itemPlayerErase[i]->SetModel(m_itemPlayerEraseModel.get());
		capsuleItemPlayerErase[i].r = 1.5f;                                    //���a
		switch (i)
		{
		case 0:
			m_itemPlayerErase[0]->SetPosition(Vector3(0.0f, 14, 95.0f));
			capsuleItemPlayerErase[0].start = Vector3(0.5f, 0.5f, 5.0f);           //���E���̒��S
			capsuleItemPlayerErase[0].end = Vector3(0.5f, 0.5f, -5.0f);		    //���E���̒��S
			break;
		case 1:
			m_itemPlayerErase[1]->SetPosition(Vector3(30.0f, 0, -75.0f));
			capsuleItemPlayerErase[1].start = Vector3(3.5f, 0.5f, 5.0f);           //���E���̒��S
			capsuleItemPlayerErase[1].end = Vector3(-3.5f, 0.5f, -5.0f);		    //���E���̒��S
			break;
		}
		m_itemPlayerErase[i]->SetCollision(capsuleItemPlayerErase[i]);
	}
}
//�A�C�e���쐬(CPU
void ScenePlay::ItemCPUCreate()
{
	Collision::Capsule capsuleItemCPU[ITEM_SET_NUM];

	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemCPU[i] = std::make_unique<Item>();
		m_itemCPU[i]->SetGame(m_game);
		m_itemCPU[i]->SetModel(m_itemCPUModel.get());
		capsuleItemCPU[i].r = 1.5f;                                    //���a
		switch (i)
		{
		case 0:
			m_itemCPU[0]->SetPosition(Vector3(-98.5f, 0, 40.0f));
			capsuleItemCPU[0].start = Vector3(0.5f, 0.5f, 0.5f);       //���E���̒��S
			capsuleItemCPU[0].end = Vector3(0.5f, 0.5f, 0.5f);		    //���E���̒��S
			break;
		case 1:
			m_itemCPU[1]->SetPosition(Vector3(88.0f, 0, 10.0f));
			capsuleItemCPU[1].start = Vector3(1.0f, 1.0f, 1.0f);           //���E���̒��S
			capsuleItemCPU[1].end = Vector3(1.0f, 1.0f, 1.0f);		    //���E���̒��S
			break;
		}
		m_itemCPU[i]->SetCollision(capsuleItemCPU[i]);
	}
}
//�A�C�e�����ʐ؂�(CPU)
void ScenePlay::ItemCPUEraseCreate()
{
	Collision::Capsule capsuleItemCPUErase[ITEM_SET_NUM];

	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemCPUErase[i] = std::make_unique<CollisionCapsule>();
		m_itemCPUErase[i]->SetGame(m_game);
		m_itemCPUErase[i]->SetModel(m_itemCPUEraseModel.get());
		capsuleItemCPUErase[i].r = 1.5f;                                    //���a
		switch (i)
		{
		case 0:
			m_itemCPUErase[0]->SetPosition(Vector3(0.0f, 14, 95.0f));
			capsuleItemCPUErase[0].start = Vector3(0.5f, 0.5f, 5.0f);           //���E���̒��S
			capsuleItemCPUErase[0].end = Vector3(0.5f, 0.5f, -5.0f);		    //���E���̒��S
			break;
		case 1:
			m_itemCPUErase[1]->SetPosition(Vector3(30.0f, 0, -75.0f));
			capsuleItemCPUErase[1].start = Vector3(3.5f, 0.5f, 5.0f);           //���E���̒��S
			capsuleItemCPUErase[1].end = Vector3(-3.5f, 0.5f, -5.0f);		    //���E���̒��S
			break;
		}
		m_itemCPUErase[i]->SetCollision(capsuleItemCPUErase[i]);
	}
}
//�R�[�X�쐬
void ScenePlay::CourseCreate()
{
	//���̍쐬												      
	m_root = m_taskManager.AddTask<Obj3D>();
	m_root->SetGame(m_game);
	m_root->SetModel(m_rootModel.get());

}
//�S�[���쐬
void ScenePlay::GoalCreate()
{
	Collision::Capsule capsuleGoal[GOAL_SET_NUM];

	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i] = std::make_unique<CollisionCapsule>();

		m_goal[i]->SetGame(m_game);
		m_goal[i]->SetModel(m_goalModel.get());
		capsuleGoal[i].r = 0.6f;
		// �J�v�Z���^�̃R���W����������
		switch (i)
		{
		case 0:
			m_goal[0]->SetPosition(Vector3(-96.0f, 0, 5.0f));
			capsuleGoal[0].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
			capsuleGoal[0].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
			break;
		case 1:
			m_goal[1]->SetPosition(Vector3(0, 14, 95.0f));
			capsuleGoal[1].start = Vector3(0.0f, 0.0f, 3.5f);           //���E���̒��S
			capsuleGoal[1].end = Vector3(0.0f, 0.0f, -3.5f);		    //���E���̒��S
			break;
		case 2:
			m_goal[2]->SetPosition(Vector3(93.0f, 0, 0.0f));
			capsuleGoal[2].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
			capsuleGoal[2].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
			break;
		case 3:
			m_goal[3]->SetPosition(Vector3(10.0f, 0, 0));
			capsuleGoal[3].start = Vector3(6.0f, 0.0f, 0.0f);           //���E���̒��S
			capsuleGoal[3].end = Vector3(-6.0f, 0.0f, 0.0f);		    //���E���̒��S
			break;
		case 4:
			m_goal[4]->SetPosition(Vector3(-40.0f, 0, 0));
			capsuleGoal[4].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
			capsuleGoal[4].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
			break;
		case 5:
			m_goal[5]->SetPosition(Vector3(-96.0f, 0, -3.0f));
			capsuleGoal[5].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
			capsuleGoal[5].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
			break;
		}
		
		m_goal[i]->SetCollision(capsuleGoal[i]);
	}
}
//CPU�̈ړ��p�̓����蔻��
void ScenePlay::EnemyHitMoveCreate()
{
	Collision::Capsule capsulebox[ENEMY_HITCHECK_NUM];
	
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i] = std::make_unique<CollisionCapsule>();
		m_box[i]->SetGame(m_game);

		capsulebox[i].r = 5.0f;
		switch (i)
		{
		case 0:
			m_box[0]->SetPosition(Vector3(-96.0f, 0.0f, 0.0f));
			capsulebox[0].start = Vector3(0.0f, 0.0f, 80.0f);
			capsulebox[0].end = Vector3(0.0f, 0.0f, -80.0f);
			break;
		case 1:
			m_box[1]->SetPosition(Vector3(-85.0f, 0.0f, 87.0f));
			capsulebox[1].start = Vector3(7.0f, 0.0f, 7.0f);
			capsulebox[1].end = Vector3(-10.0f, 0.0f, -10.0f);
			capsulebox[1].r = 5.5f;
			break;
		case 2:
			m_box[2]->SetPosition(Vector3(0.0f, 0.0f, 95.0f));
			capsulebox[2].start = Vector3(70.0f, 0.0f, 0.0f);
			capsulebox[2].end = Vector3(-75.0f, 0.0f, 0.0f);
			break;
		case 3:
			m_box[3]->SetPosition(Vector3(84.0f, 0.0f, 85.0f));
			capsulebox[3].start = Vector3(5.0f, 0.0f, -5.0f);
			capsulebox[3].end = Vector3(-8.0f, 0.0f, 8.0f);
			capsulebox[3].r = 5.5f;
			break;
		case 4:
			m_box[4]->SetPosition(Vector3(92.0f, 0.0f, 0.0f));
			capsulebox[4].start = Vector3(0.0f, 0.0f, 75.0f);
			capsulebox[4].end = Vector3(0.0f, 0.0f, -80.0f);
			break;
		case 5:
			m_box[5]->SetPosition(Vector3(86.0f, 0.0f, -90.0f));
			capsulebox[5].start = Vector3(10.0f, 0.0f, 10.0f);
			capsulebox[5].end = Vector3(-8.0f, 0.0f, -8.0f);
			break;
		case 6:
			m_box[6]->SetPosition(Vector3(70.0f, 0.0f, -100.0f));
			capsulebox[6].start = Vector3(10.0f, 0.0f, 0.0f);
			capsulebox[6].end = Vector3(-13.0f, 0.0f, 0.0f);
			break;
		case 7:
			m_box[7]->SetPosition(Vector3(25.0f, 0.0f, -70.0f));
			capsulebox[8].start = Vector3(30.0f, 0.0f, -30.0f);
			capsulebox[8].end = Vector3(-25.0f, 0.0f, 25.0f);
			break;
		case 8:
			m_box[8]->SetPosition(Vector3(-5.0f, 0.0f, -25.0f));
			capsulebox[8].start = Vector3(-0.0f, 0.0f, 3.0f);
			capsulebox[8].end = Vector3(0.0f, 0.0f, -15.0f);
			capsulebox[8].r = 5.5f;
			break;
		case 9:
			m_box[9]->SetPosition(Vector3(17.0f, 0.0f, 7.0f));
			capsulebox[9].start = Vector3(18.0f, 0.0f, 18.0f);
			capsulebox[9].end = Vector3(-25.0f, 0.0f, -25.0f);
			break;
		case 10:
			m_box[10]->SetPosition(Vector3(40.0f, 0.0f, 33.0f));
			capsulebox[10].start = Vector3(0.0f, 0.0f, 5.0f);
			capsulebox[10].end = Vector3(-4.0f, 0.0f, -7.0f);
			break;
		case 11:
			m_box[11]->SetPosition(Vector3(40.0f, 0.0f, 43.0f));
			capsulebox[11].start = Vector3(0.0f, 0.0f, 7.0f);
			capsulebox[11].end = Vector3(1.0f, 0.0f, -5.0f);
			break;
		case 12:
			m_box[12]->SetPosition(Vector3(33.0f, 0.0f, 60.0f));
			capsulebox[12].start = Vector3(7.0f, 0.0f, -7.0f);
			capsulebox[12].end = Vector3(-7.0f, 0.0f, 7.0f);
			capsulebox[12].r = 5.5f;
			break;
		case 13:
			m_box[13]->SetPosition(Vector3(0.0f, 0.0f, 70.0f));
			capsulebox[13].start = Vector3(20.0f, 0.0f, 0.0f);
			capsulebox[13].end = Vector3(-20.0f, 0.0f, 0.0f);
			break;
		case 14:
			m_box[14]->SetPosition(Vector3(-30.0f, 0.0f, 65.0f));
			capsulebox[14].start = Vector3(5.0f, 0.0f, 5.0f);
			capsulebox[14].end = Vector3(-8.0f, 0.0f, -8.0f);
			break;
		case 15:
			m_box[15]->SetPosition(Vector3(-40.0f, 0.0f, -10.0f));
			capsulebox[15].start = Vector3(0.0f, 0.0f, 70.0f);
			capsulebox[15].end = Vector3(0.0f, 0.0f, -68.0f);
			break;
		case 16:
			m_box[16]->SetPosition(Vector3(-50.0f, 0.0f, -95.0f));
			capsulebox[16].start = Vector3(7.0f, 0.0f, 10.0f);
			capsulebox[16].end = Vector3(-10.0f, 0.0f, -5.0f);
			capsulebox[16].r = 5.5f;
			break;
		case 17:
			m_box[17]->SetPosition(Vector3(-70.0f, 0.0f, -100.0f));
			capsulebox[17].start = Vector3(3.0f, 0.0f, 0.0f);
			capsulebox[17].end = Vector3(-3.0f, 0.0f, 0.0f);
			capsulebox[17].r = 6.5f;
			break;
		case 18:
			m_box[18]->SetPosition(Vector3(-88.0f, 0.0f, -90.0f));
			capsulebox[18].start = Vector3(10.0f, 0.0f, -10.0f);
			capsulebox[18].end = Vector3(-7.0f, 0.0f, 7.0f);
			capsulebox[18].r = 5.5f;
			break;
		case 19:
			m_box[19]->SetPosition(Vector3(-93.5f, 0, 9.0f));
			capsulebox[19].start = Vector3(0.5f, 0.5f, 0.5f);
			capsulebox[19].end = Vector3(0.5f, 0.5f, 0.5f);
			capsulebox[19].r = 3.5f;
			break;
		}

		m_box[i]->SetCollision(capsulebox[i]);
	}
}
