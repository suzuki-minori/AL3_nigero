#pragma once
#include "ViewProjection.h"
/// <summary>
/// カメラコントローラ
/// </summary>

// 前方宣言
class Player;
class CameraController {
public:
	struct Rect {
		float left = 0.0f;   // 左端
		float right = 1.0f;  // 右端
		float bottom = 0.0f; // 下端
		float top = 1.0f;    // 上端
	};
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(ViewProjection* viewProjection, Rect movableArea_);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	void SetTarget(Player* target) { target_ = target; }
	void Reset();
	void SetMovableArea(Rect area) { movableArea_ = area; }

private:
	// 座標補間割合
	static inline const float kInterpolationRate = 0.8f;
	// 速度掛け率
	static inline const float kVelocityBias = 1.0f;
	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin = { -5.0f, 5.0f, -5.0f, 5.0f };
	// ビュープロジェクション
	ViewProjection* viewProjection_;
	Player* target_ = nullptr;
	// 追従対象とカメラの座標の差(オフセット)
	Vector3 targetOffset_ = { 0, 0, -15.0f };
	// カメラ移動範囲
	Rect movableArea_ = { 0, 100, 0, 100 };
	// カメラの目標座標
	Vector3 targetpos_ = {};
};