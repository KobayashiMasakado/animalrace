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

	// ゲームカメラ
	std::unique_ptr<GameCamera> m_gameCamera;

	// キーボード
	std::unique_ptr<DirectX::Keyboard> m_keyboard;

	//// スプライトバッチ
	//std::unique_ptr<DirectX::SpriteBatch> m_sprites;

	//3Dスプライト///////////////////////////////////////////
	//空
	std::unique_ptr<DirectX::Model> m_skydome;

	// 草原
	std::unique_ptr<DirectX::Model> m_prairie;

	ObjectCreate* m_objCreate;

	//プレイヤー
	Player* m_player;
	//std::unique_ptr<DirectX::Model> m_itemPlayerModel;
	//CPU
	Enemy* m_cpu;
//	std::unique_ptr<DirectX::Model> m_itemCPUModel;

	std::unique_ptr<CollisionCapsule> m_box[ENEMY_HITCHECK_NUM];
	std::unique_ptr<DirectX::Model> m_boxModel[ENEMY_HITCHECK_NUM];

	//Root* m_root;
	//道のモデル
	std::unique_ptr<DirectX::Model> m_rootModel;
	//ゴール
	std::unique_ptr<Goal> m_goal[GOAL_SET_NUM];
	std::unique_ptr<DirectX::Model> m_goalModel;
	//アイテム
	//プレイヤー用
	std::unique_ptr<Item> m_itemPlayer[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemPlayerModel;
	//CPU用
	std::unique_ptr<Item> m_itemCPU[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemCPUModel;
	//アイテム解除
	//プレイヤー用
	std::unique_ptr<Item> m_itemPlayerErase[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemPlayerEraseModel;
	//CPU用
	std::unique_ptr<Item> m_itemCPUErase[ITEM_SET_NUM];
	std::unique_ptr<DirectX::Model> m_itemCPUEraseModel;
	//2Dスプライト/////////////////////////////
	//テクスチャハンドル
	//制限時間
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tTime;
	//周回
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tLap;
	//スピードメーター
	//キャラ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tHO;
	//キロメートル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tKm;
	//GOAL!!
	//プレイヤー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tPlayerGoal;
	//CPU
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCPUGoal;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tFlipGoal;;
	//カウントダウン
	//GO!
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCGo;
	//数字
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_tCNum[TIME_TYPE_NUM];

	Number m_number[TIME_SET_NUM];

	//タイム
	int m_time;
	int m_timeS;
	//衝突したかどうか判定
	bool m_hitPlayerFlag;
	bool m_hitCpuFlag;

	//ゴールに辿り着いたかどうか判定
	bool m_goalPlayerFlag[GOAL_SET_NUM];
	bool m_goalCPUFlag[GOAL_SET_NUM];
	
	//アイテム取得
	bool m_itemPlayerCheck;
	bool m_itemCPUCheck;

	bool m_itemPlayerBadCheck;
	bool m_itemCPUBadCheck;

	//カウントダウン
	int m_count;
	//アイテム
	//int m_itemCount;
	
	//ゴールのチェックポイント
	int m_checkPoint;

	//タスクマネージャー
	TaskManager m_taskManager;

	std::unique_ptr<CollisionMesh> m_floorMesh;

	
public:
	//初期化
	void Initialize() override;
	//更新
	void Update(float elapsedTime) override;
	//描画
	void Render() override;

	void Finalize() override { delete m_objCreate; }
	void CreateDeviceDependentResources();

	//プレイヤー操作
	void PlayerOperation(DirectX::Keyboard::State &kb);

	//プレイヤー操作(コース外)
	void PlayerOperationwOutSide(DirectX::Keyboard::State &kb);

	//コースとキャラの当たり判定
	void HitCourseCheck();

	//ゴールとキャラの当たり判定
	void HitGoalCheck();

	//アイテム取得
	//プレイヤー用
	void PlayerItemGet();
	//CPU用
	void CPUItemGet();

	//カウントダウン
	void CountDownStart();

	//レース結果
	void RaceEnd();

	//ゲームをSet
	void SetGame2();

	//CPUの角度を変える
	void EnemyDirection();;

	
	//アイテム作成(CPU)
	void ItemCPUCreate();
	//アイテム効果切れ(CPU)
	void ItemCPUEraseCreate();
	//コース作成
	void CourseCreate();
	//ゴール作成
	void GoalCreate();
	//CPUの移動用の当たり判定
	void EnemyHitMoveCreate();

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