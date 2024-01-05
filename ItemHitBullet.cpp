#include "ItemHitBullet.h"

bool HitItem(Item item[ITEMTYPE][ITEMNUM], Vector2 bulletPos) {
	bool isHit = false;
	for (int i = 0; i < ITEMTYPE; i++) {
		for (int j = 0; j < ITEMNUM; i++) {
			if (item[i][j].isSpawn) {
				isHit = Hit(item[i][j].pos.x, item[i][j].pos.y, 64, 64, bulletPos.x, bulletPos.y, 64, 64);
			}
		}
	}
	return isHit;
}
