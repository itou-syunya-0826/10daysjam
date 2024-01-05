#include "DrawEnemy.h"
#include "Novice.h"

Enemy DrawEnemy(Enemy enemy,int drawEnemy) {
	for (int i = 0; i < 4; i++) {
		enemy.ani[0] += 1;
		if (enemy.ani[0] >= i * 15.0f && enemy.ani[0] <= (i * 15.0f) + 15) {
			Novice::DrawQuad(
				(int)enemy.newLeftEnemyTop.position.x,
				(int)enemy.newLeftEnemyTop.position.y,
				(int)enemy.newRightEnemyTop.position.x,
				(int)enemy.newRightEnemyTop.position.y,
				(int)enemy.newLeftEnemyBottom.position.x,
				(int)enemy.newLeftEnemyBottom.position.y,
				(int)enemy.newRightEnemyBottom.position.x,
				(int)enemy.newRightEnemyBottom.position.y, 0, 0, 184, 184, drawEnemy, WHITE
			);
		}
	}
	if (enemy.ani[0] == 60){
		enemy.ani[0] = 0;
	}
	
	return enemy;
}