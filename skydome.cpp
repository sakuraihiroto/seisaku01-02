#include "skydome.h"
#include <cassert>

MatWorld* skydomeMatworld = nullptr;

void Skydome::Initialize(Model* model) {
	assert(model);

	model_ = model;
	worldTransform_.Initialize();

	//s—ñ‚ÌŒvŽZ
	worldTransform_.matWorld_ = skydomeMatworld->CreateMatWorld(worldTransform_);
	//s—ñ‚Ì“]‘—
	worldTransform_.TransferMatrix();
}

void Skydome::Update() {}


void Skydome::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection);
}