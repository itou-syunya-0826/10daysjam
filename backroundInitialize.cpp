#include "backroundInitialize.h"
#include "Novice.h"

Backround backroundInitialize(Backround backround) {
	backround.img[0] = Novice::LoadTexture("./resources/backround/PJWH_Background0.png");
	backround.pos = { 0,0 };
	backround.color = WHITE;
	return backround;
}
