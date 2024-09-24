#include "DeathParticles.h"

DeathParticles::DeathParticles() {}

DeathParticles::~DeathParticles() {}

void DeathParticles::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	model_ = model;
	viewProjection_ = viewProjection;
	// ワールド変換の初期化
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.Initialize();
		worldTransform.translation_ = position;
	}
	objectColor_.Initialize();
	color_ = { 1, 1, 1, 1 };
}

void DeathParticles::Update() {
	//早期リターン
	if (finished_) {
		return;
	}

	for (uint32_t i = 0; i < kNumParticles; ++i) {
		// 基本となる速度ベクトル
		Vector3 velocity = { kSpeed, 0.0f, 0.0f };
		// 回転角を設定する
		float angle = kAngleUnit * i;
		//Z軸周り回転行列
		Matrix4x4 matrixRotation = MakeRotateZMatrix(angle);
		//基本ベクトルを回転させて速度ベクトルを得る
		velocity = Transform(velocity, matrixRotation);
		//移動処理
		worldTransforms_[i].translation_.x += velocity.x;
		worldTransforms_[i].translation_.y += velocity.y;
	}
	//カウンターを1フレーム分の秒数進める
	counter_ += 1.0f / 60.0f;
	//存続時間の上限に達したら
	if (counter_ >= kDuration) {
		counter_ = kDuration;
		//終了扱いにする
		finished_ = true;
	}
	for (auto& worldTransform : worldTransforms_) {
		worldTransform.UpdateMatrix();
	}

	color_.w = std::clamp(1.0f - counter_ / kDuration, 0.0f, 1.0f);
	//色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);
	//色変更オブジェクトをVRAMに転送
	objectColor_.TransferMatrix();
}

void DeathParticles::Draw() {
	//早期リターン
	if (finished_) {
		return;
	}
	for (auto& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, *viewProjection_, &objectColor_);
	}
}