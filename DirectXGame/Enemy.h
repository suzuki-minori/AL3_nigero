#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include<vector>
#include"MapChipField.h"
#include"aabb.h"

class Player;

class Enemy {
public:
	// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	// 更新
	void Update();
	// 描画
	void Draw();
	// ワールド座標を取得
	Vector3 GetWorldPosition();
	// AABBを取得
	AABB GetAABB();
	// 衝突応答
	void OnCollision(const Player* player);

private:
	//歩行の速さ
	static inline const float kWalkSpeed = 0.05f;
	// 最初の角度[度]
	static inline const float kWalkMotionAngleStart = -5.0f;
	// 最後の角度[度]
	static inline const float kWalkMotionAngleEnd = 8.0f;
	// アニメーションの周期となる時間[秒]
	static inline const float kWalklMotionTime = 1.0f;
	// 経過時間
	float walkTimer_ = 0.0f;
	// キャラクターの当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	// 速度
	Vector3 velocity_ = {};
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};