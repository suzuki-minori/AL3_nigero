#include "WorldTransform.h"
#include"myMath.h"

void WorldTransform::UpdateMatirx() {
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	TransferMatrix();
}