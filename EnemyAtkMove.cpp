#include "EnemyAtkMove.h"
#include "enemyrotate.h"

Bullet enemyAtkMove(Bullet enemyBullet, Player player,float timer) {

	if (enemyBullet.bulletType == 0 && enemyBullet.isShot[0] == true) {

		for (int i = 0; i < 8; i++) {
			enemyBullet.newLeftBottom[i] = MoveEnemyBullet(enemyBullet.pos[i], enemyBullet.kLeftBottom[i]);
			enemyBullet.newLeftTop[i] = MoveEnemyBullet(enemyBullet.pos[i], enemyBullet.kLeftTop[i]);
			enemyBullet.newRightBottom[i] = MoveEnemyBullet(enemyBullet.pos[i], enemyBullet.kRightBottom[i]);
			enemyBullet.newRightTop[i] = MoveEnemyBullet(enemyBullet.pos[i], enemyBullet.kRightTop[i]);
		}
		enemyBullet.t[0]--;
		if (enemyBullet.t[0] <= 0) {
			enemyBullet.isShot[0] = false;
		}
	}

	if (timer > 0) {
		if (enemyBullet.position.x <= player.newLeftTop.position.x + 500 && enemyBullet.position.y <= player.newLeftTop.position.y + 200) {
			enemyBullet.distance[0].x = player.newLeftTop.position.x - enemyBullet.position.x;
			enemyBullet.distance[0].y = player.newLeftTop.position.y - enemyBullet.position.y;

			enemyBullet.length[0] = sqrtf(powf(enemyBullet.distance[0].x, 2) + powf(enemyBullet.distance[0].y, 2));

			if (enemyBullet.length != 0) {
				enemyBullet.distance[0].x /= enemyBullet.length[0];
				enemyBullet.distance[0].y /= enemyBullet.length[0];
			}
		}
	}	
	enemyBullet.angle = atan2f(enemyBullet.distance[0].y, enemyBullet.distance[0].x);

	enemyBullet.position.x += enemyBullet.distance[0].x * enemyBullet.speed;
	enemyBullet.position.y += enemyBullet.distance[0].y * enemyBullet.speed;
		
	
	return enemyBullet;
}