#pragma once

const float kWindowWidth = 1920.0f;
const float kWindowHeight = 1080.0f;

const int screenWidth = 1920;
const int screenHeight = 1080;

const float gentenX = kWindowWidth / 2;
const float gentenY = kWindowHeight / 2;

const int ITEMTYPE = 5;
const int ITEMNUM = 32;

enum itemType {
	cross,			 //cross 0
	heart,			 //heart 1
	maru,			 //maru 2
	square,			 //square 3
	triangle		 //triangle 4
};

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

typedef struct GameObject {
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	bool isAlive = false;
}GameObject;

typedef struct PoitionAndAngle {
	Vector2 position;
	float angle;
	int type;
}PositionAndAngle;

typedef struct Size {
	float w;
	float h;
}Size;

typedef struct Player {
	PositionAndAngle newLeftTop;
	PositionAndAngle newLeftBottom;
	PositionAndAngle newRightTop;
	PositionAndAngle newRightBottom;
	PositionAndAngle move;
	Vector2 pos;
	Vector2 position;
	Vector2 vertex;
	Vector2 kLeftTop;
	Vector2 kLeftBottom;
	Vector2 kRightTop;
	Vector2 kRightBottom;
	Size size;
	float vel;
	float accel;
	bool isAlive;
	bool isHit;
	int ani;
	int img[4];
}Player;

typedef struct effect {
	PositionAndAngle newLeftTop;
	PositionAndAngle newLeftBottom;
	PositionAndAngle newRightTop;
	PositionAndAngle newRightBottom;
	Vector2 kLeftTop;
	Vector2 kLeftBottom;
	Vector2 kRightTop;
	Vector2 kRightBottom;
	Vector2 position;

}effect;

typedef struct Enemy {
	PositionAndAngle newLeftEnemyTop;
	PositionAndAngle newLeftEnemyBottom;
	PositionAndAngle newRightEnemyTop;
	PositionAndAngle newRightEnemyBottom;
	Vector2 pos;
	Vector2 position;
	Vector2 vertex;
	Vector2 kLeftEnemyTop;
	Vector2 kLeftEnemyBottom;
	Vector2 kRightEnemyTop;
	Vector2 kRightEnemyBottom;
	Size size;
	float vel;
	float accel;
	bool isAlive;
	float t[3];
	float ani[3];
	bool isHit;
	int color;
	int img[20];
	int texture[11];
	int bakuhatu[15];
}Enemy;

typedef struct Item {
	Vector2 pos;
	Size size;
	float angle;
	Vector2 move;
	float speed;
	bool isSpawn;
	int color;
	int img;
}Item;

typedef struct ItemCounter {
	int crossNum;				//cross
	int heartNum;				//heart
	int maruNum;				//round
	int squareNum;				//square
	int triangleNum;			//triangle
	int bossNum;				//bossCount
}ItemCounter;

typedef struct Bullet {
	PositionAndAngle newLeftTop[9];
	PositionAndAngle newLeftBottom[9];
	PositionAndAngle newRightTop[9];
	PositionAndAngle newRightBottom[9];
	PositionAndAngle squareTama;
	Vector2 position;
	Vector2 pos[9];
	Vector2 kLeftTop[9];
	Vector2 kLeftBottom[9];
	Vector2 kRightTop[9];
	Vector2 kRightBottom[9];
	Vector2 move;
	Vector2 distance[3];
	Vector2 target[2];
	Size size[12];
	int img[6][12];
	int bulletType;
	bool isShot[6];
	bool isHit[6];
	float speed;
	float angle;
	float angle1;
	int color;
	float length[3];
	float ani[6];
	float t[6];
}Bullet;

typedef struct Backround {
	Vector2 pos;
	Size size;
	int color;
	int img[5];
}Backround;

typedef struct HpBar {
	Vector2 leftTop;
	Vector2 leftBottom;
	Vector2 rightTop;
	Vector2 rightBottom;
}HpBar;

typedef struct SEHandler {
	int audio[20];
	int handler[20];
	int t[20];
	float count[20];
}SEHandler;
