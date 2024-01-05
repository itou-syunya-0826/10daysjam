#include "DrawPlayer.h"
#include "Novice.h"

Player DrawPlayer(Player player) {
	if (player.isAlive == true) {
		for (int i = 0; i < 4; i++) {
			player.ani += 1;
			if (player.ani >= i * 15 && player.ani <= (i * 15) + 15) {
				Novice::DrawQuad(
					(int)player.newLeftTop.position.x,
					(int)player.newLeftTop.position.y,
					(int)player.newRightTop.position.x,
					(int)player.newRightTop.position.y,
					(int)player.newLeftBottom.position.x,
					(int)player.newLeftBottom.position.y,
					(int)player.newRightBottom.position.x,
					(int)player.newRightBottom.position.y, 0, 0, 128, 128, player.img[i], WHITE
				);
			}
		}
		if (player.ani >= 60) {
			player.ani = 0;
		}
	}
	return player;
}
