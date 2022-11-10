#include "skydome.h"
#include <cassert>

MatWorld* skydomeMatworld = nullptr;

void Skydome::Initialize(Model* model) {
	assert(model);

	model_ = model;
	worldTransform_.Initialize();

	//�s��̌v�Z
	worldTransform_.matWorld_ = skydomeMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Skydome::Update() {}


void Skydome::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}