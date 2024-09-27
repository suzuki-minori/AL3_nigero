#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "Skydome.h"
#include<myMath.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete skydome_;
	delete model_;
	delete modelBlock_;
	delete debugCamera_;
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	delete player_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("mario.png");
	model_ = Model::Create();
	modelBlock_ = Model::Create();
	viewProjection_.Initialize();
	worldTransform_.Initialize();

	player_ = new Player();
	player_->Initialize(model_, textureHandle_, &viewProjection_);

	skydomeModel_ = Model::Create();
	skydome_ = new Skydome();
	skydome_->Initialize(skydomeModel_, &viewProjection_);

	debugCamera_ = new DebugCamera(1280, 720);
	const uint32_t kNumBlockHorizontal = 20;
	const uint32_t kNumBlockVirtucal = 10;
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;
	worldTransformBlocks_.resize(kNumBlockVirtucal);

	for (uint32_t i = 0; i < kNumBlockVirtucal; ++i) {
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);

	}
	for (uint32_t i = 0; i < kNumBlockVirtucal; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		}



	}
}


void GameScene::Update() {
	skydome_->Update();
	player_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	player_->Draw();
	skydome_->Draw();

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
