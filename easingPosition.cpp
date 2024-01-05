#include "easingPosition.h"

#include "easing.h"
#include "myStructs.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

//bool isEasing = true;
Vector2 EasingPosition(Vector2 begingPoint, Vector2 endPoint, int type, float t) {
	float easedT = 0;
	if (t >= 1) {
		/*isEasing = false;*/
		t = 1;
	}
	if (t < 0) {
		t = 0;
	}

	/*t = 0;
	easedT = 0;
	speed = 0;*/
	/*isEasing = true;*/

	Vector2 result = { 0 };
	/*if (result.x <= 0 || result.y <= 0 && t == 1||speed==1) {
		t = 0;
		speed = 0;
	}*/

	easedT = Easing(type, t);
	result.x = (1 - easedT) * begingPoint.x + easedT * endPoint.x;
	result.y = (1 - easedT) * begingPoint.y + easedT * endPoint.y;

	/*if (!isEasing) {
		t = 0;
		speed = 0;
	}*/
	//Novice::ScreenPrintf(0, 0, "%f", t);
	return result;
}