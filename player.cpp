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

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	//�r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0,0,100 };//���W{x,y,z}

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

//�v���C���[�̍U������
void Player::Attack()
{
	//�X�y�[�X���������猂��
	if (input_->TriggerKey(DIK_SPACE))
	{
		if (shootFlag == 0)
		{
			//�e�𐶐����A������
			std::unique_ptr<PlayerBullet>newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(modelPlayerBullet_, worldTransform_.translation_);

			//�e��o�^����
			bullets_.push_back(std::move(newBullet));

			shootFlag = 1; //���˃t���O		
		}
		if (shootFlag == 1)
		{
			shootFlag = 0;
		}
	}
}


//�A�b�v�f�[�g
void Player::Update()
{
	velocity_.z = -kBulletSpeed;

	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0, 0, 0 };

	// ���s�ړ�
	{ // X����
		if (input_->PushKey(DIK_A)) {
			move.x += 0.2f;

		}
		else if (input_->PushKey(DIK_D)) {
			move.x -= 0.2f;
		}
		// Z����
		if (input_->PushKey(DIK_W)) {
			move.z -= 0.2f;
		}
		else if (input_->PushKey(DIK_S)) {
			move.z += 0.2f;
		}
		// Z����
		if (input_->PushKey(DIK_3)) {
			move.z = 0.2f;
		}
		else if (input_->PushKey(DIK_4)) {
			move.z = -0.2f;
		}
	}

	worldTransform_.translation_ += move;


	// ��]�x�N�g��
	Vector3 rotate = { 0, 0, 0 };

	{ // X����
		if (input_->PushKey(DIK_Q)) {
			
		}
		else if (input_->PushKey(DIK_E)) {
			
		}
		// Y����
		if (input_->PushKey(DIK_1)) {
			rotate.y = +0.1f;
		}
		else if (input_->PushKey(DIK_2)) {
			rotate.y = -0.1f;
		}
	}

	worldTransform_.rotation_ += rotate;

	//�e�̈ʒu
	

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
	model_->Draw(worldTransform_, viewProjection_);

	// �e�̕`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_)
	{
		bullet->Draw(viewProjection_);
	}
}
