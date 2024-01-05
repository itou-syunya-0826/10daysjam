#include "DrawItem.h"
#include "Novice.h"

void DrawItem(Item item[ITEMTYPE][ITEMNUM], bool itemHit) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 32; j++) {
			if (item[i][j].isSpawn == true) {
				Novice::DrawSprite((int)item[i][j].pos.x, (int)item[i][j].pos.y, item[i][j].img, 1.0f, 1.0f, 0.0f, item[i][j].color);
				//Novice::DrawBox((int)item[i][j].pos.x, (int)item[i][j].pos.y, (int)item[i][j].size.w, (int)item[i][j].size.h, 0.0f, RED, kFillModeWireFrame);
			}
		}
	}

	if (itemHit == true) {

	}

}
