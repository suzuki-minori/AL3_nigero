#pragma once
#define NOMINMAX
#include "Input.h"
#include "MapChipField.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "aabb.h"
#include <algorithm>
#include <cassert>
#include <numbers>
#include <vector>
class MapChipField;
class Player;

class Goal {
public:
	// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw();
	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// 衝突応答
	void OnCollision(const Player* player);

	// AABBを取得
	AABB GetAABB();
	bool IsDead() const { return isFinished_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	// uint32_t textureHandle_ = 0u;
	// マップチップ
	MapChipField* mapChipField_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	// デスフラグ
	bool isFinished_ = false;
};