#pragma once
#define NOMINMAX
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include <numbers>
#include "Input.h"
#include <algorithm>
#include <cassert>
#include<vector>
#include"aabb.h"
#include"MapChipField.h"
class MapChipField;
class Enemy;
class Goal;

enum class LRDirection {
	kRight,
	kLeft,

};

enum Corner {
	kRightBottom, // 右下
	kLeftBottom,  // 左下
	kRightTop,    // 右上
	kLeftTop,     // 左上

	kNumCorner // 要素数
};
// マップとの当たり判定情報
struct CollisionMapInfo {
	// 天井衝突フラグ
	bool ceilCollision = false;
	// 着地フラグ
	bool onLanding = false;
	// 壁接触フラグ
	bool wallContact = false;
	// 移動量
	Vector3 moveAmount;
};
class Player {
public:
	// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	// 更新
	void Update();
	// 移動関数
	void Move();
	//マップの衝突判定
	void MapCollisionDetection(CollisionMapInfo& info);
	void MapTopCollision(CollisionMapInfo& info);
	void MapBottomCollision(CollisionMapInfo& info);
	void MapLightCollision(CollisionMapInfo& info);
	void MapLeftCollision(CollisionMapInfo& info);
	// 判定結果を反映して移動させる
	void ResultMove(const CollisionMapInfo& info);
	//天井に衝突している場合の処理	
	void CollidingCeiling(const CollisionMapInfo& info);
	//壁に接触している場合の処理
	void WallContact(const CollisionMapInfo& info);
	//接地状態の切り替え
	void ChangeGround(const CollisionMapInfo& info);
	//衝突応答
	void OnCollision(const Enemy* enemy);
	void OnCollision2(const Goal* goal);
	// 描画
	void Draw();
	//ワールド座標を取得
	Vector3 GetWorldPosition();
	//AABBを取得
	AABB GetAABB();
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	const Vector3& GetVelocity() const { return velocity_; }
	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }
	Vector3 CornerPosition(const Vector3& center, Corner corner);
	bool IsDead() const { return isDead_; }
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	//uint32_t textureHandle_ = 0u;
	// マップチップ
	MapChipField* mapChipField_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewPlojection_ = nullptr;
	static inline const float kAcceleration = 0.1f;
	static inline const float kAttenuation = 0.5f;
	static inline const float kLimitRunSpeed = 0.1f;
	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.08f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 1.0f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 1.0f;
	LRDirection lrDirection_ = LRDirection::kRight;
	//旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;
	//旋回時間
	static inline const float kTimeTurn = 0.3f;
	//接地状態フラグ
	bool onGround_ = true;
	static inline const float kGrandingHeight = 0.06f;
	static inline const float kAttenuationLanding = 0.1f;
	static inline const float kAttenuationWall = 1.0f;

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	static inline const float kBlank = 1.0f;
	static inline const float initialVelocity = 1.0f;
	Vector3 velocity_ = {};
	// デスフラグ
	bool isDead_ = false;
};