#include "player.h"

// アフィン行列呼び出し
MatWorld* playerMatworld = nullptr;


//初期化処理
void Player::Initialize(Model* model)
{
	// NULLポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;

	//自キャラの弾モデルの生成
	modelPlayerBullet_ = Model::CreateFromOBJ("bullet", true);
	modelPlayerShoot_ = Model::CreateFromOBJ("robo_shoot", true);
	modelPlayerFront_ = Model::CreateFromOBJ("robo_front", true);
	modelPlayerBack_ = Model::CreateFromOBJ("robo_back", true);
	modelPlayerLeft_ = Model::CreateFromOBJ("robo_left", true);
	modelPlayerRight_ = Model::CreateFromOBJ("robo_right", true);



	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,50 };//座標{x,y,z}

	//初期座標をセット
	worldTransform_.translation_ = move;

}

//ワールド座標を入れる変数
Vector3 Player::GetWorldPosition()
{
	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列の平行移動分を取得
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//衝突判定
void Player::OnCollision(int& hp)
{
	hp -= 1;
}

void Player::Mat()
{
	//行列の計算
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();
}

//プレイヤーの攻撃処理
void Player::Attack()
{
	//スペースを押したら撃つ
	if (input_->TriggerKey(DIK_SPACE))
	{

		//弾を生成し、初期化
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelPlayerBullet_, worldTransform_.translation_);

		//弾を登録する
		bullets_.push_back(std::move(newBullet));


	}
	/*if (shootFlag == true)
	{
		shootTimer--;
		action = action::攻撃;
	}
	if (shootTimer <= 0)
	{
		shootTimer = cShootTimer;
		shootFlag = false;
	}*/
}


//アップデート
void Player::Update()
{
	//弾の位置
	velocity_.z = -kBulletSpeed;

	//キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	action = action::攻撃;
	// 平行移動
	{ // X方向
		if (input_->PushKey(DIK_A)) {
			move.x += 0.2f;
			action = action::左;
		}
		else if (input_->PushKey(DIK_D)) {
			move.x -= 0.2f;
			action = action::右;
		}
		// Z方向
		if (input_->PushKey(DIK_W)) {
			move.y += 0.2f;
			action = action::前;

		}
		else if (input_->PushKey(DIK_S)) {
			move.y -= 0.2f;
			action = action::後ろ;
		}
	}

	worldTransform_.translation_ += move;

	//デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//行列の計算
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();

	Attack();

	// 弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update(velocity_, shootFlag);
	}
}



//描画処理
void Player::Draw(ViewProjection& viewProjection_)
{
	switch (action)
	{
	case action::待つ:
		model_->Draw(worldTransform_, viewProjection_);
		break;
	case action::左:
		modelPlayerLeft_->Draw(worldTransform_, viewProjection_);
		break;
	case action::右:
		modelPlayerRight_->Draw(worldTransform_, viewProjection_);
		break;
	case action::前:
		modelPlayerFront_->Draw(worldTransform_, viewProjection_);
		break;
	case action::後ろ:
		modelPlayerBack_->Draw(worldTransform_, viewProjection_);
		break;
	default:
		modelPlayerShoot_->Draw(worldTransform_, viewProjection_); break;
	}

	// 弾の描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}
