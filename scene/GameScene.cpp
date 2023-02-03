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

	//タイトル生成
	textureHandle_title = TextureManager::Load("TD2_TITLE.png");
	sprite_title = Sprite::Create(textureHandle_title, { 0,0 });
	//操作説明生成
	textureHandle_setsumei = TextureManager::Load("setumei.png");
	sprite_setsumei = Sprite::Create(textureHandle_setsumei, { 0,0 });
	//ゲームオーバー生成
	textureHandle_gameOver = TextureManager::Load("TD2_GAMEOVER.png");
	sprite_gameOver = Sprite::Create(textureHandle_gameOver, { 0,0 });
	//クリア生成
	textureHandle_clear = TextureManager::Load("TD2_GAMECLEAR.png");
	sprite_clear = Sprite::Create(textureHandle_clear, { 0,0 });

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

	//残機の生成
	textureHandle_Hp = TextureManager::Load("robo_life.png");
	sprite_Hp = Sprite::Create(textureHandle_Hp, { 10,+10 });
	sprite_Hp_1 = Sprite::Create(textureHandle_Hp, { 30,+10 });

	//敵キャラの生成
	enemy_ = new Enemy();
	//敵キャラモデルの生成
	modelEnemy_ = Model::CreateFromOBJ("Enemy", true);
	//敵キャラの初期化
	enemy_->Initialize(modelEnemy_);

	//残機(敵)の生成
	textureHandle_enemyHp = TextureManager::Load("Enemy_life.png");
	sprite_enemyHp = Sprite::Create(textureHandle_enemyHp, { 960,+10 });
	sprite_enemyHp_1 = Sprite::Create(textureHandle_enemyHp, { 1020,+10 });
	sprite_enemyHp_2 = Sprite::Create(textureHandle_enemyHp, { 1080,+10 });
	sprite_enemyHp_3 = Sprite::Create(textureHandle_enemyHp, { 1140,+10 });
	sprite_enemyHp_4 = Sprite::Create(textureHandle_enemyHp, { 1200,+10 });

	//天球の生成
	skydome_ = new Skydome();
	//天球モデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	//天球の初期化
	skydome_->Initialize(modelSkydome_);


	//サウンドデータの読み込み
	soundPlayBGM = audio_->LoadWave("Audio/battleBGM.mp3"); //戦闘BGM
	soundGameOverBGM = audio_->LoadWave("Audio/gameover3.mp3"); //ゲームオーバーBGM
	soundClearBGM = audio_->LoadWave("Audio/clear.mp3"); //クリアBGM

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

	case 1: //操作説明  scene:1

		if (input_->TriggerKey(DIK_RETURN))
		{
			scene = 2;
		}
		break;

	case 2:  //ゲームシーン  scene:2

		if (checkSoundFlag1 == 0)
		{
			//プレイBGM再生
			voicePlayBGM = audio_->PlayWave(soundPlayBGM, true);

			checkSoundFlag1 = 1;
		}

		playerWorldPos_ = player_->GetWorldPosition();
		enemy_->SetWorldPos(playerWorldPos_);

		if (sceneFlag == 0)
		{
			//登場カメラシーン① cameraScene:0
			if (cameraScene == 0)
			{
				count1 += 0.2f;
				viewProjection_.eye.x = player_->GetX() - count1;
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
					cameraScene = 2;
					sceneFlag = 1;
				}
			}
		}
		
		if (sceneFlag == 1)
		{
			//カメラシーン③(通常)
			if (cameraScene == 2)
			{
				//ズーム
				if (input_->PushKey(DIK_U))
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
			}
			enemy_->Update();
			player_->Update();
		}
	
		player_->Mat();

		//ゲームクリアへ
		if (enemy_hp == 0)
		{
			scene = 3;
			checkSoundFlag1 = 0;
			//プレイBGM停止
			audio_->StopWave(voicePlayBGM);
		}

		//ゲームオーバーへ
		if (player_hp == 0)
		{
			scene = 4;
			checkSoundFlag1 = 0;
			//プレイBGM停止
			audio_->StopWave(voicePlayBGM);
		}
		break;

	case 3:  //ゲームクリア scene:3

		if (checkSoundFlag2 == 0)
		{
			//クリアBGM再生
			voiceClearBGM = audio_->PlayWave(soundClearBGM, true);

			checkSoundFlag2 = 1;
		}

		//敵の弾
		enemy_->ResetBullet();
		//残機
		player_hp = 2;
		enemy_hp = 5;
		//カメラカウント
		count = 0;
		count1 = 0;
		cameraScene = 0;
		sceneFlag = 0;
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene = 0; //タイトルへ

				//クリアBGM停止
			audio_->StopWave(voiceClearBGM);
			checkSoundFlag2 = 0;
		}
		break;

	default: // ゲームオーバー scene:4

		

		//敵の弾
		enemy_->ResetBullet();
		//残機
		player_hp = 2;
		enemy_hp = 5;
		//カメラカウント
		count = 0;
		count1 = 0;
		cameraScene = 0;
		sceneFlag = 0;
		if (input_->TriggerKey(DIK_SPACE))
		{
			scene = 2; //リトライ
		}
		break;
	}

	Collision();
	viewProjection_.UpdateMatrix();

}

//衝突判定
void GameScene::Collision()
{
	// 判定対象AとBとCの座標
	Vector3 posA, posB, posC, posD, posE;

	// AとBの距離
	float posAB = 0.0f;

	// 弾同士の半径
	float posR = 0.0f;
	float posR1 = 1.5f;
	float posR2 = 1.5f;

	// 自弾リストの取得
	const std::list<std::unique_ptr<PlayerBullet>>&playerBullets = player_->GetBullets();
	// 敵弾リストの取得
	const std::list<std::unique_ptr<EnemyBullet>>&enemyLaser = enemy_->GetBullets();
	// 敵弾ミサイルの取得
	const std::list<std::unique_ptr<EnemyMissile>>&enemyMissile = enemy_->GetMissiles();

#pragma region 自キャラと敵レーザーの当たり判定

	// プレイヤーと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyBullet>& bullet : enemyLaser)
	{

		//プレイヤーの座標
		posA = player_->GetWorldPosition();
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		// AB間の距離の計算
		posAB = (posB.x - posA.x) * (posB.x - posA.x) + (posB.y - posA.y) * (posB.y - posA.y) + (posB.z - posA.z) * (posB.z - posA.z);
		posR = (posR1 + posR2 - 5) * (posR1 + posR2 - 5);

		// 球と球の交差判定
		if (posAB <= posR)
		{
			// プレイヤーの衝突時コールバックを呼び出す
			player_->OnCollision(player_hp);
			// 敵弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
		}
	}

#pragma region 自キャラと敵ミサイルの当たり判定

	// プレイヤーと敵弾全ての当たり判定
	for (const std::unique_ptr<EnemyMissile>& missile : enemyMissile)
	{

		//ミサイル座標
		posE = missile->GetWorldPosition();

		// AB間の距離の計算
		posAB = (posE.x - posA.x) * (posE.x - posA.x) + (posE.y - posA.y) * (posE.y - posA.y) + (posE.z - posA.z) * (posE.z - posA.z);
		posR = (posR1 + posR2 - 5) * (posR1 + posR2 - 5);

		// 球と球の交差判定
		if (posAB <= posR)
		{
			// プレイヤーの衝突時コールバックを呼び出す
			player_->OnCollision(player_hp);
			// 敵弾の衝突時コールバックを呼び出す
			missile->OnCollision();
		}
	}

#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラと自弾全ての当たり判定
	for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {

		//敵の座標
		posC = enemy_->GetWorldPosition();
		// 自弾の座標
		posD = bullet->GetWorldPosition();
		
		// AB間の距離の計算
		posAB = (posD.x - posC.x) * (posD.x - posC.x) + (posD.y - posC.y) * (posD.y - posC.y) + (posD.z - posC.z) * (posD.z - posC.z);
		posR = (posR1 + posR2) * (posR1 + posR2);

		// 球と球の交差判定
		if (posAB <= posR)
		{
			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->OnCollision(enemy_hp);
			// 自弾の衝突時コールバックを呼び出す
			bullet->OnCollision();
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
		sprite_title->Draw();
	}

	if (scene == 1)
	{
		//操作説明
		sprite_setsumei->Draw();
	}

	if (scene == 3)
	{
		//クリア
		sprite_clear->Draw();
	}

	if (scene == 4)
	{
		//ゲームオーバー
		sprite_gameOver->Draw();
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
	if (scene == 2)
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
	if (sceneFlag == 1)
	{
		if (input_->PushKey(DIK_U))
		{
			sprite_reticle->Draw();
		}
		//残機描画

		//プレイヤー
		if (player_hp >= 1)
		{
			sprite_Hp->Draw();
		}
		if (player_hp >= 2)
		{
			sprite_Hp_1->Draw();
		}

		//敵		
		if (enemy_hp >= 1)
		{
			sprite_enemyHp->Draw();
		}
		if (enemy_hp >= 2)
		{
			sprite_enemyHp_1->Draw();
		}
		if (enemy_hp >= 3)
		{
			sprite_enemyHp_2->Draw();
		}
		if (enemy_hp >= 4)
		{
			sprite_enemyHp_3->Draw();
		}
		if (enemy_hp >= 5)
		{
			sprite_enemyHp_4->Draw();
		}
		
	}
	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

	//// デバックテキスト
	//debugText_->SetPos(60, 120);
	//debugText_->Printf(
	//	"sceneFlag(%d)", sceneFlag);

#pragma endregion
}
