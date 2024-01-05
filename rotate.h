#include "myStructs.h"
#include "Novice.h"
//#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

PositionAndAngle MovePlayer(char keys[], Vector2 pos, Vector2 vertex,float playerHP,bool isStart);
PositionAndAngle MoveBullet(char keys[], Vector2 pos, Vector2 vertex);
PositionAndAngle TransferAngle(PositionAndAngle squareTama);
