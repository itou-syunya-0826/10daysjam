#include "chkItemBulletHit.h"
#include "chkObjHit.h"

bool chkItemBulletHit(Item item[ITEMTYPE][ITEMNUM], Bullet bullet) {

	for (int i = 0; i < ITEMTYPE; i++) {
		for (int j = 0; j < ITEMNUM; j++) {
			if (item[i][j].isSpawn == true) {
				bool chkCollision;
				bool chkCollision2;
				bool chkCollision3;

				chkCollision = chkObjHit(item[i][j].pos, item[i][j].size, bullet.pos[maru], bullet.size[maru]);
				chkCollision2 = chkObjHit(item[i][j].pos, item[i][j].size, bullet.pos[square], bullet.size[square]);
				chkCollision3 = chkObjHit(item[i][j].pos, item[i][j].size, bullet.pos[triangle], bullet.size[triangle]);

				if (chkCollision == true || chkCollision2 == true || chkCollision3) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	return false;
}