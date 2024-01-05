#include "easing.h"
#include "myStructs.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <Novice.h>

//bool isEasing = true;
float Easing(int type,float t) {
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
	
	
	/*if (result.x <= 0 || result.y <= 0 && t == 1||speed==1) {
		t = 0;
		speed = 0;
	}*/

		/*if (isEasing) {*/
		if (type == 1) {
			//t += 1.0f / timeDestination;
			easedT = t * t;
		}

		else if (type == 2) {
			
			//t += 1.0f / timeDestination;
			easedT = 1.0f - powf(1.0f - t, 3.0);
		}

		else if (type == 3) {
			
			easedT = -(cosf(float(M_PI) * t) - 1.0f) / 2.0f;
		}
		//}
		
		
		/*if (!isEasing) {
			t = 0;
			speed = 0;
		}*/
		//Novice::ScreenPrintf(0, 0, "%f", t);
	return easedT;
}
