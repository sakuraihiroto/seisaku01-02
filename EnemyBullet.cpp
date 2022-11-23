#include"EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(const Vector3& position, const Vector3& velocity)
{
	//null�|�C���^�`�F�b�N
	//assert(model);

	model_ = Model::Create();
	//model_ = model;
	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("enemyBulletP.png");

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	//�����Ŏ󂯎�������x�������o�ϐ��ɑ��
	velocity_ = velocity;
	velocity_ *= -1.0f;
}

void EnemyBullet::Update()
{
	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);
	//���[���h�s���]��
	worldTransform_.TransferMatrix();

	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;
	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}

}
Vector3 EnemyBullet::GetWorldPosition()
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
void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

void EnemyBullet::Draw(const ViewProjection& viewProjection)
{
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}