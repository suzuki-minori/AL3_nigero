#pragma once
#define NOMINMAX
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "aabb.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#include <vector>
class MapChipField;
class Player;

class Goal {
public:
	// ������
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// ���[���h���W���擾
	Vector3 GetWorldPosition();
	// �Փˉ���
	void OnCollision(const Player* player);

	// AABB���擾
	AABB GetAABB();
	bool IsDead() const { return isFinished_; }

private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	// uint32_t textureHandle_ = 0u;
	// �}�b�v�`�b�v
	MapChipField* mapChipField_ = nullptr;
	// �r���[�v���W�F�N�V����
	ViewProjection* viewProjection_ = nullptr;
	// �L�����N�^�[�̓����蔻��T�C�Y
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	// �f�X�t���O
	bool isFinished_ = false;
};