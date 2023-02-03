#include "enemy.h"



//�ړ��t�F�[�Y
void Enemy::Move(float& appSpeed)
{

}

void Enemy::Initialize(Model* model) {

	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	missileModel_ = Model::CreateFromOBJ("missile", true);

	//�G��HP�̏�����
	//Hp = 5;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,-50 };//���W{x,y,z}

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
	if (Hp < 3)
	{
		isPhase2_ = true;
	}

	// �f�X�t���O�̗������e������
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		}
	);
	// �f�X�t���O�̗������e������
	missiles_.remove_if([](std::unique_ptr<EnemyMissile>& missile)
		{
			return missile->IsDead();
		}
	);

	// �G�L�����̃��[���h���W���擾
	Vector3 enemyWP = GetWorldPosition();

	// �G�L�����A���L�����̍����x�N�g��
	len = enemyWP - playerWP;

	// �x�N�g���̐��K��
	len = MathUtility::Vector3Normalize(len);

	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->GetLen(playerWP);
	}

	// ���˃^�C�}�[�J�E���g�_�E��
	fireTimer--;
	LaserTimer--;
	//�G�̎�_�J�E���g�_�E��
	weakTimer--;
	if (weakTimer < 0)
	{
		isWeak_ = true;
	}

	//�G���t�F�[�Y2�̎�
	if (isPhase2_ == true)
	{
		// �w�莞�ԂɒB����
		if (LaserTimer < 0 && LaserNum > 0)
		{
			// �e�𔭎�
			Laser();
			Missile();
			LaserNum--;
			// ���˃^�C�}�[��������
			LaserTimer = 20;// 1/3�b
			fireTimer = 60;//1�b
		}
		if (fireTimer < 0)
		{
			LaserNum = 3;
		}
	}
	//�G���t�F�[�Y1�̎�
	if (isPhase2_ == false)
	{
		missileTimer--;
		// �w�莞�ԂɒB����
		if (fireTimer < 0)
		{
			// �e�𔭎�
			Laser();
			missileTimer = 40;
			// ���˃^�C�}�[��������
			fireTimer = kFireInterval;
		}
		if (missileTimer < 0)
		{
			Missile();
			missileTimer = 40;
		}
	}
	// ���[�U�[�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Update();
	}
	// �~�T�C���X�V
	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->Update();
	}

	//�s��̌v�Z
	worldTransform_.matWorld_ = enemyMatworld->CreateMatWorld(worldTransform_);

	//�s��̓]��
	worldTransform_.TransferMatrix();
}

void Enemy::Laser()
{
	
	// �e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(worldTransform_.translation_, len);

	// �e��o�^����
	bullets_.push_back(std::move(newBullet));
}

void Enemy::Missile()
{
	// �e�𐶐����A������
	std::unique_ptr<EnemyMissile> newMissile = std::make_unique<EnemyMissile>();
	newMissile->Initialize(missileModel_, worldTransform_.translation_);

	// �e��o�^����
	missiles_.push_back(std::move(newMissile));
}

void Enemy::ResetBullet()
{
	for (std::unique_ptr<EnemyBullet>& laser : bullets_)
	{
		laser->OnCollision();
	}
	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->OnCollision();
	}

	// �f�X�t���O�̗������e������
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
		{
			return bullet->IsDead();
		}
	);
	// �f�X�t���O�̗������e������
	missiles_.remove_if([](std::unique_ptr<EnemyMissile>& missile)
		{
			return missile->IsDead();
		}
	);
}


//�Փ˔���
void Enemy::OnCollision(int& hp)
{
	if (isWeak_)
	{
		hp -= 1;
		isWeak_ = false;
		weakTimer = 300;
	}
	if (hp < 3)
	{
		isPhase2_ = true;
	}
	if (hp <= 0)
	{
		isDead_ = true;
	}
}

void Enemy::Draw(ViewProjection& viewProjection)
{
	//���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
	// �e�̕`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection);
	}
	// �~�T�C���̕`��
	for (std::unique_ptr<EnemyMissile>& missile : missiles_)
	{
		missile->Draw(viewProjection);
	}
}