#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include <cassert>
#include <math.h>

MatWorld* matworld_ = nullptr;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete enemy_;
	delete modelSkydome_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//レティクルの生成
	textureHandle_reticle = TextureManager::Load("reticle.png");
	sprite_reticle = Sprite::Create(textureHandle_reticle, { 0,+10 });

	//3Dモデルの生成
	model_ = Model::Create();

	//自キャラの生成
	player_ = new Player();
	//自キャラモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);
	//自キャラの初期化
	player_->Initialize(modelPlayer_);

	//敵キャラの生成
	enemy_ = new Enemy();
	//敵キャラモデルの生成
	modelEnemy_ = Model::CreateFromOBJ("Enemy_Proto", true);
	//敵キャラの初期化
	enemy_->Initialize(modelEnemy_);

	//天球の生成
	skydome_ = new Skydome();
	//天球モデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//天球の初期化
	skydome_->Initialize(modelSkydome_);

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//視点移動
	viewProjection_.UpdateMatrix();

}

void GameScene::Update() {

	switch (scene)
	{
	case 0:  //タイトル  scene:0

		if (input_->TriggerKey(DIK_SPACE))
		{
			scene = 1;
		}
		break;

	case 1:  //ゲームシーン  scene:1

		playerWorldPos_ = player_->GetWorldPosition();
		enemy_->SetWorldPos(playerWorldPos_);

		//登場ムービーしているとき
		if (sceneFlag == 0)
		{
			//登場カメラシーン① cameraScene:0
			if (cameraScene == 0)
			{
				count1 += 0.2f;
				viewProjection_.eye.x = player_->GetX()-count1;
				viewProjection_.eye.y = player_->GetY();
				viewProjection_.eye.z = -30;
				if (count1 > 80)
				{
					count1 = 80;
					cameraScene = 1;
				}
			}

			//登場カメラシーン② cameraScene:1
			if (cameraScene == 1)
			{
				count += 0.2f;
				viewProjection_.eye.z = count;

				viewProjection_.eye.x = player_->GetX() - 20;
				viewProjection_.eye.y = player_->GetY() + 10;

				viewProjection_.target.x = player_->GetX();
				viewProjection_.target.y = player_->GetY() + 7;

				if (count > 80)
				{
					count = 80;
					sceneFlag = 1;
				}
			}
		}

		//登場ムービーが終わった時
		if (sceneFlag == 1)
		{
			//ズーム
			if (input_->PushKey(DIK_O))
			{
				viewProjection_.eye.x = player_->GetX();
				viewProjection_.eye.y = player_->GetY();
				viewProjection_.eye.z = player_->GetZ();

				viewProjection_.target.x = player_->GetX();
				viewProjection_.target.y = player_->GetY() + 1.5f;
			}
			//通常時
			else
			{
				viewProjection_.eye.x = player_->GetX() - 20;
				viewProjection_.eye.y = player_->GetY() + 10;
				viewProjection_.eye.z = player_->GetZ() + 30;

				viewProjection_.target.x = player_->GetX();
				viewProjection_.target.y = player_->GetY() + 7;
			}
			player_->Attack();
			enemy_->Update();
		}
		player_->Update();
		
	}
	viewProjection_.UpdateMatrix();
}


//衝突判定
void GameScene::Collision()
{
	CollisionPlayerEnamy();
}

//衝突判定(プレイヤーと敵)
void GameScene::CollisionPlayerEnamy()
{
	Vector3 posP, posE;

	posP = player_->GetWorldPosition();
	posE = enemy_->GetWorldPosition();

	//敵がいれば
	if (enemyFlag == 1)
	{
		//差を求める
		float dx = abs(posP.x - posE.x);
		float dz = abs(posP.y - posE.y);

		//衝突したら
		if (dx < 1 && dz < 1)
		{
			enemyFlag = 0;
		}
	}
}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	if (scene == 0)
	{
		//タイトル
	}

	if (scene == 2)
	{
		//クリア
	}

	if (scene == 3)
	{
		//ゲームオーバー
	}

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();


#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	


	//ゲームシーン
	if (scene == 1)
	{
		//天球の描画
		skydome_->Draw(viewProjection_);

		//自キャラの描画
		player_->Draw(viewProjection_);

		//敵キャラの描画
		enemy_->Draw(viewProjection_);
	}


	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	//ズーム描画
	if (input_->PushKey(DIK_O) && sceneFlag == 1)
	{
		sprite_reticle->Draw();
	}
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	//デバックテキスト
	debugText_->SetPos(50, 120);
	debugText_->Printf(
		"eye(X:%f)(Y:%f)(Z:%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	//デバックテキスト
	debugText_->SetPos(50, 140);
	debugText_->Printf(
		"scene(%d)", scene);

	//デバックテキスト
	debugText_->SetPos(50, 160);
	debugText_->Printf(
		"count1(%f)", count1);
	
	//デバックテキスト
	debugText_->SetPos(50, 180);
	debugText_->Printf(
		"count(%f)", count);

	//デバックテキスト
	debugText_->SetPos(50, 200);
	debugText_->Printf(
		"camerascene(%d)", cameraScene);
	//


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
