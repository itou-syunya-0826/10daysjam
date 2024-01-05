#include "DrawBackround.h"
#include "Novice.h"

Backround DrawBackround(Backround backround) {

	Novice::DrawSprite((int)backround.pos.x, (int)backround.pos.y, backround.img[0], 1.0f, 1.0f, 0.0f, backround.color);

	return backround;
}