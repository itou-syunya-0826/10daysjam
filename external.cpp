#include "external.h"
#include "myStructs.h"


bool External(Vector2 lineBegin, Vector2 lineEnd, Vector2 target,float targetWidth,float targetHeight) {
	float external = 0;
	Vector2 distance[2] = { 0,0 };
	distance[0].x = lineEnd.x - lineBegin.x;
	distance[0].y = lineEnd.y - lineBegin.y;

	distance[1].x = target.x+ targetWidth - lineBegin.x;
	distance[1].y = target.y+ targetHeight - lineBegin.y;

	external = distance[0].x * distance[1].y - distance[0].y * distance[1].x;
	return external > 0;
}