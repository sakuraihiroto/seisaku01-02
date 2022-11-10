#include "enemy.h"

MatWorld* enemyMatworld = nullptr;

//�ڋ߃t�F�[�Y
void Enemy::Approach(float& appSpeed)
{
	
}

void Enemy::Initialize(Model* model) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,10,-50 };//���W{x,y,z}

	//�������W���Z�b�g
	worldTransform_.translation_ = move;

}

Vector3 Enemy::GetWorldPosition()
{
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾(���[���h���W)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Update()
{
	
	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//�s��̓]��
	worldTransform_.TransferMatrix();

}

//�Փ˔���
void Enemy::OnCollision(int& deadEnemyNum)
{
	isDead_ = true;
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
}