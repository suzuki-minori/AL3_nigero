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
	// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw();
	// デスグラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;
	std::array<WorldTransform, kNumParticles> worldTransforms_;
	// 存続時間
	static inline const float kDuration = 2.0f;
	// 移動の速さ
	static inline const float kSpeed = 0.05f;
	// 分割した1個分の角度
	static inline const float kAngleUnit = (2 * std::numbers::pi_v<float> / kNumParticles);
	// 終了フラグ
	bool finished_ = false;
	// 経過時間カウント
	float counter_ = 0.0f;
	// 色変更オブジェクト
	ObjectColor objectColor_;
	// 色の変更
	Vector4 color_;

};