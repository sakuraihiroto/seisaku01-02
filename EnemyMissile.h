#pragma once
#include"Model.h"
#include"matWorld.h"
#include"MathUtility.h"
#include"player.h"

using namespace MathUtility;

class EnemyMissile
{
public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="position">�������W</param>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V����</param>
	void Draw(const ViewProjection& viewProjection);

	bool IsDead()const { return isDead_; }

	Vector3 GetLen(Vector3& len);
	//void SetPlayer(Player* player) { player_ = player; }

	Vector3 GetWorldPosition();
	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision();
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	WorldTransform worldTransform_2;
	//���f���̃|�C���^
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//���x
	Vector3 velocity_;

	Vector3 len_;

	Vector3 playerWP;

	MatWorld* enemyMatworld = nullptr;

	Player* player_ = nullptr;


	int upTimer = 60;
	int timer = 0;
	//����
	static const int32_t kLifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};