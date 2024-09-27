#pragma once
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>
#include<stdint.h>
#include<string>

enum class MapChipType { kBlank, kBlock };
struct IndexSet {
	uint32_t xIndex;
	uint32_t yIndex;
};
struct Rect {
	float left;
	float right;
	float bottom;
	float top;
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {


public:
	uint32_t GetNumBlockVirtical();

	uint32_t GetNumBlockHorizontal();


	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	IndexSet GetMapChipIndexSetByPosition(const Vector3& position);
	Rect GetRectByIndex(uint32_t xIndex, uint32_t yIndex);
private:
	//1ブロックサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//ブロックの個数
	static inline const int kNumBlockVirtical = 20;
	static inline const int kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

};