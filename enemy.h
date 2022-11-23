#pragma once

#include"ViewProjection.h"
#include"WorldTransform.h"
#include"Model.h"
#include"matWorld.h"
//#include"player.h"
#include"EnemyBullet.h"
#include"EnemyMissile.h"

//�O���錾
class Player;

class Enemy
{
public:

	//�s���t�F�[�Y
	enum class Phase
	{
		Move,	//�ڋ߂���
		Leave,		//���E����
	};
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���[�U�[�U��
	/// </summary>
	void Laser();

	/// <summary>
	/// �~�T�C���U��
	/// </summary>
	void Missile();

	//�ړ�
	void Move(float& appSpeed);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection& viewProjection);

	//�Փ˔���
	void OnCollision(int& deadEnemyNum);

	void SetPlayer(Player* player) { player_ = player; }

	void SetWorldPos(Vector3 worldPos) { playerWP = worldPos; }

	// ���[���h���W���擾
	Vector3 GetWorldPosition();

	bool IsDead() const { return isDead_; }

	//���ˊԊu
	static const int kFireInterval = 60;

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyMissile>>& GetMissiles() { return missiles_; }

	//�e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }
private:

	//���L����
	Player* player_ = nullptr;

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	Model* missileModel_ = nullptr;

	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
	//�t�F�[�Y
	Phase phase_ = Phase::Move;
	//���x
	Vector3 velocity_;

	Vector3 len;

	Vector3 playerWP;

	MatWorld* enemyMatworld = nullptr;

	//�e
	std::list < std::unique_ptr< EnemyBullet >> bullets_;
	//�~�T�C��
	std::list < std::unique_ptr< EnemyMissile >> missiles_;

	//�f�X�t���O
	int Hp = 5;
	bool isDead_ = false;

	//�{�X�t�F�[�Y2
	bool isPhase2_ = false;

	//���˃^�C�}�[
	int32_t fireTimer = 0;
	int32_t fireTimer2 = 0;
	int32_t missileTimer = 40;
	int32_t LaserTimer = 10;
	int32_t LaserNum = 3;

};