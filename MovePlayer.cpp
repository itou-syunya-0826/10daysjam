#include "MovePlayer.h"
#include "Novice.h"
#include "myStructs.h"
#define _USE_MATH_DEFINES
#include <math.h>

PositionAndAngle movePlayer(char keys[], PositionAndAngle genzaichi)
{
	float theta2 = genzaichi.angle;
	float newposx1 = genzaichi.position.x;
	float newposy1 = genzaichi.position.y;

	float posX1 = 100.0f, posY1 = 150.0f;

	float genTenX = kWindowWidth / 2;
	float genTenY = kWindowHeight / 2;

	newposx1 = posX1 * cosf(theta2) + genTenX - posY1 * sinf(theta2);
	newposy1 = posY1 * cosf(theta2) + genTenY + posX1 * sinf(theta2);

	if (keys[DIK_A]) {
		theta2 += 0.05f;
	}
	if (keys[DIK_D]) {
		theta2 -= 0.05f;
		newposx1 = posX1 * cosf(theta2) + genTenX - posY1 * sinf(theta2);
		newposy1 = posY1 * cosf(theta2) + genTenY + posX1 * sinf(theta2);
	}

	genzaichi.position.x = newposx1;
	genzaichi.position.y = newposy1;
	genzaichi.angle = theta2;

	return genzaichi;
}

