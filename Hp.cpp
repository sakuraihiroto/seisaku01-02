#include "Hp.h"

MatWorld* HpMatWorld = nullptr;

void Hp::Initialize(Model* model, const Vector3& position)
{
	//NULLポインタチェック
	assert(model);

	model_ = model;

	//ワールド変換の初期化
	worldTransform_.Initialize();

	//初期座標をセット
	worldTransform_.translation_ = position;

}

void Hp::Update()
{
	//行列の計算
	worldTransform_.matWorld_ = HpMatWorld->CreateMatWorld(worldTransform_);
	//行列の転送
	worldTransform_.TransferMatrix();
}

void Hp::Draw(ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}