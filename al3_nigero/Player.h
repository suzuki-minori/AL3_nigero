
#pragma once
#define NOMINMAX
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "aabb.h"
#include <algorithm>
#include <cassert>
#include <numbers>
/// <summary>
/// 自キャラ
/// </summary>
class MapChipField;
class Enemy;
// 左右
enum class LRDirection {
	kRight,
	kLeft,
};
// 角
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
	bool onGround = false;
	// 壁接触フラグ
	bool wallhit = false;
	// 移動量
	Vector3 moveAmount;
};
class Player {
public:
	Player();

	~Player();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	const WorldTransform& GetWorldTransform() { return worldTransform_; };
	const Vector3& Getvelocity() const { return velocity_; }
	void SetMapChipField(MapChipField* mapChipField) { mapchipField_ = mapChipField; }
	// 移動関数
	void move();
	// マップ衝突判定関数
	void MapCollision(CollisionMapInfo& info);
	void MapTopCollision(CollisionMapInfo& info);
	void MapBottomCollision(CollisionMapInfo& info);
	void MapRightCollision(CollisionMapInfo& info);
	void MapLeftCollision(CollisionMapInfo& info);
	// 判定結果を反映して移動させる
	void ResultMove(const CollisionMapInfo& info);
	// 天井に接触している場合の処理
	void CeilingHit(const CollisionMapInfo& info);
	// 接地状態の切り替え処理
	void OnGround(const CollisionMapInfo& info);
	// 壁に接触してる場合の処理
	void WallHit(const CollisionMapInfo& info);
	// 旋回制御関数
	void TurnPlayer();

	//衝突応答
	void OnCollision(const Enemy* enemy);

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	//AABBを取得
	AABB GetAABB();

	// デスフラグのgetter
	bool IsDead() const { return isDead_; }

private:
	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.5f;
	static inline const float kLimitRunSpeed = 0.8f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;
	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = 0.1f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 1.0f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 1.0f;
	static inline const float kAttenuationLanding = 0.1f;

	// 微小な数値
	static inline const float kGroundSearchHeight = 0.06f;

	static inline const float kBlank = 1.0f;

	// 着地時の速度減衰率
	static inline const float kAttenuationWall = 1.0f;

	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 接地状態フラグ
	bool onGround_ = true;
	// 着地フラグ
	bool landing = false;
	//デスフラグ
	bool isDead_ = false;
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	LRDirection lrDirection_ = LRDirection::kRight;
	// マップチップによるフィールド
	MapChipField* mapchipField_ = nullptr;

};