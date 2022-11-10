#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include "matWorld.h"

class Skydome
{

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection viewProjection);

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル

	//モデル
	Model* model_ = nullptr;
	
};

