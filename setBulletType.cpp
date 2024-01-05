#include "setBulletType.h"
#include "chkItemCounter.h"
#include "easing.h"
#include "Novice.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "IsPlaySE.h"

Bullet setBulletType(char keys[], char preKeys[], Bullet bullet, ItemCounter &itemCounter, Player player, SEHandler soundEffect) {

	if (keys[DIK_SPACE] &&
		!preKeys[DIK_SPACE] &&
		itemCounter.heartNum >= 3) {





	}

	if (keys[DIK_SPACE] &&
		!preKeys[DIK_SPACE] &&
		itemCounter.maruNum >= 3) {

		IsPlaySE(soundEffect.audio[maru], soundEffect.handler[maru], soundEffect.count[maru], 5);

		bullet.position.x = player.newLeftTop.position.x + player.size.w / 2;
		bullet.position.y = player.newLeftTop.position.y + player.size.h / 2;

		bullet.bulletType = maru;
		bullet.isShot[maru] = true;
		itemCounter.maruNum = 0;
	}

	bullet.target[0] = player.newRightTop.position;

	if (!bullet.isShot[square]) {
		bullet.pos[8].x = player.newLeftTop.position.x;
		bullet.pos[8].y = player.newLeftTop.position.y;
	}

	if (keys[DIK_SPACE] &&
		!preKeys[DIK_SPACE] &&
		itemCounter.squareNum >= 3) {

		IsPlaySE(soundEffect.audio[square], soundEffect.handler[square], soundEffect.count[square], 5);

		bullet.bulletType = square;
		bullet.isShot[square] = true;
		itemCounter.squareNum = 0;

		bullet.distance[0].x = bullet.target[0].x - bullet.pos[8].x;
		bullet.distance[0].y = bullet.target[0].y - bullet.pos[8].y;

		bullet.length[0] = sqrtf(powf(bullet.distance[0].x, 2) + powf(bullet.distance[0].y, 2));

		if (bullet.length[0] != 0) {
			bullet.distance[0].x /= bullet.length[0];
			bullet.distance[0].y /= bullet.length[0];
		}

		bullet.angle = atan2f(bullet.distance[0].y, bullet.distance[0].x);
	}

	if (keys[DIK_SPACE] &&
		!preKeys[DIK_SPACE] &&
		itemCounter.triangleNum >= 3) {

		IsPlaySE(soundEffect.audio[triangle], soundEffect.handler[triangle], soundEffect.count[triangle], 5);

		bullet.bulletType = triangle;
		bullet.t[triangle] = 180.0f;
		bullet.isShot[triangle] = true;
		itemCounter.triangleNum = 0;
	}
	return bullet;
}