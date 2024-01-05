#include "DrawBullet.h"
#include "Novice.h"

int kirikae2 = 0;

Bullet DrawBullet(Bullet bullet) {

	if (bullet.isShot[maru] == true) {
		for (int i = 0; i < 8; i++) {
			bullet.ani[maru] += 0.5f;
			if (bullet.ani[maru] >= i * 15.0f && bullet.ani[maru] <= (i * 15.0f) + 15.0f) {
				Novice::DrawSprite((int)bullet.position.x + (int)bullet.size[maru].w / 2, (int)bullet.position.y - (int)bullet.size[maru].h / 2, bullet.img[maru][i], 1.0f, 1.0f, bullet.angle, bullet.color);
			}
		}
		if (bullet.ani[maru] >= 120) {
			bullet.ani[maru] = 0.0f;
		}
	}

	if (bullet.isShot[triangle] == true) {

		bullet.ani[triangle]--;

		if ((int)bullet.ani[triangle] % 10 == 0) {
			kirikae2 = 0;
			if (bullet.ani[triangle] == 0) {
				bullet.ani[triangle] = 30;
				kirikae2 = 1;
			}
		}
		Novice::DrawQuad(
			(int)bullet.newLeftTop[0].position.x,
			(int)bullet.newLeftTop[0].position.y,
			(int)bullet.newRightTop[0].position.x,
			(int)bullet.newRightTop[0].position.y,
			(int)bullet.newLeftBottom[0].position.x,
			(int)bullet.newLeftBottom[0].position.y,
			(int)bullet.newRightBottom[0].position.x,
			(int)bullet.newRightBottom[0].position.y, 0, 0, 64, 64, bullet.img[triangle][kirikae2], WHITE
		);
		for (int i = 1; i < 8; i++) {
			Novice::DrawQuad(
				(int)bullet.newLeftTop[i].position.x,
				(int)bullet.newLeftTop[i].position.y,
				(int)bullet.newRightTop[i].position.x,
				(int)bullet.newRightTop[i].position.y,
				(int)bullet.newLeftBottom[i].position.x,
				(int)bullet.newLeftBottom[i].position.y,
				(int)bullet.newRightBottom[i].position.x,
				(int)bullet.newRightBottom[i].position.y, 0, 0, 64, 64, bullet.img[kirikae2][i], WHITE
			);
		}
	}
	if (bullet.isShot[square] == true) {
		for (int i = 0; i < 4; i++) {
			bullet.ani[square] += 3;
			if (bullet.ani[square] >= i * 15.0f && bullet.ani[square] <= (i * 15.0f) + 15.0f) {
				Novice::DrawSprite((int)bullet.pos[8].x, (int)bullet.pos[8].y, bullet.img[square][i], 1.0f, 1.0f, bullet.angle, bullet.color);
				//Novice::DrawSprite((int)bullet.pos[square + 2].x, (int)bullet.pos[square + 2].y, bullet.img[square][i], 3.0f, 3.0f, bullet.angle1, bullet.color);
			}
		}
		if (bullet.ani[square] == 60) {
			bullet.ani[square] = 0;
		}
	}
	return bullet;
}