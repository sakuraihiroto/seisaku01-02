#pragma once
#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Model.h"
#include"matWorld.h"
#include <assert.h>

class Hp
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model"></param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection& viewProjection);
private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
