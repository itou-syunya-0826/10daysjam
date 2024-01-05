#include "updateCounter.h"

ItemCounter updateCounter(char keys[], char preKeys[], ItemCounter itemCounter) {
	if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
		if (itemCounter.heartNum >= 3 || itemCounter.maruNum >= 3 || itemCounter.squareNum>=3 || itemCounter.triangleNum>=3) {

			itemCounter.crossNum = 0;
			itemCounter.heartNum = 0;
			itemCounter.maruNum = 0;
			itemCounter.squareNum = 0;
			itemCounter.triangleNum = 0;
		}
	}
	return itemCounter;
}