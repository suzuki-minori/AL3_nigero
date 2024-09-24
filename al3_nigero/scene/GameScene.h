#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>
#include "DebugCamera.h"
#include "mymath.h"
#include "Skydome.h"
#include "Player.h"
#include "Enemy.h"
#include "MapChipField.h"
#include "CameraController.h"
#include "DeathParticles.h"
/// <summary>
/// ゲームシーン
/// </summary>

//ゲームのフェーズ(型)
enum class Phase {
	kPlay,//ゲームプレイ
	kDeath,//デス演出
};

class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void GenerateBlocks();

	//全ての当たり判定を行う
	void CheckAllCollisions();

	//フェーズの切り替え
	void ChangePhase();

	//デスフラグのgetter
	bool IsFinished() const { return finished_; }

private:
	// メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Model* modelBlocks_ = nullptr;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	ViewProjection viewProjection_;
	// デバックカメラ有効
	bool isDebugCameraActive_ = false;
	// デバックカメラ
	DebugCamera* debugCamera_ = nullptr;
	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;
	Model* modelPlayer_ = nullptr;

	//敵
	std::list<Enemy*> enemies_;
	Model* modelEnemy_ = nullptr;

	//パーティクル
	DeathParticles* deathParticles_ = nullptr;
	Model* modelParticles_ = nullptr;

	//マップチップフィールド
	MapChipField* mapChipField_;
	//カメラコントローラ
	CameraController* cameraController_ = nullptr;
	CameraController::Rect movableArea = { 0, 100, 0, 100 };

	//ゲームの現在フェーズ(変数)
	Phase phase_;

	//終了フラグ
	bool finished_ = false;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};