#include "pch.h"
#include "ScenePlay.h"
#include <time.h>

#include <Effects.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>
#include <CommonStates.h>
#include "ModelDate.h"
#include "GameCamera.h"


#include "Game.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ScenePlay::ScenePlay()
{
	m_effectLeafManager = nullptr;
	m_effectMeatManager = nullptr;
	m_effectFunManager = nullptr;
}

ScenePlay::~ScenePlay()
{
}

void ScenePlay::Initialize()
{
	//ゴールフラグの初期化
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goalPlayerFlag[i] = false;
		m_goalCPUFlag[i] = false;
	}
	//アイテムフラグの初期化
	m_itemCPUCheck = false;
	m_itemCPUBadCheck = false;
	m_itemFunCheck = false;

	//カウントダウンの初期化
	m_count = 0;

	m_checkPoint = 0;
	
	m_time = 0;
	m_timeS = 0;

//	m_debugCamera = std::make_unique<DebugCamera>(800, 600);
}

void ScenePlay::Update(DX::StepTimer timer)//float elapsedTime)
{
	// デバッグカメラの更新
//	m_debugCamera->Update();
	// キーボードの状態を取得する
	Keyboard::State kb = Keyboard::Get().GetState();
    //カウントダウン（処理はカウントアップ）
	m_count += 1;
	///更新/////////////////////
	float elapsedTime = timer.GetTotalSeconds();
	m_effectLeafManager->Update(timer);
	m_effectMeatManager->Update(timer);
	m_effectFunManager->Update(timer);
	//プレイヤーの更新
	if (m_count > GAME_START_TIME)
	{
		m_player->Update(elapsedTime);
	}
	//CPUの更新
	m_cpu->Update(elapsedTime);
	//アイテムの更新
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i]->Update(elapsedTime);
		m_itemPlayerErase[i]->Update(elapsedTime);
		m_itemCPU[i]->Update(elapsedTime);
		m_itemCPUErase[i]->Update(elapsedTime);
		m_itemFun[i]->Update(elapsedTime);
		m_itemFunErase[i]->Update(elapsedTime);
	}
	//ゴールの更新
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Update(elapsedTime);
	}
	//コースの当たり判定の更新
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i]->Update(elapsedTime);
	}
	/////当たり判定////////////
	CollisionUpdate();
	
	//カウントダウンが終わったら
	if (m_count > GAME_START_TIME)
	{
		m_time += 1;
		m_timeS += 1;
		for (int i = 0; i < GOAL_SET_NUM; i++)
		{
			//プレイヤーの移動
			if (m_goalCPUFlag[i] == true)
			{
				m_player->PlayerMove(Player::NONE);
			}
			//else if (m_hitPlayerFlag == true)
			//{
			//	//プレイヤー操作
			//	m_player->PlayerOperation(kb);
			//}
			//else if (m_hitPlayerFlag == false)
			//{
			//	//プレイヤー操作(コース外)
			//	m_player->PlayerOperationwOutSide(kb);
			//}
			//アイテム取得
			m_player->PlayerItemGet(m_itemPlayer, m_itemPlayerErase, m_itemCPU, m_itemCPUErase, m_itemFun, m_itemFunErase);
			//CPUアイテム取得
			m_cpu->CPUItemGet(m_itemCPU, m_itemCPUErase, m_itemPlayer, m_itemPlayerErase, m_itemFun, m_itemFunErase);
			//CPUの移動
			//ゴールしたら
			if (m_goalPlayerFlag[i] == true)
			{
				m_cpu->EnemyChangeAngle(Enemy::NONE);
			}
			//ゴールしてないなら
			else if (m_hitCpuFlag == true)
			{
				/*for (int i = 0; i < 6; i++)
				{
					m_cpu->CPUWarp(static_cast<Enemy::Warp>(i));
				}*/
				//CPUの方向を変えて移動させる
				m_cpu->EnemyDirection(m_box);

			}
			//下がる
			else if (m_hitCpuFlag == false)
			{
				m_cpu->EnemyChangeAngle(Enemy::BACK);
			}
			
		}
	}
	//重力
	if (m_player->GetPlayer().y >= GROUND_POSY)
	{
		m_player->PlayerMove(Player::GRAVITY);
	}

}

void ScenePlay::Render()
{
	auto context = m_deviceResources->GetD3DDeviceContext();

	GameCamera* ganeCamera = GameCamera::GetInstance();
	//追従カメラ
	// ビュー行列の作成
	Vector3 cameraPos = Vector3(0.0f, 10.0f, -20.0f); //カメラの固定する位置
	Vector3 target;

	Matrix rotY = Matrix::CreateFromQuaternion(m_player->GetRot());
	cameraPos = Vector3::Transform(cameraPos, rotY);
	target = m_player->GetPlayer();
	ganeCamera->SetTarget(target);
	ganeCamera->SetEye(target + cameraPos);
	m_view = ganeCamera->GetViewMatrix();

	//m_view = m_debugCamera->GetCameraMatrix();
	///描画///////////////////
	if (m_player->GetItemPlayer() == true)
	{
		m_effectLeafManager->Render();
	}
	if (m_player->GetItemPlayerBad() == true)
	{
		m_effectMeatManager->Render();
	}
	if (m_player->GetItemFun() == true)
	{
		m_effectFunManager->Render();
	}
	
	//プレイヤーの描画
	m_player->Render();
	//CPUの描画
	m_cpu->Render();
	//アイテムの描画
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i]->Render();
		m_itemPlayerErase[i]->Render();
		m_itemCPU[i]->Render();
		m_itemCPUErase[i]->Render();
		m_itemFun[i]->Render();
		m_itemFunErase[i]->Render();
	}
    
	//ゴールの描画
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->Render();
	}
	//当たり判定の描画
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i]->Render();
	}

	////////////////////////////
	//3Dスプライト 
	//草原
	Matrix worldPra;
	Matrix transPra = Matrix::CreateTranslation(Vector3(0.0f, -0.3f, 0.0f));
	worldPra = transPra;
	m_prairie->Draw(context, *m_states.get(), worldPra, m_view, m_projection);

	///////////////////////////////////////
	// 空
	Matrix worldSky;
	Matrix transSky = Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));
	Matrix scaleSky = Matrix::CreateScale(3.0f);
	worldSky = transSky * scaleSky;
	m_skydome->Draw(context, *m_states.get(), worldSky, m_view, m_projection);

	//2Dスプライトの描画
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());
	m_sprites->Draw(m_tLap.Get(), Vector2(550, 1));
	m_sprites->Draw(m_tHO.Get(), Vector2(15, 250));
	m_sprites->Draw(m_tKm.Get(), Vector2(10, 500));
	//ゲーム結果
	//プレイヤーがゴールしたら
	if (m_goalPlayerFlag[0] == true && m_goalPlayerFlag[1] == true && m_goalPlayerFlag[2] == true &&
		m_goalPlayerFlag[3] == true && m_goalPlayerFlag[4] == true && m_goalPlayerFlag[5] == true)
	{
		//YOU WIN!画像表示
		m_sprites->Draw(m_tPlayerGoal.Get(), Vector2(200, 200));
	}
	//CPUがゴールしたら
	else if (m_goalCPUFlag[0] == true && m_goalCPUFlag[1] == true && m_goalCPUFlag[2] == true &&
		m_goalCPUFlag[3] == true && m_goalCPUFlag[4] == true && m_goalCPUFlag[5] == true)
	{
		//YOU LOSE...画像表示
		m_sprites->Draw(m_tCPUGoal.Get(), Vector2(200, 200));
	}
	//タイム--------------------------------------
	//カウントダウン
	for (int i = 3; i > 0; i--)
	{
		if (m_count > ((i * TIME_MINUTE) - GAME_START_TIME) * -1 && m_count < 
			(((i * TIME_MINUTE) - GAME_START_TIME) * -1) + (TIME_MINUTE - 1))
		{
			m_sprites->Draw(m_tCNum[i].Get(), Vector2(380, 220));
		}
	}
	if (m_count > GAME_START_TIME && m_count < 200)
	{
		m_sprites->Draw(m_tCGo.Get(), Vector2(320, 200));
	}
	//ミリ秒
	int miri = m_time;
	//秒
	int sec = miri / TIME_MIRI;

	//分
	int min = sec / TIME_MINUTE;

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

void ScenePlay::Finalize()
{ 
	delete m_player;
	delete m_cpu;
	//delete m_root;
	delete m_effectFunManager;
	delete m_effectLeafManager;
	delete m_effectMeatManager;

	//delete m_deviceResources;

	delete m_objCreate; 
}

void ScenePlay::CreateDeviceDependentResources()
{
	//スプライトバッチの作成
	ID3D11Device* device = m_deviceResources->GetD3DDevice();
	ID3D11DeviceContext* context = m_deviceResources->GetD3DDeviceContext();

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	m_sprites = std::make_unique<SpriteBatch>(context);

	//2Dスプライトの描画素材
	CreateWICTextureFromFile(device, L"Textures\\savanna_time.png", nullptr, m_tTime.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Lap.png", nullptr, m_tLap.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Human&Datyou.png", nullptr, m_tHO.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\km.png", nullptr, m_tKm.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouWin.png", nullptr, m_tPlayerGoal.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\YouLose.png", nullptr, m_tCPUGoal.GetAddressOf());
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
	CreateWICTextureFromFile(device, L"Textures\\GO.png", nullptr, m_tCGo.GetAddressOf());
	CreateWICTextureFromFile(device, L"Textures\\Waening.png", nullptr, m_tFlipGoal.GetAddressOf());
	//数字の描画--------------------------------
	for (int i = 0; i < TIME_SET_NUM; i++)
	{
		for (int j = 0; j < TIME_TYPE_NUM; j++)
		{
			m_number[i].SetTexture(j, m_tCNum[j].Get());
		}
	}

	//-------------------------------------------
	m_objCreate = new ObjectCreate();
	m_player = new Player();
	m_cpu = new Enemy();

	RECT outputSize = m_deviceResources->GetOutputSize();
	UINT backBufferWidth = std::max<UINT>(outputSize.right - outputSize.left, 1);
	UINT backBufferHeight = std::max<UINT>(outputSize.bottom - outputSize.top, 1);
	Vector3 camera = Vector3(0, 0, -5);
	Matrix view = Matrix::CreateLookAt(camera,
		Vector3::Zero, Vector3::UnitY);
	Matrix proj = Matrix::CreatePerspectiveFieldOfView(XM_PI / 4.f,
		float(backBufferWidth) / float(backBufferHeight), 0.1f, 1000.f);
	//Player用アイテム
	m_effectLeafManager = new EffectManager();
	m_effectLeafManager->Create(m_deviceResources, L"Textures\\gameE.png", 10);
	m_effectLeafManager->InitializeCorn(0.05f, Vector3(0, 0, 0), Vector3(0, 1, 0));
	m_effectLeafManager->SetRenderState(camera, view, proj);
	//CPU用アイテム
	m_effectMeatManager = new EffectManager();
	m_effectMeatManager->Create(m_deviceResources, L"Textures\\gameB.png", 10);
	m_effectMeatManager->InitializeCorn(0.01f, Vector3(0, 0.9f, 0), Vector3(0, -1, 0));
	m_effectMeatManager->SetRenderState(camera, view, proj);
	//フンアイテム
	m_effectFunManager = new EffectManager();
	m_effectFunManager->Create(m_deviceResources, L"Textures\\gameB.png", 10);
	m_effectFunManager->InitializeCorn(0.01f, Vector3(0, 0.9f, 0), Vector3(0, -1, 0));
	m_effectFunManager->SetRenderState(camera, view, proj);

	// モデルを読み込み
	// エフェクトファクトリー 
	EffectFactory fx(device);
	// モデルのテクスチャの入っているフォルダを指定する 
	fx.SetDirectory(L"Resources\\Models");      //テクスチャ付きのcmoがある場合上に持ってくる
	
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{   //アイテム作成(プレイヤー)
		m_itemPlayer[i] = std::make_unique<Item>();
		m_itemPlayer[i]->ItemPlayerCreate(i);

		//アイテム作成(CPU)
		m_itemCPU[i] = std::make_unique<Item>();
		m_itemCPU[i]->ItemCPUCreate(i);

		//アイテム効果切れ(フン)
		m_itemFun[i] = std::make_unique<Item>();
		m_itemFun[i]->ItemFunCreate(i);

		//アイテム効果切れ(プレイヤー)
		m_itemPlayerErase[i] = std::make_unique<Item>();
		m_itemPlayerErase[i]->ItemPlayerEraseCreate(i);

		//アイテム効果切れ(CPU)
		m_itemCPUErase[i] = std::make_unique<Item>();
		m_itemCPUErase[i]->ItemCPUEraseCreate(i);

		//アイテム効果切れ(CPU)
		m_itemFunErase[i] = std::make_unique<Item>();
		m_itemFunErase[i]->ItemFunEraseCreate(i);
	}
	
	//ゴール作成
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i] = std::make_unique<Goal>();
		m_goal[i]->GoalCreate(i);
	}
	
	//床のコリジョンメッシュを作成
	m_floorMesh = std::make_unique<CollisionMesh>(device, L"Resources\\Models\\Root.obj");

	//CPUの移動用の当たり判定
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i] = std::make_unique<Root>();
		m_box[i]->EnemyHitMoveCreate(i);
	}
	GameSeter();
	//プレイヤー作成
	m_player->PlayerCreate();
	//CPU作成
	m_cpu->CPUCreate();
	
	// モデルをロードしてモデルハンドルを取得する 
	//空
	m_skydome = Model::CreateFromCMO(device, L"Resources\\Models\\savanna.cmo", fx);
	m_skydome->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});
	//地面
	m_prairie = Model::CreateFromCMO(device, L"Resources\\Models\\newSavanna.cmo", fx);
	m_prairie->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false); lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する 
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});

	
}
//
void ScenePlay::CollisionUpdate()
{
	///////////////////////////////
	//当たり判定フラグを初期化する
	m_hitPlayerFlag = false;
	m_hitCpuFlag = false;
	///当たり判定////////////
	//プレイヤーとコースの当たり判定
	static int id;
	Vector3 s;
	Vector3 playerPos = m_player->GetPlayer();
	Vector3 cpuPos = m_cpu->GetCPUPosition();
	Vector3 pV[2] = { Vector3(playerPos.x,100,playerPos.z),Vector3(playerPos.x,-1,playerPos.z) };
	Vector3 cV[2] = { Vector3(cpuPos.x,100,cpuPos.z),Vector3(cpuPos.x,-1,cpuPos.z) };
	
	if (m_floorMesh->HitCheck_Segment(pV[0], pV[1], &id, &s))
	{
		m_hitPlayerFlag = true;
		s.y -= 0.1f;
		m_player->SetPosition(s);
	}
	if (m_floorMesh->HitCheck_Segment(cV[0], cV[1], &id, &s))
	{
		m_hitCpuFlag = true;
		s.y -= 0.1f;
		m_cpu->SetPosition(s);
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
		//ゴールとプレイヤーの当たり判定をする
		if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
			, m_player->GetCollision()) == true)
		{
			if (m_checkPoint == i)
			{
				m_goalPlayerFlag[i] = true;
				m_checkPoint = i + 1;
			}
		}
		//ゴールとCPUの当たり判定をする
		if (Collision::HitCheck_Capsule2Capsule(m_goal[i]->GetCollision()
			, m_cpu->GetCollision()) == true)
		{
			m_goalCPUFlag[i] = true;
		}
	}

	m_player->SetCourseOut(!m_hitPlayerFlag);
}

void ScenePlay::GameSeter()
{
	//アイテムのゲームオブジェクトを設定
	for (int i = 0; i < ITEM_SET_NUM; i++)
	{
		m_itemPlayer[i]->SetGame(m_game);
		m_itemCPU[i]->SetGame(m_game);
		m_itemPlayerErase[i]->SetGame(m_game);
		m_itemCPUErase[i]->SetGame(m_game);
		m_itemFun[i]->SetGame(m_game);
		m_itemFunErase[i]->SetGame(m_game);
	}
	//床のゲームオブジェクトを設定
	m_floorMesh->SetGame(m_game);
	//ゴールのゲームオブジェクトを設定
	for (int i = 0; i < GOAL_SET_NUM; i++)
	{
		m_goal[i]->SetGame(m_game);
	}
	//AIルートのゲームオブジェクトを設定
	for (int i = 0; i < ENEMY_HITCHECK_NUM; i++)
	{
		m_box[i]->SetGame(m_game);
	}
	//プレイヤーのゲームオブジェクトを設定
	m_player->SetGame(m_game);
	//CPUのゲームオブジェクトを設定
	m_cpu->SetGame(m_game);
}
