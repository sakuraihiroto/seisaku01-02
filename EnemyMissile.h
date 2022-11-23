#pragma once
#include"Model.h"
#include"matWorld.h"
#include"MathUtility.h"
#include"player.h"

using namespace MathUtility;

class EnemyMissile
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="position">初期座標</param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);

	bool IsDead()const { return isDead_; }

	Vector3 GetLen(Vector3& len);
	//void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();
	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision();
private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	WorldTransform worldTransform_2;
	//モデルのポインタ
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//速度
	Vector3 velocity_;

	Vector3 len_;

	Vector3 playerWP;

	MatWorld* enemyMatworld = nullptr;

	Player* player_ = nullptr;


	int upTimer = 60;
	int timer = 0;
	//寿命
	static const int32_t kLifeTime = 60 * 5;
	//デスタイマー
	int32_t deathTimer_ = kLifeTime;
	//デスフラグ
	bool isDead_ = false;
};