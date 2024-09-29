#include "deathParticles.h"

void deathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	viewProjection_ = viewProjection;
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	objectColor_.Initialize();
	color_ = { 1, 1, 1, 1 };
}
// 更新
void deathParticles::Update() {
	//終了ならなんもしない
	if (finished_) {
		return;
	}
	for (uint32_t i = 0; i < kNumParticles; ++i) {
		//基本となる速度ベクトル
		Vector3 velocity = { kSpeed, 0, 0 };
		//回転角を計算する
		float angle = kAngleUnit * i;
		//Z軸回り回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		//基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		//移動処理
		worldTransforms_[i].translation_ += velocity;
	}
	// カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	// 存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		// 終了扱いにする
		finished_ = true;
	}
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatirx();
	}
	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);
	// 色変更オブジェクトをVRAMに転送
	objectColor_.TransferMatrix();
}
// 描画
void deathParticles::Draw() {
	// 終了ならなんもしない
	if (finished_) {
		return;
	}
	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}
}