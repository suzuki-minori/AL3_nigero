#include "Skydome.h"

void Skydome::Initialize(Model* model, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();

	worldTransform_.scale_ = { 3.0f,3.0f,3.0f };
};

void Skydome::Update() { worldTransform_.UpdateMatrix(); }

void Skydome::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}