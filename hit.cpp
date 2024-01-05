#include "hit.h"
bool Hit(float objctAX, float objctAY, float objctAW, float objectAH, float objectBX, float objectBY, float objectBW, float objectBH) {
	bool shotXleEnemyXW = objctAX <= objectBX + objectBW;
	bool enemyXleShotXW = objectBX <= objctAX + objctAW;
	bool shotYleEnemyYH = objctAY <= objectBY + objectBH;
	bool enemyYleShotYH = objectBY <= objctAY + objectAH;
	return shotXleEnemyXW && enemyXleShotXW && shotYleEnemyYH && enemyYleShotYH;
}