#include "chkItemCounter.h"
#include "chkObjHit.h"
#include "ItemSpawn.h"
#include "external.h"
#include "IsPlaySE.h"

ItemCounter chkItemCounter(Item item[5][32], Player player, Enemy enemy, ItemCounter itemCounter, SEHandler soundEffect,bool &isCloss) {

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 32; j++) {

			if (item[i][j].isSpawn == true) {

				if (External(player.newLeftTop.position, player.newRightTop.position, item[i][j].pos, 50, 50) &&
					External(player.newRightTop.position, player.newRightBottom.position, item[i][j].pos, 0, 50) &&
					External(player.newRightBottom.position, player.newLeftBottom.position, item[i][j].pos, 0, 0) &&
					External(player.newLeftBottom.position, player.newLeftTop.position, item[i][j].pos, 50, 0)) {

					if (i == cross) {
						item[i][j].isSpawn = false;
						if (itemCounter.crossNum < 5) {
							isCloss = true;
							itemCounter.crossNum += 1;
							IsPlaySE(soundEffect.audio[7], soundEffect.handler[7], soundEffect.count[7], 5);
						}
					}
					if (i == heart) {
						item[i][j].isSpawn = false;
						if (itemCounter.heartNum < 5) {
							itemCounter.heartNum += 1;
						}
						if (itemCounter.heartNum == 3) {
							IsPlaySE(soundEffect.audio[0], soundEffect.handler[0], soundEffect.count[0], 5);
						}
					}
					if (i == maru) {
						item[i][j].isSpawn = false;
						if (itemCounter.maruNum < 5) {
							itemCounter.maruNum += 1;
						}
						if (itemCounter.maruNum == 3) {
							IsPlaySE(soundEffect.audio[0], soundEffect.handler[0], soundEffect.count[0], 5);
						}
					}
					if (i == square) {
						item[i][j].isSpawn = false;
						if(itemCounter.squareNum < 5) {
							itemCounter.squareNum += 1;
						}
						if (itemCounter.squareNum == 3) {
							IsPlaySE(soundEffect.audio[0], soundEffect.handler[0], soundEffect.count[0], 5);
						}
					}
					if (i == triangle) {
						item[i][j].isSpawn = false;
						if (itemCounter.triangleNum < 5) {
							itemCounter.triangleNum += 1;
						}
						if (itemCounter.triangleNum == 3) {
							IsPlaySE(soundEffect.audio[0], soundEffect.handler[0], soundEffect.count[0], 5);
						}
					}
				}

				if (External(enemy.newLeftEnemyTop.position, enemy.newRightEnemyTop.position, item[i][j].pos, 50, 50) &&
					External(enemy.newRightEnemyTop.position, enemy.newRightEnemyBottom.position, item[i][j].pos, 0, 50) &&
					External(enemy.newRightEnemyBottom.position, enemy.newLeftEnemyBottom.position, item[i][j].pos, 0, 0) &&
					External(enemy.newLeftEnemyBottom.position, enemy.newLeftEnemyTop.position, item[i][j].pos, 50, 0)) {

					if (itemCounter.bossNum < 11 && item[i][j].isSpawn == true) {
						item[i][j].isSpawn = false;
						itemCounter.bossNum += 1;
					}
				}
			}
		}
	}

	if (itemCounter.crossNum >= 1) {
		if (itemCounter.heartNum > 0 ||
			itemCounter.maruNum > 0 ||
			itemCounter.squareNum > 0 ||
			itemCounter.triangleNum > 0) {

			itemCounter.crossNum = 0;
			itemCounter.heartNum = 0;
			itemCounter.maruNum = 0;
			itemCounter.squareNum = 0;
			itemCounter.triangleNum = 0;
		}
	}

	if (itemCounter.heartNum >= 1) {
		if (itemCounter.crossNum > 0 ||
			itemCounter.maruNum > 0 ||
			itemCounter.squareNum > 0 ||
			itemCounter.triangleNum > 0) {

			itemCounter.crossNum = 0;
			itemCounter.heartNum = 0;
			itemCounter.maruNum = 0;
			itemCounter.squareNum = 0;
			itemCounter.triangleNum = 0;
		}
	}

	if (itemCounter.maruNum >= 1) {
		if (itemCounter.crossNum > 0 ||
			itemCounter.heartNum > 0 ||
			itemCounter.squareNum > 0 ||
			itemCounter.triangleNum > 0) {

			itemCounter.crossNum = 0;
			itemCounter.heartNum = 0;
			itemCounter.maruNum = 0;
			itemCounter.squareNum = 0;
			itemCounter.triangleNum = 0;
		}
	}

	if (itemCounter.squareNum >= 1) {
		if (itemCounter.crossNum > 0 ||
			itemCounter.heartNum > 0 ||
			itemCounter.maruNum > 0 ||
			itemCounter.triangleNum > 0) {

			itemCounter.crossNum = 0;
			itemCounter.heartNum = 0;
			itemCounter.maruNum = 0;
			itemCounter.squareNum = 0;
			itemCounter.triangleNum = 0;
		}
	}

	if (itemCounter.triangleNum >= 1) {
		if (itemCounter.crossNum > 0 ||
			itemCounter.heartNum > 0 ||
			itemCounter.maruNum > 0 ||
			itemCounter.squareNum > 0) {

			itemCounter.crossNum = 0;
			itemCounter.heartNum = 0;
			itemCounter.maruNum = 0;
			itemCounter.squareNum = 0;
			itemCounter.triangleNum = 0;
		}
	}

	return itemCounter;
}