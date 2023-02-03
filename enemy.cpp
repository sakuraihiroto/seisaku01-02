#include "enemy.h"



//移動フェーズ
void Enemy::Move(float& appSpeed)
{

}

void Enemy::Initialize(Model* model) {

	//NULLポインタチェック
	assert(model);

	model_ = model;
	missileModel_ = Model::CreateFromOBJ("missile", true);

	//敵のHPの初期化
	//Hp = 5;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,-50 };//座標{x,y,z}

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
	if (Hp < 3)
	{
		isPhase2_ = true;
	}

	// デスフラグの立った弾を解除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		}
	);
	// デスフラグの立った弾を解除
	missiles_.remove_if([](std::unique_ptr<EnemyMissile>& missile)
		{
			return missile->IsDead();
		}
	);

	// 敵キャラのワールド座標を取得
	Vector3 enemyWP = GetWorldPosition();

	// 敵キャラ、自キャラの差分ベクトル
	len = enemyWP - playerWP;

	// ベクトルの正規化
	len = MathUtility::Vector3Normalize(len);

	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->GetLen(playerWP);
	}

	// 発射タイマーカウントダウン
	fireTimer--;
	LaserTimer--;
	//敵の弱点カウントダウン
	weakTimer--;
	if (weakTimer < 0)
	{
		isWeak_ = true;
	}

	//敵がフェーズ2の時
	if (isPhase2_ == true)
	{
		// 指定時間に達した
		if (LaserTimer < 0 && LaserNum > 0)
		{
			// 弾を発射
			Laser();
			Missile();
			LaserNum--;
			// 発射タイマーを初期化
			LaserTimer = 20;// 1/3秒
			fireTimer = 60;//1秒
		}
		if (fireTimer < 0)
		{
			LaserNum = 3;
		}
	}
	//敵がフェーズ1の時
	if (isPhase2_ == false)
	{
		missileTimer--;
		// 指定時間に達した
		if (fireTimer < 0)
		{
			// 弾を発射
			Laser();
			missileTimer = 40;
			// 発射タイマーを初期化
			fireTimer = kFireInterval;
		}
		if (missileTimer < 0)
		{
			Missile();
			missileTimer = 40;
		}
	}
	// レーザー更新
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}
	// ミサイル更新
	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->Update();
	}

	//行列の計算
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//行列の転送
	worldTransform_.TransferMatrix();
}

void Enemy::Laser()
{
	
	// 弾を生成し、初期化
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(worldTransform_.translation_, len);

	// 弾を登録する
	bullets_.push_back(std::move(newBullet));
}

void Enemy::Missile()
{
	// 弾を生成し、初期化
	std::unique_ptr<EnemyMissile> newMissile = std::make_unique<EnemyMissile>();
	newMissile->Initialize(missileModel_, worldTransform_.translation_);

	// 弾を登録する
	missiles_.push_back(std::move(newMissile));
}

void Enemy::ResetBullet()
{
	for (std::unique_ptr<EnemyBullet>& laser : bullets_)
	{
		laser->OnCollision();
	}
	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->OnCollision();
	}

	// デスフラグの立った弾を解除
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		}
	);
	// デスフラグの立った弾を解除
	missiles_.remove_if([](std::unique_ptr<EnemyMissile>& missile)
		{
			return missile->IsDead();
		}
	);
}


//衝突判定
void Enemy::OnCollision(int& hp)
{
	if (isWeak_)
	{
		hp -= 1;
		isWeak_ = false;
		weakTimer = 300;
	}
	if (hp < 3)
	{
		isPhase2_ = true;
	}
	if (hp <= 0)
	{
		isDead_ = true;
	}
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	//モデルの描画
	model_->Draw(worldTransform_, viewProjection);
	// 弾の描画
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}
	// ミサイルの描画
	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->Draw(viewProjection);
	}
}