#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "Skydome.h"
#include"DebugCamera.h"
#include "WinApp.h"
#include <stdlib.h>
#include "Hp.h"
#include "EnemyMissile.h"
#include "EnemyBullet.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定
	/// </summary>
	void Collision();

	/// <summary>
	/// 衝突判定(プレイヤーと敵)
	/// </summary>
	


  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	//テクスチャハンドル
	uint32_t textureHandle_reticle = 0; //レティクル
	uint32_t textureHandle_Hp = 0; //残機(プレイヤー)
	uint32_t textureHandle_enemyHp = 0; //残機(敵)

	uint32_t textureHandle_title = 0; //タイトル
	uint32_t textureHandle_setsumei = 0; //操作説明
	uint32_t textureHandle_gameOver = 0; //ゲームオーバー
	uint32_t textureHandle_clear = 0; //クリア

	//スプライト
	Sprite* sprite_reticle = nullptr; //レティクル
	Sprite* sprite_Hp = nullptr; //残機	(プレイヤー)
	Sprite* sprite_Hp_1 = nullptr; //残機1(プレイヤー)
	Sprite* sprite_enemyHp = nullptr; //残機 (敵)
	Sprite* sprite_enemyHp_1 = nullptr; //残機1 (敵)
	Sprite* sprite_enemyHp_2 = nullptr; //残機2 (敵)
	Sprite* sprite_enemyHp_3 = nullptr; //残機3 (敵)
	Sprite* sprite_enemyHp_4 = nullptr; //残機4 (敵)

	Sprite* sprite_title = nullptr; //タイトル
	Sprite* sprite_setsumei = nullptr; //操作説明
	Sprite* sprite_gameOver = nullptr; //ゲームオーバー
	Sprite* sprite_clear = nullptr; //クリア

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr; //プレイヤーモデル
	Model* modelEnemy_ = nullptr; //敵モデル
	Model* modelSkydome_ = nullptr; //背景

	//サウンド
	uint32_t soundTitleBGM = 0; //タイトルBGM
	uint32_t soundPlayBGM = 0; //プレイBGM
	uint32_t soundGameOverBGM = 0; //ゲームオーバーBGM
	uint32_t soundClearBGM = 0; //クリアBGM

	uint32_t voiceTitleBGM = 0; //音声再生ハンドル
	uint32_t voicePlayBGM = 0;
	uint32_t voiceGameOverBGM = 0;
	uint32_t voiceClearBGM = 0;

	int checkSoundFlag = 0;    //サウンドフラグ 
	int checkSoundFlag1 = 0;
	int checkSoundFlag2 = 0;
	int checkSoundFlag3 = 0;


	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;
	//自キャラの弾
	PlayerBullet* playerBullet_ = nullptr;
	//敵キャラ
	Enemy* enemy_ = nullptr;
	//敵キャラの弾①
	EnemyBullet* enemyBullet_ = nullptr;
	//敵キャラの弾②
	EnemyMissile* enemyMissile_ = nullptr;

	// 天球
	Skydome* skydome_ = nullptr;
	//カメラカウント
	float count = 0.0f;
	float count1 = 0.0f;
	//シーン
	int scene = 0;
	int sceneFlag = 0;
	//カメラシーン
	int cameraScene = 0;	

	//敵の残機
	int enemy_hp = 5;
	//プレイヤーの残機
	int player_hp = 2;

	Vector3 playerWorldPos_;
	
	//デバックテキスト用
	int a = 0;
	
};
