#include "itemInitialize.h"
#include "Novice.h"

void itemInitialize(Item item[ITEMTYPE][ITEMNUM]) {
	for (int i = 0; i < 32; i++) {
		item[0][i].img = Novice::LoadTexture("./resources/itemSprites/Item_Cross.png");			 //cross
		item[1][i].img = Novice::LoadTexture("./resources/itemSprites/Item_Heart.png");			 //heart
		item[2][i].img = Novice::LoadTexture("./resources/itemSprites/Item_Round.png");			 //round
		item[3][i].img = Novice::LoadTexture("./resources/itemSprites/Item_Square.png");			 //square
		item[4][i].img = Novice::LoadTexture("./resources/itemSprites/Item_Triangle.png");			//triangle
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 32; j++) {
			item[i][j].color = WHITE;
			item[i][j].speed = 5.0f;
			item[i][j].size.h = 64.0f;
			item[i][j].size.w = 64.0f;
		}
	}
}