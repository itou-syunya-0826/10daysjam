#include "chkAtkHit.h"
#include "chkObjHit.h"
#include"external.h"
#include "IsPlaySE.h"


Bullet chkAtkHit(Bullet bullet, Enemy &enemy, SEHandler soundEffect) {
	if (bullet.isShot[maru] == true) {
		bool chkCollision;

		chkCollision = chkObjHit(bullet.position, bullet.size[maru], enemy.newLeftEnemyBottom.position, enemy.size);
		if (chkCollision == true) {
			IsPlaySE(soundEffect.audio[7], soundEffect.handler[7], soundEffect.count[7], 5);
			bullet.isShot[maru] = false;
			bullet.isHit[maru] = true;
			bullet.t[maru] = 0;
			enemy.isHit = true;
		}
	}
	if (bullet.isShot[triangle] == true) {

		for (int i = 0; i < 8; i++) {
			bool chkCollision = false;
			chkCollision = (External(bullet.newLeftTop[i].position, bullet.newRightTop[i].position, enemy.newLeftEnemyBottom.position, enemy.size.w, enemy.size.h) &&
				External(bullet.newRightTop[i].position, bullet.newRightBottom[i].position, enemy.newLeftEnemyTop.position, 0, enemy.size.h) &&
				External(bullet.newRightBottom[i].position, bullet.newLeftBottom[i].position, enemy.newRightEnemyTop.position, 0, 0) &&
				External(bullet.newLeftBottom[i].position, bullet.newLeftTop[i].position, enemy.newRightEnemyBottom.position, enemy.size.w, 0));
			if (chkCollision) {
				IsPlaySE(soundEffect.audio[7], soundEffect.handler[7], soundEffect.count[7], 5);
				bullet.isHit[triangle] = true;
				enemy.isHit = true;
			}
		}
	}
	if (bullet.isShot[square] == true) {
		bool chkCollision = false;

		chkCollision = chkObjHit(bullet.pos[8], bullet.size[square], enemy.newLeftEnemyTop.position, enemy.size);
		if (chkCollision == true) {
			IsPlaySE(soundEffect.audio[7], soundEffect.handler[7], soundEffect.count[7], 5);
			bullet.isShot[square] = false;
			bullet.isHit[square] = true;
			enemy.isHit = true;
		}
	}
	return bullet;
}