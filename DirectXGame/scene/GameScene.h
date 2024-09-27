#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include"Player.h"
#include <vector>
#include"DebugCamera.h"


class Skydome;
/// <summary>
/// ゲームシーン
/// </summary>
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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	Model* model_ = nullptr;
	Model* modelBlock_ = nullptr;
	WorldTransform worldTransform_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>

	Skydome* skydome_;
	Model* skydomeModel_;
	ViewProjection viewProjection_;
	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;
	bool isDebugcameraActive_ = false;
	DebugCamera* debugCamera_ = nullptr;
	Player* player_ = nullptr;
};
