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
//	m_itemFun->Update(elapsedTime);
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
	//	m_itemFun->Render();
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
	//	m_box[i]->DrawCollision();
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
	{   //�A�C�e���쐬(�v���C���[)
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

		//�A�C�e���쐬(�t��)
		m_itemCPUErase[i] = std::make_unique<Item>();
		m_itemCPUErase[i]->ItemCPUEraseCreate(i);
	}
	/*m_itemFun = std::make_unique<Item>();
	m_itemFun->ItemFunCreate();*/
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
		m_box[i]->EnemyHitMoveCreate(i);
	}
	//EnemyHitMoveCreate();

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
	//m_itemFun->SetGame(m_game);

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