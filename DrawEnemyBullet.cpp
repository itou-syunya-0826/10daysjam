#include "DrawEnemyBullet.h"
#include "Novice.h"

int kirikae = 0;
int kirikae1 = 1;
int effect = 4;
int effect1 = 0;

Bullet DrawEnemyBullet(Bullet enemyBullet) {
	if (enemyBullet.isShot[0] == true){
		enemyBullet.ani[0]--;
		enemyBullet.ani[3]--;

		if ((int)enemyBullet.ani[0] % 30 == 0) {
			kirikae = 1;
			kirikae1 = 2;
			effect = 5;
			if (enemyBullet.ani[0] == 0) {
				enemyBullet.ani[0] = 60;
				kirikae = 0;
				kirikae1 = 1;
				effect = 4;
			}
		}
		if ((int)enemyBullet.ani[3] % 24 == 0) {
			effect1 += 1;
			if (effect1 == 4) {
				effect1 = 0;
				enemyBullet.ani[3] = 120;
			}
		}
	

		Novice::DrawQuad(
			(int)enemyBullet.newLeftTop[0].position.x,
			(int)enemyBullet.newLeftTop[0].position.y,
			(int)enemyBullet.newRightTop[0].position.x,
			(int)enemyBullet.newRightTop[0].position.y,
			(int)enemyBullet.newLeftBottom[0].position.x,
			(int)enemyBullet.newLeftBottom[0].position.y,
			(int)enemyBullet.newRightBottom[0].position.x,
			(int)enemyBullet.newRightBottom[0].position.y, 0, 0, 104, 64, enemyBullet.img[0][kirikae], enemyBullet.color
		);

		for (int i = 1; i < 8; i++) {
			Novice::DrawQuad(
				(int)enemyBullet.newLeftTop[i].position.x,
				(int)enemyBullet.newLeftTop[i].position.y,
				(int)enemyBullet.newRightTop[i].position.x,
				(int)enemyBullet.newRightTop[i].position.y,
				(int)enemyBullet.newLeftBottom[i].position.x,
				(int)enemyBullet.newLeftBottom[i].position.y,
				(int)enemyBullet.newRightBottom[i].position.x,
				(int)enemyBullet.newRightBottom[i].position.y, 0, 0, 64, 64, enemyBullet.img[kirikae1][i], enemyBullet.color
			);
		}
		for (int i = 0; i < 5; i++) {
			Novice::DrawQuad(
				(int)enemyBullet.newLeftTop[i].position.x,
				(int)enemyBullet.newLeftTop[i].position.y,
				(int)enemyBullet.newRightTop[i].position.x,
				(int)enemyBullet.newRightTop[i].position.y,
				(int)enemyBullet.newLeftBottom[i].position.x,
				(int)enemyBullet.newLeftBottom[i].position.y,
				(int)enemyBullet.newRightBottom[i].position.x,
				(int)enemyBullet.newRightBottom[i].position.y, 0, 0, 64, 64, enemyBullet.img[effect][effect1], enemyBullet.color
			);
		}
		for (int i = 5; i < 8; i++) {
			Novice::DrawQuad(
				(int)enemyBullet.newLeftTop[i].position.x,
				(int)enemyBullet.newLeftTop[i].position.y,
				(int)enemyBullet.newRightTop[i].position.x,
				(int)enemyBullet.newRightTop[i].position.y,
				(int)enemyBullet.newLeftBottom[i].position.x,
				(int)enemyBullet.newLeftBottom[i].position.y,
				(int)enemyBullet.newRightBottom[i].position.x,
				(int)enemyBullet.newRightBottom[i].position.y, 0, 0, 64, 64, enemyBullet.img[effect][effect1], enemyBullet.color
			);
		}
	}

	if (enemyBullet.isShot[1] == true) {
		for (int i = 0; i < 4; i++) {
			Novice::DrawSprite((int)enemyBullet.position.x, (int)enemyBullet.position.y, enemyBullet.img[3][i], 1.0f, 1.0f, enemyBullet.angle, WHITE);
		}
	}
	return enemyBullet;
}