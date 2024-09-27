#include "ClearParticle.h"
void ClearParticle::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	viewProjection_ = viewProjection;
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	objectColor_.Initialize();
	color_ = { 1, 0, 0, 0 };
}
// �X�V
void ClearParticle::Update() {
	// �I���Ȃ�Ȃ�����Ȃ�
	if (finished_) {
		return;
	}
	for (uint32_t i = 0; i < kNumParticles; ++i) {
		// ��{�ƂȂ鑬�x�x�N�g��
		Vector3 velocity = { kSpeed, 0, 0 };
		// ��]�p���v�Z����
		float angle = kAngleUnit * i;
		// Z������]�s��
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		// ��{�x�N�g������]�����đ��x�x�N�g���𓾂�
		velocity = Transform(velocity, matrixRotation);
		// �ړ�����
		worldTransforms_[i].translation_ += velocity;
	}
	// �J�E���^�[��1�t���[�����̕b���i�߂�
	counter_ += 1.0f / 60.0f;
	// �������Ԃ̏���ɒB������
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// �I�������ɂ���
		finished_ = true;
	}
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatirx();
	}
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	// �F�ύX�I�u�W�F�N�g�ɐF�̐��l��ݒ肷��
	objectColor_.SetColor(color_);
	// �F�ύX�I�u�W�F�N�g��VRAM�ɓ]��
	objectColor_.TransferMatrix();
}
// �`��
void ClearParticle::Draw() {
	// �I���Ȃ�Ȃ�����Ȃ�
	if (finished_) {
		return;
	}
	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}
}