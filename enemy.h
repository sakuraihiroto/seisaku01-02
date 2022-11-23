#pragma once

#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Model.h"
#include"matWorld.h"
//#include"player.h"
#include"EnemyBullet.h"
#include"EnemyMissile.h"

//前方宣言
class Player;

class Enemy
{
public:

	//行動フェーズ
	enum class Phase
	{
		Move,	//接近する
		Leave,		//離脱する
	};
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// レーザー攻撃
	/// </summary>
	void Laser();

	/// <summary>
	/// ミサイル攻撃
	/// </summary>
	void Missile();

	//移動
	void Move(float& appSpeed);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	//衝突判定
	void OnCollision(int& deadEnemyNum);

	void SetPlayer(Player* player) { player_ = player; }

	void SetWorldPos(Vector3 worldPos) { playerWP = worldPos; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

	//発射間隔
	static const int kFireInterval = 60;

	//弾リストを取得
	const std::list<std::unique_ptr<EnemyMissile>>& GetMissiles() { return missiles_; }

	//弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
private:

	//自キャラ
	Player* player_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	Model* missileModel_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//フェーズ
	Phase phase_ = Phase::Move;
	//速度
	Vector3 velocity_;

	Vector3 len;

	Vector3 playerWP;

	MatWorld* enemyMatworld = nullptr;

	//弾
	std::list < std::unique_ptr< EnemyBullet >> bullets_;
	//ミサイル
	std::list < std::unique_ptr< EnemyMissile >> missiles_;

	//デスフラグ
	int Hp = 5;
	bool isDead_ = false;

	//ボスフェーズ2
	bool isPhase2_ = false;

	//発射タイマー
	int32_t fireTimer = 0;
	int32_t fireTimer2 = 0;
	int32_t missileTimer = 40;
	int32_t LaserTimer = 10;
	int32_t LaserNum = 3;

};