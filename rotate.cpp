#include "rotate.h"
#include "myStructs.h"
//#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
PositionAndAngle object = { {0,0}, float(M_PI)/2*-1};
PositionAndAngle object1;
PositionAndAngle object2;

PositionAndAngle MovePlayer(char keys[], Vector2 pos, Vector2 vertex, float playerHP,bool isStart) {

	if (playerHP >= 384&&!isStart) {
		object.angle = float(M_PI) / 2 * -1;
	}
	float theta = object.angle;
	float posX = vertex.x + pos.x;
	float posY = vertex.y + pos.y;
	if (isStart) {
		if (!keys[DIK_LSHIFT] && !keys[DIK_RSHIFT]) {
			if (keys[DIK_RIGHT] || keys[DIK_D]) {
				theta -= 1.0f / 600.0f * float(M_PI);
				/*theta -= 0.05f;*/
			}

			if (keys[DIK_LEFT] || keys[DIK_A]) {
				theta += 1.0f / 600.0f * float(M_PI);
				/*theta += 0.05f;*/
			}
		}
		if (keys[DIK_LSHIFT] || keys[DIK_RSHIFT]) {
			if ((keys[DIK_RIGHT] || keys[DIK_D])/*&& object.stamina!=0*/) {
				//object.stamina--;
				theta -= 1.0f / 800.0f * float(M_PI);
			}
			if ((keys[DIK_LEFT] || keys[DIK_A]) /*&& object.stamina != 0*/) {
				//object.stamina--;
				theta += 1.0f / 800.0f * float(M_PI);
			}
		}
	}
	/*if (!keys[DIK_LSHIFT]) {
		object.stamina++;
	}
	if (object.stamina > 180) {
		object.stamina = 180;
	}*/
	float playerTopRotateX = posX * cosf(theta) - posY * sinf(theta);
	float playerTopRotateY = posY * cosf(theta) + posX * sinf(theta);
	
	object.position = { playerTopRotateX + kWindowWidth / 2, playerTopRotateY + kWindowHeight / 2 };
	object.angle = theta;
	object1.angle = object.angle;

	/*Novice::ScreenPrintf(0, 0, "%f", object.stamina);*/
	return object;
}

PositionAndAngle MoveBullet(char keys[], Vector2 pos, Vector2 vertex) {

	float theta = object1.angle;
	float posX1 = vertex.x + pos.x;
	float posY1 = vertex.y + pos.y;

	if (keys[DIK_RIGHT] || keys[DIK_D]) {
		theta -= 1.0 / 120.0f * float(M_PI);
		/*theta -= 0.05f;*/
	}

	if (keys[DIK_LEFT] || keys[DIK_A]) {
		theta += 1.0 / 120.0f * float(M_PI);
		/*theta += 0.05f;*/
	}
	float playerTopRotateX1 = posX1 * cosf(theta) - posY1 * sinf(theta);
	float playerTopRotateY1 = posY1 * cosf(theta) + posX1 * sinf(theta);

	object1.position = { playerTopRotateX1 + kWindowWidth / 2, playerTopRotateY1 + kWindowHeight / 2 };

	return object1;
}

PositionAndAngle TransferAngle(PositionAndAngle squareTama) {
	squareTama.position.x = object.position.x;
	squareTama.position.y = object.position.y;

	squareTama.angle = object.angle;
	return squareTama;
}