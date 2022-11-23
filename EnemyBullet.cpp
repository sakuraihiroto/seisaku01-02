#include"EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(const Vector3& position, const Vector3& velocity)
{
	//nullポインタチェック
	//assert(model);

	model_ = Model::Create();
	//model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("enemyBulletP.png");

	//ワールド変換の初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

	//引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	velocity_ *= -1.0f;
}

void EnemyBullet::Update()
{
	//行列の計算
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);
	//ワールド行列を転送
	worldTransform_.TransferMatrix();

	//座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
Vector3 EnemyBullet::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動成分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	//worldPos = worldTransform_.translation_;
	return worldPos;
}
void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
