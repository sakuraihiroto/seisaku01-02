#include "enemy.h"

MatWorld* enemyMatworld = nullptr;

//接近フェーズ
void Enemy::Approach(float& appSpeed)
{
	
}

void Enemy::Initialize(Model* model) {

	//NULLポインタチェック
	assert(model);

	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	//キャラクターの移動ベクトル
	Vector3 move = { 0,10,-50 };//座標{x,y,z}

	//初期座標をセット
	worldTransform_.translation_ = move;

}

Vector3 Enemy::GetWorldPosition()
{
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Update()
{
	
	//行列の計算
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//行列の転送
	worldTransform_.TransferMatrix();

}

//衝突判定
void Enemy::OnCollision(int& deadEnemyNum)
{
	isDead_ = true;
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection);
}