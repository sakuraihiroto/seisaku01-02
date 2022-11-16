#include "GameScene.h"
#include "TextureManager.h"
#include "matWorld.h"
#include <cassert>

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
	modelEnemy_ = Model::CreateFromOBJ("bat_TD2", true);
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

	player_->Update();
	enemy_->Update();

	//マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition);

	//クライアントエリア座標に変換する
	HWND hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition);

	//視点移動
	
	viewProjection_.eye.x = mousePosition.x/100;
	viewProjection_.eye.y = mousePosition.y/100;
	
	viewProjection_.target.x = player_->GetX();
	viewProjection_.target.y = player_->GetY() + 6.5f;

	////範囲を超えない処理
	//viewProjection_.eye.x = max(viewProjection_.eye.x, -40.0f);
	//viewProjection_.eye.x = min(viewProjection_.eye.x, +40.0f);
	//viewProjection_.eye.y = max(viewProjection_.eye.y, -40.0f);
	//viewProjection_.eye.y = min(viewProjection_.eye.y, +40.0f);


	if (input_->PushKey(DIK_Q)) 
	{
		viewProjection_.eye.z = player_->GetZ() - 30;
	}
	else
	{
		viewProjection_.eye.z = player_->GetZ() + 10;
	}
	viewProjection_.UpdateMatrix();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

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

	//天球の描画
	skydome_->Draw(viewProjection_);

	//自キャラの描画
	player_->Draw(viewProjection_);

	//敵キャラの描画
	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);

	//デバックテキスト
	debugText_->SetPos(50, 120);
	debugText_->Printf(
		"eye(X:%f)(Y:%f)(Z:%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);

	debugText_->SetPos(50, 160);
	debugText_->Printf(
		"mouse(X:%f)(Y:%f)", mousePosition.x, mousePosition.y);
	//


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
