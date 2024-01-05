#include "chkEnemyAtkHit.h"
#include "chkObjHit.h"
#include "external.h"
#include "IsPlaySE.h"

Bullet chkEnemyAtkHit(Bullet enemyBullet, Item[ITEMTYPE][ITEMNUM], Player &player, SEHandler soundEffect) {

	if (enemyBullet.isShot[0] == true) {
		bool chkCollision = false;

		for (int i = 0; i < 8; i++) {
			chkCollision = (External(enemyBullet.newLeftTop[i].position, enemyBullet.newRightTop[i].position, player.newLeftTop.position, player.size.w, player.size.h) &&
				External(enemyBullet.newRightTop[i].position,enemyBullet.newRightBottom[i].position, player.newLeftTop.position, 0, player.size.h) &&
				External(enemyBullet.newRightBottom[i].position, enemyBullet.newLeftBottom[i].position, player.newLeftTop.position, 0, 0) &&
				External(enemyBullet.newLeftBottom[i].position, enemyBullet.newLeftTop[i].position, player.newLeftTop.position, player.size.w, 0));
			if (chkCollision == true) {
				IsPlaySE(soundEffect.audio[7], soundEffect.handler[7], soundEffect.count[7], 5);
				enemyBullet.isHit[0] = true;
				player.isHit = true;
			}
		}
	}

	if (enemyBullet.isShot[1] == true) {
		bool chkCollision = false;

		chkCollision = chkObjHit(enemyBullet.position, enemyBullet.size[2], player.newLeftTop.position, player.size);
		if (chkCollision == true) {
			IsPlaySE(soundEffect.audio[7], soundEffect.handler[7], soundEffect.count[7], 5);
			player.isHit = true;
			enemyBullet.isShot[1] = false;
		}
	}
	return enemyBullet;
}