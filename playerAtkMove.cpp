#include "playerAtkMove.h"
#include "rotate.h"

Bullet playerAtkMove(char keys[], Bullet bullet, Enemy enemy) {

	if (bullet.isShot[maru] == true) {

		bullet.distance[maru].x = enemy.newLeftEnemyBottom.position.x - bullet.position.x;
		bullet.distance[maru].y = enemy.newLeftEnemyBottom.position.y - bullet.position.y;

		bullet.length[maru] = sqrtf(powf(bullet.distance[maru].x, 2) + powf(bullet.distance[maru].y, 2));

		if (bullet.length[maru] != 0) {
			bullet.distance[maru].x /= bullet.length[maru];
			bullet.distance[maru].y /= bullet.length[maru];

		}
		bullet.angle = atan2f(bullet.distance[maru].y, bullet.distance[maru].x);

		bullet.position.x += bullet.distance[maru].x * bullet.speed;
		bullet.position.y += bullet.distance[maru].y * bullet.speed;

	}

	if (bullet.isShot[square] == true) {

		bullet.pos[8].x += bullet.distance[0].x * bullet.speed;
		bullet.pos[8].y += bullet.distance[0].y * bullet.speed;

		//off screen limit
		if (bullet.pos[8].x >= kWindowWidth - bullet.size[square].w ||
			bullet.pos[8].x <= 0 + bullet.size[square].w) {
			bullet.isShot[square] = false;
		}
		if (bullet.pos[8].y >= kWindowHeight + bullet.size[square].h ||
			bullet.pos[8].y <= 0 - bullet.size[square].h) {
			bullet.isShot[square] = false;
		}
	}

	if (bullet.isShot[triangle] == true) {

		for (int i = 0; i < 8; i++) {
			bullet.newLeftBottom[i] = MoveBullet(keys, bullet.pos[i], bullet.kLeftBottom[i]);
			bullet.newLeftTop[i] = MoveBullet(keys, bullet.pos[i], bullet.kLeftTop[i]);
			bullet.newRightBottom[i] = MoveBullet(keys, bullet.pos[i], bullet.kRightBottom[i]);
			bullet.newRightTop[i] = MoveBullet(keys, bullet.pos[i], bullet.kRightTop[i]);
		}
		
		bullet.t[triangle]--;
		if (bullet.t[triangle] <= 0) {
			bullet.isShot[triangle] = false;
		}
	}
	return bullet;
}
