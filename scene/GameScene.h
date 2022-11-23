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
	void CollisionPlayerEnamy();


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

	//スプライト
	Sprite* sprite_reticle = nullptr; //レティクル

	//3Dモデル
	Model* model_ = nullptr;
	Model* modelPlayer_ = nullptr; //プレイヤーモデル
	Model* modelEnemy_ = nullptr; //敵モデル
	Model* modelSkydome_ = nullptr; //背景

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//自キャラ
	Player* player_ = nullptr;
	//敵キャラ
	Enemy* enemy_ = nullptr;
	//敵キャラフラグ
	int enemyFlag = 0;
	// 天球
	Skydome* skydome_ = nullptr;
	//カメラカウント
	float count = 0.0f;
	float count1 = 0.0f;
	//カメラフラグ
	int cameraFlag = 0;
	int cameraFlag1 = 0;
	//シーン
	int scene = 0;
	int sceneFlag = 0;
	//カメラシーン
	int cameraScene = 0;

	Vector3 playerWorldPos_;
	
};
