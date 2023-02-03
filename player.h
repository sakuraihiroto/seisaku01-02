#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "matWorld.h"
#include <assert.h>
#include<memory>
#include<list>
#include "playerBullet.h"
#include "ViewProjection.h"

class Player
{
public:

	enum class action
	{
		待つ,
		左,
		右,
		前,
		後ろ,
		攻撃,
	};

	///<summary>
	///初期化
	/// </summary>
	/// <pragma name="model">モデル</param>
	/// <pragma name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model);

	///<summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="">ビュープロジェクション</param>
	void Draw(ViewProjection& viewProjection_);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	// 弾リストを取得
	const std::list < std::unique_ptr<PlayerBullet >>& GetBullets() { return bullets_; }

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//衝突判定
	void OnCollision(int& hp);
	//行列の計算と転送
	void Mat();

	//プレイヤーの座標
	float GetX() { return worldTransform_.translation_.x; }
	float GetY() { return worldTransform_.translation_.y; }
	float GetZ() { return worldTransform_.translation_.z; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
	// モデル
	Model* model_ = nullptr;
	Model* modelPlayerBullet_ = nullptr;
	Model* modelPlayerShoot_ = nullptr;
	Model* modelPlayerFront_ = nullptr;
	Model* modelPlayerBack_ = nullptr;
	Model* modelPlayerLeft_ = nullptr;
	Model* modelPlayerRight_ = nullptr;


	//方向
	action action = action::待つ;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 入力処理するため
	Input* input_ = nullptr;
	//弾
	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	PlayerBullet* playerBullet_ = nullptr;
	// デバッグテキスト
	DebugText* debugText_ = nullptr;

	const int32_t cShootTimer = 60;
	int32_t shootTimer = cShootTimer;

	//発射フラグ
	bool shootFlag = 0;
	//タイマー
	float timer = 0;
	//速度
	Vector3 velocity_;
	//弾の速度
	float kBulletSpeed = 1.0f; //スピード


};