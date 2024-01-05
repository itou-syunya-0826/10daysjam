#include "ItemSpawn.h"

int timer = 35;
int numSpawn[5];

Vector2 setDirection(Vector2 setMove) {

	int randHand = rand() % 8;

	if (randHand == 0) {
		setMove.x = 0;
		setMove.y = -1;
	}
	if (randHand == 1) {
		setMove.x = 0;
		setMove.y = sinf(0.5f * float(M_PI));
	}
	if (randHand == 2) {
		setMove.x = cosf(1.0f * float(M_PI));
		setMove.y = 0;
	}
	if (randHand == 3) {
		setMove.x = cosf(2.0f * float(M_PI));
		setMove.y = 0;
	}
	if (randHand == 4) {
		setMove.x = cosf(1.75f * float(M_PI));
		setMove.y = sinf(1.75f * float(M_PI));
	}
	if (randHand == 5) {
		setMove.x = cosf(1.25f * float(M_PI));
		setMove.y = sinf(1.25f * float(M_PI));
	}
	if (randHand == 6) {
		setMove.x = cosf(0.75f * float(M_PI));
		setMove.y = sinf(0.75f * float(M_PI));
	}
	if (randHand == 7) {
		setMove.x = cosf(0.25f * float(M_PI));
		setMove.y = sinf(0.25f * float(M_PI));
	}

	return setMove;
}

void initializeTmer()
{
	 timer = 0;
}

void ItemSpawn(Item item[5][32],float bossHP) {
	
	int itemType = cross;

	if (timer > 0) {
		timer--;
	}
	else {
		timer = 35;
	}

	if (timer == 0) {
		itemType = rand() % 15+1;

		/*switch (itemType) {*/
		/*case cross:*/
		if (itemType == 5|| itemType == 12|| itemType == 13|| itemType == 14) {
			numSpawn[0] = rand() % 3;

			for (int i = 0; i <= numSpawn[0]; i++) {
				for (int j = 0; j < 32; j++) {
					if (item[0][j].isSpawn == false) {
						item[0][j].pos.x = gentenX - 30;
						item[0][j].pos.y = gentenY - 30;
						item[0][j].move = setDirection(item[0][j].move);
						item[0][j].isSpawn = true;
						break;
					}
				}
			}

		}
			/*break;*/

		/*case heart:*/
		if (itemType == 4|| itemType == 7|| itemType == 8) {
			numSpawn[1] = rand() % 2;

			for (int i = 0; i <= numSpawn[1]; i++) {
				for (int j = 0; j < 32; j++) {
					if (item[1][j].isSpawn == false) {
						item[1][j].pos.x = gentenX - 30;
						item[1][j].pos.y = gentenY - 30;
						item[1][j].move = setDirection(item[1][j].move);
						item[1][j].isSpawn = true;
						break;
					}
				}
			}
		}
			/*break;*/

		/*case maru:*/
		if (itemType == 3 || itemType == 6) {
			numSpawn[2] = rand() % 6;

			for (int i = 0; i <= numSpawn[2]; i++) {
				for (int j = 0; j < 32; j++) {
					if (item[2][j].isSpawn == false) {
						item[2][j].pos.x = gentenX - 30;
						item[2][j].pos.y = gentenY - 30;
						item[2][j].move = setDirection(item[2][j].move);
						item[2][j].isSpawn = true;
						break;
					}
				}
			}
		}
			/*break;*/

		/*case square:*/
		if (itemType == 2|| itemType == 9|| itemType == 10|| itemType == 11) {
			numSpawn[3] = rand() % 6;

			for (int i = 0; i <= numSpawn[3]; i++) {
				for (int j = 0; j < 32; j++) {
					if (item[3][j].isSpawn == false) {
						item[3][j].pos.x = kWindowWidth / 2 - 30;
						item[3][j].pos.y = kWindowHeight / 2 - 30;
						item[3][j].move = setDirection(item[3][j].move);
						item[3][j].isSpawn = true;
						break;
					}
				}
			}
		}
			/*break;*/

		/*case triangle:*/
		if (bossHP <= 200) {
			if (itemType == 1 || itemType == 15) {
				numSpawn[4] = rand() % 4;

				for (int i = 0; i <= numSpawn[4]; i++) {

					for (int j = 0; j < 32; j++) {
						if (item[4][j].isSpawn == false) {
							item[4][j].pos.x = kWindowWidth / 2 - 30;
							item[4][j].pos.y = kWindowHeight / 2 - 30;
							item[4][j].move = setDirection(item[4][j].move);
							item[4][j].isSpawn = true;
							break;
						}
					}
				}
			}
		}	/*break;*/
		//}
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 32; j++) {
			
			item[i][j].pos.x += item[i][j].move.x * item[i][j].speed;
			item[i][j].pos.y += item[i][j].move.y * item[i][j].speed;

				if (item[i][j].pos.y <= 0 - item[i][j].size.h / 2.0f || item[i][j].pos.y >= kWindowHeight - item[i][j].size.h) {
					item[i][j].isSpawn = false;
				}
				if (item[i][j].pos.x >= kWindowWidth - item[i][j].size.w || item[i][j].pos.x <= 0 + item[i][j].size.w) {
					item[i][j].isSpawn = false;
				}
		}
	}
//	Novice::ScreenPrintf(10, 30, "timer: %d", timer);
}

