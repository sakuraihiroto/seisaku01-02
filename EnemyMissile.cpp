#include "EnemyMissile.h"
#include <cassert>

void EnemyMissile::Initialize(Model* model, const Vector3& position)
{
	//nullポインタチェック
	//assert(model);

	//model_ = Model::Create();
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("uvChecker.png");

	//ワールド変換の初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;

}

void EnemyMissile::Update()
{
	worldTransform_2 = worldTransform_;

	//行列の計算
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);
	//ワールド行列を転送
	worldTransform_.TransferMatrix();
	//上昇
	upTimer--;
	if (upTimer >= 0)
	{
		velocity_ = { 0,0.2f,0 };
	}
	else
	{
		timer++;

	}
	if (timer <= 60 && upTimer < 0)
		// 敵キャラのワールド座標を取得
	{
		Vector3 enemyWP = GetWorldPosition();

		// 敵キャラ、自キャラの差分ベクトル
		len_ = enemyWP - playerWP;

		// ベクトルの正規化
		len_ = MathUtility::Vector3Normalize(len_) / 1.5;
		len_ *= -1.0f;
		velocity_ = len_;
	}

	//座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ += velocity_;
	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
Vector3 EnemyMissile::GetWorldPosition()
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

Vector3 EnemyMissile::GetLen(Vector3& playerWP)
{
	return this->playerWP = playerWP;
}

void EnemyMissile::OnCollision()
{
	isDead_ = true;
}

void EnemyMissile::Draw(const ViewProjection& viewProjection)
{
	//モデルの描画
	model_->Draw(worldTransform_2, viewProjection);
}