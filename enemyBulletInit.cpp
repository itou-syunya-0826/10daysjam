#include "enemyBulletInit.h"
#include "Novice.h"

Bullet enemyBulletInit(Bullet enemyBullet) {
	
	for (int i = 0; i < 5; i++) {
		enemyBullet.isShot[i] = false;
		enemyBullet.isHit[i] = false;
		enemyBullet.t[i] = 0;
	}

	enemyBullet.ani[0] = 60;
	enemyBullet.ani[3] = 120;
	enemyBullet.color = WHITE;
	enemyBullet.speed = 10.0f;
	enemyBullet.size[0] = {104.0f, 64.0f};
	enemyBullet.size[1] = {64.0f,64.0f};

	enemyBullet.size[2] = { 64.0f,64.0f };

	enemyBullet.img[0][0] = Novice::LoadTexture("./resources/enemy/enemyAtk/enemyBeam_1-1.png");
	enemyBullet.img[0][1] = Novice::LoadTexture("./resources/enemy/enemyAtk/enemyBeam_1-2.png");

	enemyBullet.img[1][0] = Novice::LoadTexture("./resources/enemy/enemyAtk/enemyBeam_2-1.png");

	enemyBullet.img[3][0] = Novice::LoadTexture("./resources/itemSprites/enemyAtt1.png");
	enemyBullet.img[3][1] = Novice::LoadTexture("./resources/itemSprites/enemyAtt2.png");
	enemyBullet.img[3][2] = Novice::LoadTexture("./resources/itemSprites/enemyAtt3.png");
	enemyBullet.img[3][3] = Novice::LoadTexture("./resources/itemSprites/enemyAtt4.png");

	enemyBullet.img[4][0] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_1_1.png");
	enemyBullet.img[4][1] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_1_2.png");
	enemyBullet.img[4][2] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_1_3.png");
	enemyBullet.img[4][3] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_1_4.png");
	enemyBullet.img[4][4] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_1_5.png");
	
																								  
	enemyBullet.img[5][0] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_2_1.png");
	enemyBullet.img[5][1] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_2_2.png");
	enemyBullet.img[5][2] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_2_3.png");
	enemyBullet.img[5][3] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_2_4.png");
	enemyBullet.img[5][4] = Novice::LoadTexture("./resources/enemy/enemyAtk/PJWH_Enemy_AttackEff_2_5.png");
	

	enemyBullet.pos[0] = { 392,0 };
	enemyBullet.kLeftTop[0] = { -enemyBullet.size[0].w / 2.0f ,-enemyBullet.size[0].h / 2.0f };
	enemyBullet.kLeftBottom[0] = { -enemyBullet.size[0].w / 2.0f ,enemyBullet.size[0].h / 2.0f };
	enemyBullet.kRightTop[0] = { enemyBullet.size[0].w / 2.0f ,-enemyBullet.size[0].h / 2.0f };
	enemyBullet.kRightBottom[0] = { enemyBullet.size[0].w / 2.0f ,enemyBullet.size[0].h / 2.0f };

	enemyBullet.pos[1] = { 316,0 };   //342
	enemyBullet.pos[2] = { 260,0 };	  //300
	enemyBullet.pos[3] = { 204,0 };	  //250
	enemyBullet.pos[4] = { 148,0 };	  //202
	enemyBullet.pos[5] = { 92,0 };	  //160
	enemyBullet.pos[6] = { 36,0 };	  //110
	enemyBullet.pos[7] = { -20,0 };	  //60

	for (int i = 1; i < 8; i++) {
		enemyBullet.kLeftTop[i] = { -enemyBullet.size[1].w / 2.0f ,-enemyBullet.size[1].h / 2.0f };
		enemyBullet.kLeftBottom[i] = { -enemyBullet.size[1].w / 2.0f ,enemyBullet.size[1].h / 2.0f };
		enemyBullet.kRightTop[i] = { enemyBullet.size[1].w / 2.0f ,-enemyBullet.size[1].h / 2.0f };
		enemyBullet.kRightBottom[i] = { enemyBullet.size[1].w / 2.0f ,enemyBullet.size[1].h / 2.0f };

		enemyBullet.img[1][i] = Novice::LoadTexture("./resources/enemy/enemyAtk/enemyBeam_2-1.png");
		enemyBullet.img[2][i] = Novice::LoadTexture("./resources/enemy/enemyAtk/enemyBeam_2-2.png");
	}

	return enemyBullet;
}