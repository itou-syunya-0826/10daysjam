#include "playerInitialize.h"
#include "Novice.h"

Player playerInitialize(Player player) {

	player.isAlive = true;

	player.img[0] = Novice::LoadTexture("./resources/player/player0.png");
	player.img[1] = Novice::LoadTexture("./resources/player/player1.png");
	player.img[2] = Novice::LoadTexture("./resources/player/player2.png");
	player.img[3] = Novice::LoadTexture("./resources/player/player3.png");

	player.size.w = 128.0f, player.size.h = 128.0f;
	player.pos = { screenWidth / 6.0f,0 };

	player.kLeftTop = { -player.size.w / 2.0f ,-player.size.h / 2.0f };
	player.kLeftBottom = { -player.size.w / 2.0f ,player.size.h / 2.0f };
	player.kRightTop = { player.size.w / 2.0f ,-player.size.h / 2.0f };
	player.kRightBottom = { player.size.w / 2.0f ,player.size.h / 2.0f };

	player.newLeftTop = { {0,0},0 };
	player.newLeftBottom = { {0,0},0 };
	player.newRightTop = { {0,0},0 };
	player.newRightBottom = { {0,0},0 };

	return player;
}
