#include "EnemyMissile.h"
#include <cassert>

void EnemyMissile::Initialize(Model* model, const Vector3& position)
{
	//null�|�C���^�`�F�b�N
	//assert(model);

	//model_ = Model::Create();
	model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("uvChecker.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

}

void EnemyMissile::Update()
{
	worldTransform_2 = worldTransform_;

	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);
	//���[���h�s���]��
	worldTransform_.TransferMatrix();
	//�㏸
	upTimer--;
	if (upTimer >= 0)
	{
		velocity_ = { 0,0.2f,0 };
	}
	else
	{
		timer++;

	}
	if (timer <= 60 && upTimer < 0)
		// �G�L�����̃��[���h���W���擾
	{
		Vector3 enemyWP = GetWorldPosition();

		// �G�L�����A���L�����̍����x�N�g��
		len_ = enemyWP - playerWP;

		// �x�N�g���̐��K��
		len_ = MathUtility::Vector3Normalize(len_) / 1.5;
		len_ *= -1.0f;
		velocity_ = len_;
	}

	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
Vector3 EnemyMissile::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	//worldPos = worldTransform_.translation_;
	return worldPos;
}

Vector3 EnemyMissile::GetLen(Vector3& playerWP)
{
	return this->playerWP = playerWP;
}

void EnemyMissile::OnCollision()
{
	isDead_ = true;
}

void EnemyMissile::Draw(const ViewProjection& viewProjection)
{
	//���f���̕`��
	model_->Draw(worldTransform_2, viewProjection);
}