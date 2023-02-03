#include "player.h"

// �A�t�B���s��Ăяo��
MatWorld* playerMatworld = nullptr;


//����������
void Player::Initialize(Model* model)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//���L�����̒e���f���̐���
	modelPlayerBullet_ = Model::CreateFromOBJ("bullet", true);
	modelPlayerShoot_ = Model::CreateFromOBJ("robo_shoot", true);
	modelPlayerFront_ = Model::CreateFromOBJ("robo_front", true);
	modelPlayerBack_ = Model::CreateFromOBJ("robo_back", true);
	modelPlayerLeft_ = Model::CreateFromOBJ("robo_left", true);
	modelPlayerRight_ = Model::CreateFromOBJ("robo_right", true);



	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,50 };//���W{x,y,z}

	//�������W���Z�b�g
	worldTransform_.translation_ = move;

}

//���[���h���W������ϐ�
Vector3 Player::GetWorldPosition()
{
	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��̕��s�ړ������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//�Փ˔���
void Player::OnCollision(int& hp)
{
	hp -= 1;
}

void Player::Mat()
{
	//�s��̌v�Z
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();
}

//�v���C���[�̍U������
void Player::Attack()
{
	//�X�y�[�X���������猂��
	if (input_->TriggerKey(DIK_SPACE))
	{

		//�e�𐶐����A������
		std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelPlayerBullet_, worldTransform_.translation_);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));


	}
	/*if (shootFlag == true)
	{
		shootTimer--;
		action = action::�U��;
	}
	if (shootTimer <= 0)
	{
		shootTimer = cShootTimer;
		shootFlag = false;
	}*/
}


//�A�b�v�f�[�g
void Player::Update()
{
	//�e�̈ʒu
	velocity_.z = -kBulletSpeed;

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0, 0, 0 };

	action = action::�U��;
	// ���s�ړ�
	{ // X����
		if (input_->PushKey(DIK_A)) {
			move.x += 0.2f;
			action = action::��;
		}
		else if (input_->PushKey(DIK_D)) {
			move.x -= 0.2f;
			action = action::�E;
		}
		// Z����
		if (input_->PushKey(DIK_W)) {
			move.y += 0.2f;
			action = action::�O;

		}
		else if (input_->PushKey(DIK_S)) {
			move.y -= 0.2f;
			action = action::���;
		}
	}

	worldTransform_.translation_ += move;

	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	//�s��̌v�Z
	worldTransform_.matWorld_ = playerMatworld->CreateMatWorld(worldTransform_);
	//�s��̓]��
	worldTransform_.TransferMatrix();

	Attack();

	// �e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Update(velocity_, shootFlag);
	}
}



//�`�揈��
void Player::Draw(ViewProjection& viewProjection_)
{
	switch (action)
	{
	case action::�҂�:
		model_->Draw(worldTransform_, viewProjection_);
		break;
	case action::��:
		modelPlayerLeft_->Draw(worldTransform_, viewProjection_);
		break;
	case action::�E:
		modelPlayerRight_->Draw(worldTransform_, viewProjection_);
		break;
	case action::�O:
		modelPlayerFront_->Draw(worldTransform_, viewProjection_);
		break;
	case action::���:
		modelPlayerBack_->Draw(worldTransform_, viewProjection_);
		break;
	default:
		modelPlayerShoot_->Draw(worldTransform_, viewProjection_); break;
	}

	// �e�̕`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}
