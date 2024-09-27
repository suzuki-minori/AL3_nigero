#include "Player.h"
#include<cassert>
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;
	worldTransform_.Initialize();
	viewPlojection_ = viewProjection;

};
void Player::Update() {
	worldTransform_.TransferMatrix();
};
void Player::Draw() {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewPlojection_, textureHandle_);
};