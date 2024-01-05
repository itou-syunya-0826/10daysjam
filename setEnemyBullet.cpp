#include "setEnemyBullet.h"
#include <stdlib.h>
#include "IsPlaySE.h"

Bullet setEnemyBullet(Bullet enemyBullet, ItemCounter &itemCounter, Enemy enemy, SEHandler soundEffect) {

	int setRand = 0;
	int timer = 1;

	if (itemCounter.bossNum >= 10 && enemyBullet.isShot[0] == false) {

		if (timer > 0) {
			timer--;
		}
		else {
			timer = 1;
		}

		if (timer <= 0) {
			setRand = rand() % 2;
		}

		if (setRand == 0) {  //0 = beam
			IsPlaySE(soundEffect.audio[5], soundEffect.handler[5], soundEffect.count[5], 5);
			enemyBullet.bulletType = 0;
			enemyBullet.isShot[0] = true;
			enemyBullet.t[0] = 180;
			enemyBullet.ani[0] = 30;
			itemCounter.bossNum = 0;
		}
		else { //1 = homing
			IsPlaySE(soundEffect.audio[6], soundEffect.handler[6], soundEffect.count[6], 5);
			enemyBullet.bulletType = 1;
			enemyBullet.isShot[1] = true;

			enemyBullet.position.x = enemy.newLeftEnemyTop.position.x + enemy.size.w / 2;
			enemyBullet.position.y = enemy.newLeftEnemyTop.position.y + enemy.size.h / 2;
			itemCounter.bossNum = 0;
		}
	}
	return enemyBullet;
}