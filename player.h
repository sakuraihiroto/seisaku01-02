#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "Input.h"
#include "DebugText.h"
#include "matWorld.h"
#include <assert.h>
#include<memory>
#include<list>
#include "playerBullet.h"
#include "ViewProjection.h"

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

	// �e���X�g���擾
	const std::list < std::unique_ptr<PlayerBullet >>& GetBullets() { return bullets_; }

	//���[���h���W���擾
	Vector3 GetWorldPosition();

	//�Փ˔���
	void OnCollision(int& hp);

	//�v���C���[�̍��W
	float GetX() { return worldTransform_.translation_.x; }
	float GetY() { return worldTransform_.translation_.y; }
	float GetZ() { return worldTransform_.translation_.z; }

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�r���[�v���W�F�N�V����
	ViewProjection viewProjection_;
	// ���f��
	Model* model_ = nullptr;
	Model* modelPlayerBullet_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	// ���͏������邽��
	Input* input_ = nullptr;
	//�e
	std::list<std::unique_ptr<PlayerBullet>>bullets_;
	PlayerBullet* playerBullet_ = nullptr;
	// �f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;

	//���˃t���O
	bool shootFlag = 0;
	//�^�C�}�[
	float timer = 0;
	//���x
	Vector3 velocity_;
	//�e�̑��x
	float kBulletSpeed= 1.0f; //�X�s�[�h
	

};