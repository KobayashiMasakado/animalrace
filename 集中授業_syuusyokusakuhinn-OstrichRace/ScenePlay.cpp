#include "pch.h"
#include "ScenePlay.h"
#include <time.h>
#include "ModelDate.h"

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
	//�A�C�e���t���O�̏�����
	m_itemPlayerCheck = false;
	m_itemCPUCheck = false;
	m_itemPlayerBadCheck = false;
	m_itemCPUBadCheck = false;
	//�J�E���g�_�E���̏�����
	m_count = 0;

	m_checkPoint = 0;
	
	m_time = 0;
	m_timeS = 0;

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
	m_count += 1;
	
	///�X�V/////////////////////
	//�v���C���[�̍X�V
	m_player->Update(elapsedTime);
	//CPU�̍X�V
	m_cpu->Update(elapsedTime);
//	m_root->Update(elapsedTime);
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
	//�v���C���[�ƃR�[�X�̓����蔻��
	static int id;
	Vector3 s;
	Vector3 playerPos = m_player->GetPlayer();
	Vector3 v[2] = { Vector3(playerPos.x,100,playerPos.z),Vector3(playerPos.x,-1,playerPos.z) };
	if (m_floorMesh->HitCheck_Segment(v[0], v[1], &id, &s))
	{
		m_hitPlayerFlag = true;
		s.y -= 0.1f;
		m_player->SetPosition(s);
	}
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		if (Collision::HitCheck_Capsule2Capsule(m_box[i]->GetCollision()
			, m_cpu->GetCollision()) == true)
		{
			m_hitCpuFlag = true;
		}
	}

	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		//�S�[���ƃv���C���[�̓����蔻�������
		if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
			, m_player->GetCollision()) == true)
		{
			if (m_checkPoint == i)
			{
				m_goalPlayerFlag[i] = true;
				m_checkPoint = i + 1;
			}
		}
		//�S�[����CPU�̓����蔻�������
		if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
			, m_cpu->GetCollision()) == true)
		{
			m_goalCPUFlag[i] = true;
		}
	}
	//�J�E���g�_�E�����I�������
	if (m_count > GAME_START_TIME)
	{
		m_time += 1;
		m_timeS += 1;
		for (int i = 0; i < GOAL_SET_NUM; i++)
		{
			//�v���C���[�̈ړ�
			if (m_goalCPUFlag[i] == true)
			{
				m_player->PlayerMove(Player::NONE);
			}
			else if (m_hitPlayerFlag == true)
			{
				//�v���C���[����
				m_player->PlayerOperation(kb);
			}
			else if (m_hitPlayerFlag == false)
			{
				//�v���C���[����(�R�[�X�O)
				m_player->PlayerOperationwOutSide(kb);
			}
			//�A�C�e���擾
			m_player->PlayerItemGet(m_itemPlayer,m_itemPlayerErase,m_itemCPU,m_itemCPUErase);
			//CPU�̈ړ�
			//�S�[��������
			if (m_goalPlayerFlag[i] == true)
			{
				m_cpu->EnemyChangeAngle(Enemy::NONE);
			}
			//�S�[�����ĂȂ��Ȃ�
			else if (m_hitCpuFlag == true)
			{
				//CPU�̕�����ς��Ĉړ�������
				//�A�C�e���擾���̈ړ����x
				if (m_itemCPUCheck == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::FRONT_ITEMGET);
				}//�ʏ�̈ړ����x
				else if (m_itemCPUCheck == false)
				{
					m_cpu->EnemyChangeAngle(Enemy::FRONT);
				}

				if (Collision::HitCheck_Capsule2Capsule(m_box[2]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::UP_ANGLE);
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_SIDE);
				}
				else	if (Collision::HitCheck_Capsule2Capsule(m_box[1]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_OBLF);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[3]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_SIDE);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[4]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::DOWN_ANGLE);
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_SIDE);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[5]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_OBLB);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[6]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::BACK);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[7]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_OBLB);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[8]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_SIDE);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[9]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_OBLF);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[10]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::FRONT_SECOND);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[11]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_OBLF);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[12]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::RIGHT_OBLF);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[13]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::FRONT_SECOND);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[14]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_OBLF);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[15]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_SIDE);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[16]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_OBLB);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[17]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::UP_ANGLE); 
					m_cpu->EnemyChangeAngle(Enemy::BACK);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[18]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::BACK);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[19]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::DOWN_ANGLE);
					m_cpu->EnemyChangeAngle(Enemy::BACK);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[20]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_OBLB);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[21]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_SIDE);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[0]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::FRONT_SECOND);
				}
				else if (Collision::HitCheck_Capsule2Capsule(m_box[22]->GetCollision(), m_cpu->GetCollision()) == true)
				{
					m_cpu->EnemyChangeAngle(Enemy::LEFT_OBLF);
				}
			}
			//������
			else if (m_hitCpuFlag == false)
			{
				m_cpu->EnemyChangeAngle(Enemy::BACK);
			}
			//CPU�A�C�e���擾
			m_cpu->CPUItemGet(m_itemCPU,m_itemCPUErase);
		}
	}
	//�d��
	if (m_player->GetPlayer().y >= GROUND_POSY)
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
	//	m_itemPlayerErase[i]->DrawCollision();
		m_itemCPU[i]->Render();
		m_itemCPUErase[i]->Render();
	//	m_itemCPUErase[i]->DrawCollision();
	}
	//�R�[�X�̍쐬
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
//		m_goal[i]->DrawCollision();
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
	//�Q�[������
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
	//�^�C��--------------------------------------
	//�~���b
	float miri = m_time;
	
	//�b
	float sec = (int)(miri) / TIME_MIRI;

	//��
	float min = (int)(sec) / TIME_MINUTE;

	if (sec >= TIME_MINUTE - 1)
	{
		m_number[0].SetNum(min);
		m_time = 0;
	}
	m_number[0].SetPos(Vector2(20, 0));
	m_number[0].Draw(m_sprites.get());
	
	if (miri > TIME_MIRI - 1)
	{
		m_number[1].SetNum(sec);
	}
	m_number[1].SetPos(Vector2(100, 0));
	m_number[1].Draw(m_sprites.get());

	m_number[2].SetNum(m_timeS);
	m_number[2].SetPos(Vector2(180, 0));
	m_number[2].Draw(m_sprites.get());
	if (m_timeS >= TIME_MIRI)
	{
		m_timeS = 0;
	}
	/////////////////////////////////////
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
	CreateWICTextureFromFile(device, L"Textures\\0_red.png",        nullptr, m_tCNum[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\1_red.png",        nullptr, m_tCNum[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\2_red.png",        nullptr, m_tCNum[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\3_red.png",        nullptr, m_tCNum[3].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\4_red.png",        nullptr, m_tCNum[4].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\5_red.png",        nullptr, m_tCNum[5].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\6_red.png",        nullptr, m_tCNum[6].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\7_red.png",        nullptr, m_tCNum[7].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\8_red.png",        nullptr, m_tCNum[8].GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\9_red.png",        nullptr, m_tCNum[9].GetAddressOf());
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

	//�J�E���g�_�E��
	for (int i = 3; i > 0; i--)
	{
		if (m_count > ((i * TIME_MINUTE) - GAME_START_TIME) * -1 && m_count < (((i * TIME_MINUTE) - GAME_START_TIME) * -1) + (TIME_MINUTE - 1))
		{
			m_sprites->Draw(m_tCNum[i].Get(), Vector2(380, 220));
		}
	}
	if (m_count > GAME_START_TIME && m_count < 200)
	{
		m_sprites->Draw(m_tCGo.Get(), Vector2(320, 200));
	}
	//-------------------------------------------
	m_objCreate = new ObjectCreate();
	m_player = new Player();
	m_cpu = new Enemy();
	
	// ���f����ǂݍ���
	// �G�t�F�N�g�t�@�N�g���[ 
	EffectFactory fx(device);
	// ���f���̃e�N�X�`���̓����Ă���t�H���_���w�肷�� 
	fx.SetDirectory(L"Resources\\Models");      //�e�N�X�`���t����cmo������ꍇ��Ɏ����Ă���
	ModelDate* modelDate = ModelDate::GetInstance();

	//�v���C���[�쐬
	m_player->PlayerCreate();
	//CPU�쐬
	m_cpu->CPUCreate();

	
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{//�A�C�e���쐬(�v���C���[)
		m_itemPlayer[i] = std::make_unique<Item>();
		m_itemPlayer[i]->ItemPlayerCreate(i);
	
	//�A�C�e���쐬(CPU)
		m_itemCPU[i] = std::make_unique<Item>();
		m_itemCPU[i]->ItemCPUCreate(i);
	
	//�A�C�e�����ʐ؂�(�v���C���[)
		m_itemPlayerErase[i] = std::make_unique<Item>();
		m_itemPlayerErase[i]->ItemPlayerEraseCreate(i);
	
	//�A�C�e�����ʐ؂�(CPU)
		m_itemCPUErase[i] = std::make_unique<Item>();
		m_itemCPUErase[i]->ItemCPUEraseCreate(i);
	}
	
	//�S�[���쐬
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i] = std::make_unique<Goal>();
		m_goal[i]->GoalCreate(i);
	}
	
	//���̃R���W�������b�V�����쐬
	m_floorMesh = std::make_unique<CollisionMesh>(device, L"Root.obj");

	//CPU�̈ړ��p�̓����蔻��
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i] = std::make_unique<Root>();
	//	m_box[i]->EnemyHitMoveCreate(i);
	}
	EnemyHitMoveCreate();

//	GoalCreate();
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

	GameSeter();
}

void ScenePlay::GameSeter()
{
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i]->SetGame(m_game);
		m_itemCPU[i]->SetGame(m_game);
		m_itemPlayerErase[i]->SetGame(m_game);
		m_itemCPUErase[i]->SetGame(m_game);
	}

	m_floorMesh->SetGame(m_game);
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->SetGame(m_game);
	}

	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i]->SetGame(m_game);
	}

	m_player->SetGame(m_game);

	m_cpu->SetGame(m_game);
}
//CPU�̈ړ��p�̓����蔻��
void ScenePlay::EnemyHitMoveCreate()
{
	Collision::Capsule capsule[ENEMY_HITCHECK_NUM];
	ModelDate* modelDate = ModelDate::GetInstance();
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i] = std::make_unique<Root>();
		m_box[i]->SetGame(m_game);
		capsule[i].r = 5.0f;
		switch (i)
		{
		case 0:
			m_box[0]->SetPosition(Vector3(-96.0f, 0.0f, 0.0f));
			capsule[0].start = Vector3(0.0f, 0.0f, 80.0f);
			capsule[0].end = Vector3(0.0f, 0.0f, -80.0f);
			break;
		case 1:
			m_box[1]->SetPosition(Vector3(-84.0f, 0.0f, 87.0f));
			capsule[1].start = Vector3(7.0f, 0.0f, 5.0f);
			capsule[1].end = Vector3(-10.0f, 0.0f, -10.0f);
			capsule[1].r = 5.5f;
			break;
		case 2:
			m_box[2]->SetPosition(Vector3(-12.0f, 8.0f, 95.0f));
			capsule[2].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[2].end = Vector3(-60.0f, -8.0f, 0.0f);
			break;
		case 3:
			m_box[3]->SetPosition(Vector3(0.0f, 10.0f, 95.0f));
			capsule[3].start = Vector3(6.0f, 0.0f, 0.0f);
			capsule[3].end = Vector3(-6.0f, 0.0f, 0.0f);
			break;
		case 4:
			m_box[4]->SetPosition(Vector3(10.0f, 8.0f, 95.0f));
			capsule[4].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[4].end = Vector3(60.0f, -8.0f, 0.0f);
			break;

		case 5:
			m_box[5]->SetPosition(Vector3(84.0f, 0.0f, 85.0f));
			capsule[5].start = Vector3(5.0f, 0.0f, -5.0f);
			capsule[5].end = Vector3(-8.0f, 0.0f, 8.0f);
			capsule[5].r = 5.5f;
			break;
		case 6:
			m_box[6]->SetPosition(Vector3(92.0f, 0.0f, 0.0f));
			capsule[6].start = Vector3(0.0f, 0.0f, 75.0f);
			capsule[6].end = Vector3(0.0f, 0.0f, -80.0f);
			break;
		case 7:
			m_box[7]->SetPosition(Vector3(86.0f, 0.0f, -90.0f));
			capsule[7].start = Vector3(10.0f, 0.0f, 10.0f);
			capsule[7].end = Vector3(-8.0f, 0.0f, -8.0f);
			break;
		case 8:
			m_box[8]->SetPosition(Vector3(70.0f, 0.0f, -100.0f));
			capsule[8].start = Vector3(10.0f, 0.0f, 0.0f);
			capsule[8].end = Vector3(-13.0f, 0.0f, 0.0f);
			break;
		case 9:
			m_box[9]->SetPosition(Vector3(25.0f, 0.0f, -70.0f));
			capsule[9].start = Vector3(30.0f, 0.0f, -30.0f);
			capsule[9].end = Vector3(-25.0f, 0.0f, 25.0f);
			break;
		case 10:
			m_box[10]->SetPosition(Vector3(-5.0f, 0.0f, -25.0f));
			capsule[10].start = Vector3(-0.0f, 0.0f, 3.0f);
			capsule[10].end = Vector3(0.0f, 0.0f, -15.0f);
			capsule[10].r = 5.5f;
			break;
		case 11:
			m_box[11]->SetPosition(Vector3(17.0f, 0.0f, 7.0f));
			capsule[11].start = Vector3(18.0f, 0.0f, 18.0f);
			capsule[11].end = Vector3(-25.0f, 0.0f, -25.0f);
			break;
		case 12:
			m_box[12]->SetPosition(Vector3(40.0f, 0.0f, 33.0f));
			capsule[12].start = Vector3(0.0f, 0.0f, 5.0f);
			capsule[12].end = Vector3(-4.0f, 0.0f, -7.0f);
			break;
		case 13:
			m_box[13]->SetPosition(Vector3(40.0f, 0.0f, 43.0f));
			capsule[13].start = Vector3(0.0f, 0.0f, 7.0f);
			capsule[13].end = Vector3(1.0f, 0.0f, -5.0f);
			break;
		case 14:
			m_box[14]->SetPosition(Vector3(33.0f, 0.0f, 60.0f));
			capsule[14].start = Vector3(7.0f, 0.0f, -7.0f);
			capsule[14].end = Vector3(-7.0f, 0.0f, 7.0f);
			capsule[14].r = 5.5f;
			break;
		case 15:
			m_box[15]->SetPosition(Vector3(0.0f, 0.0f, 70.0f));
			capsule[15].start = Vector3(20.0f, 0.0f, 0.0f);
			capsule[15].end = Vector3(-20.0f, 0.0f, 0.0f);
			break;
		case 16:
			m_box[16]->SetPosition(Vector3(-30.0f, 0.0f, 65.0f));
			capsule[16].start = Vector3(5.0f, 0.0f, 5.0f);
			capsule[16].end = Vector3(-7.0f, 0.0f, -8.0f);
			break;
		case 17:
			m_box[17]->SetPosition(Vector3(-40.0f, 0.0f,55.0f));
			capsule[17].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[17].end = Vector3(0.0f, 10.0f, -60.0f);
			break;
		case 18:
			m_box[18]->SetPosition(Vector3(-40.0f, 10.0f, -20.0f));
			capsule[18].end = Vector3(0.0f, 0.0f, 7.0f);
			capsule[18].start = Vector3(0.0f, 0.0f, -7.0f);
			break;
		case 19:
			m_box[19]->SetPosition(Vector3(-40.0f, 0.0f, -78.0f));
			capsule[19].start = Vector3(0.0f, 0.0f, 0.0f);
			capsule[19].end = Vector3(0.0f, 10.0f, 50.0f);
			break;
		case 20:
			m_box[20]->SetPosition(Vector3(-50.0f, 0.0f, -95.0f));
			capsule[20].start = Vector3(7.0f, 0.0f, 10.0f);
			capsule[20].end = Vector3(-10.0f, 1.0f, -5.0f);
			capsule[16].r = 5.5f;
			break;
		case 21:
			m_box[21]->SetPosition(Vector3(-70.0f, 0.0f, -100.0f));
			capsule[21].start = Vector3(3.0f, 0.0f, 0.0f);
			capsule[21].end = Vector3(-3.0f, 0.0f, 0.0f);
			capsule[21].r = 6.5f;
			break;
		case 22:
			m_box[22]->SetPosition(Vector3(-88.0f, 0.0f, -90.0f));
			capsule[22].start = Vector3(10.0f, 0.0f, -10.0f);
			capsule[22].end = Vector3(-7.0f, 0.0f, 7.0f);
			capsule[22].r = 5.5f;
			break;
		}

		m_box[i]->SetCollision(capsule[i]);
	}
}
////�S�[���쐬
//void ScenePlay::GoalCreate()
//{
//	Collision::Capsule capsule[GOAL_SET_NUM];
//	ModelDate* modelDate = ModelDate::GetInstance();
//	
//	for (int i = 0; i < GOAL_SET_NUM; i++)
//	{
//		m_goal[i] = std::make_unique<Goal>();
//		m_goal[i]->SetGame(m_game);
//		capsule[i].r = 0.6f;
//		// �J�v�Z���^�̃R���W����������
//		switch (i)
//		{
//		case 0:
//			m_goal[0]->SetPosition(Vector3(-96.0f, 0, 5.0f));
//			capsule[0].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
//			capsule[0].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
//			break;
//		case 1:
//			m_goal[1]->SetPosition(Vector3(0, 10, 95.0f));
//			capsule[1].start = Vector3(0.0f, 0.0f, 5.5f);           //���E���̒��S
//			capsule[1].end = Vector3(0.0f, 0.0f, -5.5f);		    //���E���̒��S
//			break;
//		case 2:
//			m_goal[2]->SetPosition(Vector3(93.0f, 0, 0.0f));
//			capsule[2].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
//			capsule[2].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
//			break;
//		case 3:
//			m_goal[3]->SetPosition(Vector3(10.0f, 0, 0));
//			capsule[3].start = Vector3(6.0f, 0.0f, 0.0f);           //���E���̒��S
//			capsule[3].end = Vector3(-6.0f, 0.0f, 0.0f);		    //���E���̒��S
//			break;
//		case 4:
//			m_goal[4]->SetPosition(Vector3(-40.0f, 10, -10));
//			capsule[4].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
//			capsule[4].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
//			break;
//		case 5:
//			m_goal[5]->SetPosition(Vector3(-96.0f, 0, -3.0f));
//			capsule[5].start = Vector3(5.0f, 0.0f, 0.0f);           //���E���̒��S
//			capsule[5].end = Vector3(-5.0f, 0.0f, 0.0f);		    //���E���̒��S
//			break;
//		}
//
//		m_goal[i]->SetCollision(capsule[i]);
//	}
//}
