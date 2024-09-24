#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "mymath.h"
#include <array>
#include <numbers>
#include <algorithm>
#include <Vector4.h>
#include <ObjectColor.h>

/// <summary>
/// デス演出用パーティクル
/// </summary>
class DeathParticles {
public:
	DeathParticles();
	~DeathParticles();

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	void Update();

	void Draw();

	// デスグラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// パーティクルの個数
	static inline const uint32_t kNumParticles = 8;

	std::array<WorldTransform, kNumParticles> worldTransforms_;

	//存続時間(消滅までの時間)<秒>
	static inline const float kDuration = 2.0f;
	//移動の速さ
	static inline const float kSpeed = 0.05f;
	//分割した1個分の角度
	static inline const float kAngleUnit = (2 * std::numbers::pi_v<float> / kNumParticles);
	//終了フラグ
	bool finished_ = false;
	//経過時間カウント
	float counter_ = 0.0f;
	// ワールド変換データ
	//WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	//色変更オブジェクト
	ObjectColor objectColor_;
	//色の変更
	Vector4 color_;
};