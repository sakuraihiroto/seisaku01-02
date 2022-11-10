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
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e�N�X�`���n���h��

	//���f��
	Model* model_ = nullptr;
	
};

