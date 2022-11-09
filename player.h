#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "matWorld.h"
#include <assert.h>
#include<memory>
#include<list>

class Player
{
public:
	///<summary>
	///������
	/// </summary>
	/// <pragma name="model">���f��</param>
	/// <pragma name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model);

	///<summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="">�r���[�v���W�F�N�V����</param>
	void Draw(ViewProjection& viewProjection_);

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˔���
	void OnCollision(int& hp);

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// ���͏������邽��
	Input* input_ = nullptr;
	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	Model* modelPlayerBullet_ = nullptr;	

};