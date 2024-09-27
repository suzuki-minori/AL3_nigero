#include "Enemy.h"
#include "mymath.h"
#include <numbers>


void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	viewProjection_ = viewProjection;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;
	velocity_ = { -kWalkSpeed, 0, 0 };
	walkTimer_ = 0.0f;
}

void Enemy::Update() {
	// 移動
	worldTransform_.translation_.x += velocity_.x;
	// タイマーを加算
	walkTimer_ += 1.0f / 60.0f;
	// 回転アニメーション
	float param = std::sin(2.0f * std::numbers::pi_v<float> *walkTimer_ / kWalklMotionTime);
	float radian = kWalkMotionAngleStart + kWalkMotionAngleEnd * (param + 1.0f) / 2.0f;
	worldTransform_.rotation_.x = radian * (std::numbers::pi_v<float> / 180.0f);
	// 行列計算
	worldTransform_.UpdateMatirx();
}

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}
AABB Enemy::GetAABB() {
	Vector3 worldPos = GetWorldPosition();
	AABB aabb;
	aabb.min = { worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f };
	aabb.max = { worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f };
	return aabb;
}

void Enemy::OnCollision(const Player* player) {
	(void)player;
}

void Enemy::Draw() { model_->Draw(worldTransform_, *viewProjection_); }