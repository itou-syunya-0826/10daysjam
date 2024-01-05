#pragma once
#include "myStructs.h"
#include <time.h>
#include <stdlib.h>
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "chkObjHit.h"

void ItemSpawn(Item item[5][32],float bossHP);
Vector2 setDirection(Vector2 setMove);
void initializeTmer();