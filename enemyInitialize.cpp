#include "enemyInitialize.h"
#include "Novice.h"

Enemy enemyInitialize(Enemy enemy) {

	enemy.size.w = 128.0f, enemy.size.h = 128.0f;
	enemy.ani[1] = 60;
	enemy.color = WHITE;

	enemy.kLeftEnemyTop = { -enemy.size.w / 2.0f ,-enemy.size.h / 2.0f };
	enemy.kLeftEnemyBottom = { -enemy.size.w / 2.0f ,enemy.size.h / 2.0f };
	enemy.kRightEnemyTop = { enemy.size.w / 2.0f ,-enemy.size.h / 2.0f };
	enemy.kRightEnemyBottom = { enemy.size.w / 2.0f ,enemy.size.h / 2.0f };

	enemy.newLeftEnemyTop = { {0,0},0 };
	enemy.newLeftEnemyBottom = { {0,0},0 };
	enemy.newRightEnemyTop = { {0,0},0 };
	enemy.newRightEnemyBottom = { {0,0},0 };

	enemy.pos = { 500,0 };

	enemy.img[0] = Novice::LoadTexture("./resources/enemy/PJWH_Enemy0.png");
	enemy.img[1] = Novice::LoadTexture("./resources/enemy/PJWH_Enemy1.png");
	enemy.img[2] = Novice::LoadTexture("./resources/enemy/PJWH_Enemy2.png");
	enemy.img[3] = Novice::LoadTexture("./resources/enemy/PJWH_Enemy3.png");

	enemy.bakuhatu[0] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion0.png");
	enemy.bakuhatu[1] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion1.png");
	enemy.bakuhatu[2] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion2.png");
	enemy.bakuhatu[3] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion3.png");
	enemy.bakuhatu[4] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion4.png");
	enemy.bakuhatu[5] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion5.png");
	enemy.bakuhatu[6] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion6.png");
	enemy.bakuhatu[7] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion7.png");
	enemy.bakuhatu[8] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion8.png");
	enemy.bakuhatu[9] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion9.png");
	enemy.bakuhatu[10] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion10.png");
	enemy.bakuhatu[11] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion11.png");
	enemy.bakuhatu[12] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion12.png");
	enemy.bakuhatu[13] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion13.png");
	enemy.bakuhatu[14] = Novice::LoadTexture("./resources/enemy/PJWH_Explosion14.png");

	enemy.texture[0] = Novice::LoadTexture("./resources/enemy/enemy1.png");
	enemy.texture[1] = Novice::LoadTexture("./resources/enemy/enemy2.png");
	enemy.texture[2] = Novice::LoadTexture("./resources/enemy/enemy3.png");
	enemy.texture[3] = Novice::LoadTexture("./resources/enemy/enemy4.png");
	enemy.texture[4] = Novice::LoadTexture("./resources/enemy/enemy5.png");
	enemy.texture[5] = Novice::LoadTexture("./resources/enemy/enemy6.png");
	enemy.texture[6] = Novice::LoadTexture("./resources/enemy/enemy7.png");
	enemy.texture[7] = Novice::LoadTexture("./resources/enemy/enemy8.png");
	enemy.texture[8] = Novice::LoadTexture("./resources/enemy/enemy9.png");
	enemy.texture[9] = Novice::LoadTexture("./resources/enemy/enemy10.png");
	enemy.texture[10] = Novice::LoadTexture("./resources/enemy/enemy11.png");
	return enemy;
}