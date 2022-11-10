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

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ワールド変換の初期化
	worldTransform_.Initialize();

	//キャラクターの移動ベクトル
	Vector3 move = { 0,0,0 };//座標{x,y,z}

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

//プレイヤーの攻撃処理
void Player::Attack()
{
	//スペースを押したら撃つ
	if (input_->TriggerKey(DIK_SPACE))
	{
		if (shootFlag == 0)
		{
			//弾を生成し、初期化
			std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(modelPlayerBullet_, worldTransform_.translation_);

			//弾を登録する
			bullets_.push_back(std::move(newBullet));

			shootFlag = 1; //発射フラグ		
		}
		if (shootFlag == 1)
		{
			shootFlag = 0;
		}
	}
}


//アップデート
void Player::Update()
{

	//キャラクターの移動ベクトル
	Vector3 move = { 0, 0, 0 };

	// 平行移動
	{ // X方向
		if (input_->PushKey(DIK_A)) {
			move.x += 0.1f;
		}
		else if (input_->PushKey(DIK_D)) {
			move.x -= 0.1f;
		}
		// Y方向
		if (input_->PushKey(DIK_W)) {
			move.y += 0.1f;
		}
		else if (input_->PushKey(DIK_S)) {
			move.y -= 0.1f;
		}
		// Z方向
		if (input_->PushKey(DIK_3)) {
			move.z = 0.1f;
		}
		else if (input_->PushKey(DIK_4)) {
			move.z = -0.1f;
		}
	}

	worldTransform_.translation_ += move;


	// 回転ベクトル
	Vector3 rotate = { 0, 0, 0 };

	{ // X方向
		if (input_->PushKey(DIK_Q)) {
			rotate.x = 1;
		}
		else if (input_->PushKey(DIK_E)) {
			rotate.x = -1;
		}
		// Y方向
		if (input_->PushKey(DIK_1)) {
			rotate.y = 1;
		}
		else if (input_->PushKey(DIK_2)) {
			rotate.y = -1;
		}
	}

	worldTransform_.rotation_ += rotate;

	//弾の位置
	

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
	model_->Draw(worldTransform_, viewProjection_);

	// 弾の描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}
