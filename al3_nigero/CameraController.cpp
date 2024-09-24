#include "CameraController.h"
#include "Player.h"
#include "mymath.h"
void CameraController::Initialize(ViewProjection* viewProjection, Rect movableArea) {
	viewProjection_ = viewProjection;
	movableArea_ = movableArea;
}

void CameraController::Update() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	Vector3 targetVelocity = target_->Getvelocity();

	// 追従対象とオフセットと追従対象の速度からカメラの目標座標を計算
	targetpos_ = Add(Add(targetWorldTransform.translation_, targetOffset_), targetVelocity) * kVelocityBias;

	//座標補間によりゆったり追従
	viewProjection_->translation_.x = std::lerp(viewProjection_->translation_.x, targetpos_.x, kInterpolationRate);
	viewProjection_->translation_.y = std::lerp(viewProjection_->translation_.y, targetpos_.y, kInterpolationRate);

	//追従対象が画面外に出ないように補正
	viewProjection_->translation_.x = max(viewProjection_->translation_.x, targetpos_.x + margin.left);
	viewProjection_->translation_.x = min(viewProjection_->translation_.x, targetpos_.x + margin.right);
	viewProjection_->translation_.y = max(viewProjection_->translation_.y, targetpos_.y + margin.bottom);
	viewProjection_->translation_.y = min(viewProjection_->translation_.y, targetpos_.y + margin.top);

	//移動範囲制限
	viewProjection_->translation_.x = max(viewProjection_->translation_.x, movableArea_.left);
	viewProjection_->translation_.x = min(viewProjection_->translation_.x, movableArea_.right);
	viewProjection_->translation_.y = max(viewProjection_->translation_.y, movableArea_.bottom);
	viewProjection_->translation_.y = min(viewProjection_->translation_.y, movableArea_.top);

	// 行列を更新する
	viewProjection_->UpdateMatrix();
}

void CameraController::Reset() {
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	//追従対象とオフセットからカメラの座標を計算
	viewProjection_->translation_ = Add(targetWorldTransform.translation_, targetOffset_);
}