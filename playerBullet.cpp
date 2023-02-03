#include "playerBullet.h"
#include <assert.h>

MatWorld* bulletMatworld = nullptr;

void PlayerBullet::Initialize(Model* model, const Vector3& position)
{

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	debugText_ = DebugText::GetInstance();

}

//���[���h���W������ϐ�
Vector3 PlayerBullet::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void PlayerBullet::Update(Vector3& velocity, bool& shootFlag)
{
	if (--deathTimer_ <= 0)
	{
		isDead_ = true;
	}


	// �����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;

	// ���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;

	//�s��̌v�Z
	worldTransform_.matWorld_ = bulletMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();

}

//�Փ˔���
void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

//�`�揈��
void PlayerBullet::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}