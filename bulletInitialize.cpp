#include "bulletInitialize.h"
#include "Novice.h"

Bullet bulletInitialize(Bullet bullet) {

	bullet.speed = 10.0f;
	
	bullet.color = WHITE;
	bullet.ani[triangle] = 60;

	for (int i = 0; i < 5; i++) {
		bullet.isHit[i] = false;
		bullet.isShot[i] = false;
		bullet.t[i] = false;
	}
	
	bullet.size[cross] = { 0 };
	bullet.size[heart] = { 0 };
	bullet.size[maru] = {96.0f, 96.0f};
	bullet.size[square] = { 64.0f, 64.0f };
	bullet.size[triangle] = { 64.0f, 64.0f };

	bullet.img[maru][0] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt0.png");
	bullet.img[maru][1] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt1.png");
	bullet.img[maru][2] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt2.png");
	bullet.img[maru][3] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt3.png");
	bullet.img[maru][4] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt4.png");
	bullet.img[maru][5] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt5.png");
	bullet.img[maru][6] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt6.png");
	bullet.img[maru][7] = Novice::LoadTexture("./resources/itemSprites/Player_BuleAtt7.png");

	bullet.img[triangle][0] = Novice::LoadTexture("./resources/itemSprites/triangle_atk1-1.png");
	bullet.img[triangle][1] = Novice::LoadTexture("./resources/itemSprites/triangle_atk2-1.png");
	bullet.img[0][0] = Novice::LoadTexture("./resources/itemSprites/triangle_atk1-2.png");
	bullet.img[0][1] = Novice::LoadTexture("./resources/itemSprites/triangle_atk2-2.png");

	bullet.img[square][0] = Novice::LoadTexture("./resources/itemSprites/PJWH_Player_GreenAtt1.png");
	bullet.img[square][1] = Novice::LoadTexture("./resources/itemSprites/PJWH_Player_GreenAtt2.png");
	bullet.img[square][2] = Novice::LoadTexture("./resources/itemSprites/PJWH_Player_GreenAtt3.png");
	bullet.img[square][3] = Novice::LoadTexture("./resources/itemSprites/PJWH_Player_GreenAtt4.png");

	bullet.pos[0] = { 385.5f,0 };
	bullet.pos[1] = { 435.0f,0 };
	bullet.pos[2] = { 480.0f,0 };
	bullet.pos[3] = { 530.0f,0 };
	bullet.pos[4] = { 580.0f,0 };
	bullet.pos[5] = { 630.0f,0 };
	bullet.pos[6] = { 680.0f,0 };
	bullet.pos[7] = { 730.0f,0 };

	for (int i = 0; i < 8; i++) {
		bullet.kLeftTop[i] = { -bullet.size[triangle].w / 2.0f ,-bullet.size[triangle].h / 2.0f };
		bullet.kLeftBottom[i] = { -bullet.size[triangle].w / 2.0f ,bullet.size[triangle].h / 2.0f };
		bullet.kRightTop[i] = { bullet.size[triangle].w / 2.0f ,-bullet.size[triangle].h / 2.0f };
		bullet.kRightBottom[i] = { bullet.size[triangle].w / 2.0f ,bullet.size[triangle].h / 2.0f };

		bullet.img[0][i] = Novice::LoadTexture("./resources/itemSprites/triangle_atk1-2.png");
		bullet.img[1][i] = Novice::LoadTexture("./resources/itemSprites/triangle_atk2-2.png");
	}

	/*bullet.pos[2] = { screenWidth / 7.0f,0 };
	bullet.kLeftTop[2] = { -bullet.size[square].w / 2.0f ,-bullet.size[square].h / 2.0f };
	bullet.kLeftBottom[2] = { -bullet.size[square].w / 2.0f ,bullet.size[square].h / 2.0f };
	bullet.kRightTop[2] = { bullet.size[square].w / 2.0f ,-bullet.size[square].h / 2.0f };
	bullet.kRightBottom[2] = { bullet.size[square].w / 2.0f ,bullet.size[square].h / 2.0f };*/

	return bullet;
}