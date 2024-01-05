#include "enemyRotate.h"
#include "myStructs.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <Novice.h>

PoitionAndAngle enemyPosition = { { 0,0 },float(M_PI)/2*-1 };
//enemyPosition.angle = float(M_PI);
float moveEnemyTime = 120;
int moveEnemyType = 0;
PositionAndAngle enemyBulletPos = { 0 };
float moveEnemyTime1 = 120;
int moveEnemyType1 = 0;

PositionAndAngle MoveEnemy(Vector2 enemyObject, Vector2 vertex,float bossHp) {
	if (bossHp>= 350) {
		enemyPosition.angle = float(M_PI) / 2 * -1;
		enemyPosition.type = 3;
	}
	float theta = enemyPosition.angle;
	float leftPosX = vertex.x + enemyObject.x;
	float leftPosY = vertex.y + enemyObject.y;
	//theta = 0;
	if (moveEnemyTime > 0) {
		moveEnemyTime--;
	}
	else {
		moveEnemyTime = 300;
	}

	if (moveEnemyTime <= 0&& bossHp <= 350) {
		enemyPosition.type = rand() % 2;
	}
	if (bossHp > 200) {
		if (enemyPosition.type == 0) {
			theta -= 1.0f / 2000.0f * float(M_PI);
			/*theta -= 0.05f;*/
		}

		if (enemyPosition.type == 1) {
			theta += 1.0f / 2000.0f * float(M_PI);
			/*theta += 0.05f;*/
		}
	}
	if (bossHp <= 200) {
		if (enemyPosition.type == 0) {
			theta -= 1.0f / 1800.0f * float(M_PI);
			/*theta -= 0.05f;*/
		}

		if (enemyPosition.type == 1) {
			theta += 1.0f / 1800.0f * float(M_PI);
			/*theta += 0.05f;*/
		}
	}
	if (bossHp <= 100) {
		if (enemyPosition.type == 0) {
			theta -= 1.0f / 1700.0f * float(M_PI);
			/*theta -= 0.05f;*/
		}

		if (enemyPosition.type == 1) {
			theta += 1.0f / 1700.0f * float(M_PI);
			/*theta += 0.05f;*/
		}
	}
	float leftTopRotateX = leftPosX * cosf(theta) - leftPosY * sinf(theta);
	float leftTopRotateY = leftPosY * cosf(theta) + leftPosX * sinf(theta);

	enemyPosition.position = { leftTopRotateX + screenWidth / 2, leftTopRotateY + screenHeight / 2 };
	enemyPosition.angle = theta;
	enemyBulletPos.angle = enemyPosition.angle;

	//Novice::ScreenPrintf(0, 0, "%f", theta);

	return enemyPosition;

}

PositionAndAngle MoveEnemyBullet(Vector2 enemyObject, Vector2 vertex) {

	float theta = enemyBulletPos.angle;
	float leftPosX = vertex.x + enemyObject.x;
	float leftPosY = vertex.y + enemyObject.y;
	if (moveEnemyTime1 > 0) {
		moveEnemyTime1--;
	}
	else {
		moveEnemyTime1 = 120;
	}

	if (moveEnemyTime1 <= 0) {
		moveEnemyType1 = rand() % 2;
	}
	if (moveEnemyType1 == 0) {
		theta -= 1.0 / 240.0f * float(M_PI);
		/*theta -= 0.05f;*/
	}

	if (moveEnemyType1 == 1) {
		theta += 1.0 / 240.0f * float(M_PI);
		/*theta += 0.05f;*/
	}
	float leftTopRotateX = leftPosX * cosf(theta) - leftPosY * sinf(theta);
	float leftTopRotateY = leftPosY * cosf(theta) + leftPosX * sinf(theta);

	enemyBulletPos.position = { leftTopRotateX + screenWidth / 2, leftTopRotateY + screenHeight / 2 };

	return enemyBulletPos;

}