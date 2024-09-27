#pragma once
#pragma once
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "myMath.h"
#include <algorithm>
#include <array>
#include <numbers>
class ClearParticle {

public:
	// ������
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	// �X�V
	void Update();
	// �`��
	void Draw();
	// �f�X�O���O��getter
	bool IsFinished() const { return finished_; }

private:
	// ���f��
	Model* model_ = nullptr;
	// �r���[�v���W�F�N�V����
	ViewProjection* viewProjection_ = nullptr;
	// �p�[�e�B�N���̌�
	static inline const uint32_t kNumParticles = 8;
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	// ��������
	static inline const float kDuration = 2.0f;
	// �ړ��̑���
	static inline const float kSpeed = 0.05f;
	// ��������1���̊p�x
	static inline const float kAngleUnit = (2 * std::numbers::pi_v<float> / kNumParticles);
	// �I���t���O
	bool finished_ = false;
	// �o�ߎ��ԃJ�E���g
	float counter_ = 0.0f;
	// �F�ύX�I�u�W�F�N�g
	ObjectColor objectColor_;
	// �F�̕ύX
	Vector4 color_;

};