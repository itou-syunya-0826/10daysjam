#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <time.h>

#include "myStructs.h"
#include "MovePlayer.h"
#include "ItemSpawn.h"
#include "chkObjHit.h"
#include "chkItemCounter.h"
#include "external.h"
#include "rotate.h"
#include "enemyRotate.h"
#include "setBulletType.h"
#include "updateCounter.h"
#include "playerAtkMove.h"
#include "chkAtkHit.h"
#include "itemInitialize.h"
#include "playerInitialize.h"
#include "enemyInitialize.h"
#include "bulletInitialize.h"
#include "DrawPlayer.h"
#include "DrawEnemy.h"
#include "DrawBullet.h"
#include "DrawItem.h"
#include "backroundInitialize.h"
#include "DrawBackround.h"
#include "hit.h"
#include "ItemHitBullet.h"
#include "IsPlaySE.h"
#include "enemyBulletInit.h"
#include "EnemyAtkMove.h"
#include "chkEnemyAtkHit.h"
#include "chkItemBulletHit.h"
#include "setEnemyBullet.h"
#include "DrawEnemyBullet.h"
#include "SEInitialize.h"


const char kWindowTitle[] = "5061_WHITE_HOLE";

enum Scene {
	title,
	playerControl,
	game,
	badEnd,
	gameClear,
};
Scene scene = title;
Scene preScene = title;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1920, 1080);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int mouseDisplay = 0;
	//矩形Dの計算
	Backround backround{ 0 };
	backround = backroundInitialize(backround);

	Player player{ 0 };
	player = playerInitialize(player);

	Enemy enemy{ 0 };
	enemy = enemyInitialize(enemy);

	Bullet bullet{ 0 };
	Bullet enemyBullet = { 0 };
	bullet = bulletInitialize(bullet);
	enemyBullet = enemyBulletInit(enemyBullet);

	Item item[ITEMTYPE][ITEMNUM] = { 0 };
	ItemCounter itemCounter = { 0 };
	itemInitialize(item);

	SEHandler soundEffect = { 0 };
	soundEffect = SEInitialize(soundEffect);

	srand((unsigned int)time(nullptr));

	bool itemHit = false;

#pragma region effect
	int playerEffect[6]{
		Novice::LoadTexture("./resources/player/playerEffect1.png"),
		Novice::LoadTexture("./resources/player/playerEffect2.png"),
		Novice::LoadTexture("./resources/player/playerEffect3.png"),
		Novice::LoadTexture("./resources/player/playerEffect4.png"),
		Novice::LoadTexture("./resources/player/playerEffect5.png"),
		Novice::LoadTexture("./resources/player/playerEffect6.png"),
	};
	int drawPlayerEffect = playerEffect[0];
	float effectAnimeTime = 0;

	int playerLeftEffectTexture[4]{
		Novice::LoadTexture("./resources/player/LeftEff1.png"),
		Novice::LoadTexture("./resources/player/LeftEff2.png"),
		Novice::LoadTexture("./resources/player/LeftEff3.png"),
		Novice::LoadTexture("./resources/player/LeftEff4.png"),
	};
	int drawLeftEff = playerLeftEffectTexture[0];

	int playerRightEffectTexture[4]{
		Novice::LoadTexture("./resources/player/effRight1.png"),
		Novice::LoadTexture("./resources/player/effRight2.png"),
		Novice::LoadTexture("./resources/player/effRight3.png"),
		Novice::LoadTexture("./resources/player/effRight4.png"),
	};
	int drawRightEff = playerRightEffectTexture[0];

	int enemyMoveEff[8]{
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveLeftt1.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveLeftt2.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveLeftt3.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveLeftt4.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveRight1.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveRight2.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveRight3.png"),
		Novice::LoadTexture("./resources/enemy/PJWH_Enemy_MoveRight4.png"),
	};
	int drawEnemyMoveRight = enemyMoveEff[0];
	int drawEnemyMoveLeft = enemyMoveEff[4];

	effect playerEffectPos{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ screenWidth / 6.7f,0 },
	};

	effect playerLeftEffect{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ screenWidth / 5.5f,-48 },
	};

	effect playerRightEffect{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ screenWidth / 5.5f,110 },
	};

	effect enemyBakuhatu{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ 500,0 },
	};

	effect enemyLeft{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ 535,10 },
	};

	effect enemyRight{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ 540,85 },
	};

	effect playerBakuhatu{
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{0,0},
		{ screenWidth / 6.0f,0 },
	};

	int drawBakuhatu[2] = { enemy.bakuhatu[0],enemy.bakuhatu[0] };
	float bakuhatuCount[2] = { 0,0 };
	bool isEnemyBakuhatu = false;
	bool isPlayerBakuhatu = false;

	float playerEffectLeftCount = 0;
	float playerEffectRightCount = 0;
	float enemyEffectLeftCount = 0;
	float enemyEffectRightCount = 0;
#pragma endregion


	int drawEnemy = enemy.texture[0];

	bool isItemRiset = false;

	bool isFullScreen = true;

	bool isSamonBoss = false;

	float hitTime = 0;


#pragma region startBoss
	Vector2 startBoss{ 0,0 };
	Vector2 startBossBegin{ gentenX - 60,-1000 };
	Vector2 startBossEnd{ gentenX - 60,100 };
	float startBossTime = 0;
#pragma endregion

#pragma region itemGe-zi
	Vector2 itemUI[5] = { {1800,900},{1750,900},{1700,900},{1650,900},{1600,900} };
	bool isItemUI[4] = { false };
	bool isItemErazeUI[4] = { false };
	float itemErazeTime[4] = { 0 };
	int maruAnime[3] = {
		Novice::LoadTexture("./resources/ItemAnime/maruAnime1.png"),
		Novice::LoadTexture("./resources/ItemAnime/maruAnime2.png"),
		Novice::LoadTexture("./resources/ItemAnime/maruAnime3.png"),
	};
	int sankakuAnime[2]{
		Novice::LoadTexture("./resources/ItemAnime/triangle1.png"),
		Novice::LoadTexture("./resources/ItemAnime/triangle2.png"),
	};
	int sikakuAnime[2]{
		Novice::LoadTexture("./resources/ItemAnime/sikaku1.png"),
		Novice::LoadTexture("./resources/ItemAnime/sikaku2.png"),
	};

	int drawEraze[4] = { maruAnime[0] ,sankakuAnime[0], maruAnime[0],sikakuAnime[0] };

	bool isMaru[5] = { false };
	bool isSankaku[5] = { false };
	bool isHeart[5] = { false };
	bool isSikaku[5] = { false };
#pragma endregion

#pragma region HP
	Vector2 hpPos[2] = { { 1500,950 },{ 50,98 } };
	HpBar playerHP = { { 1500,950 },{ 1500,1014 },{1500,950},{1500,1014} };
	HpBar enemyHP = { { 50,98 },{ 50,162 },{50,98},{ 50,162 } };
	int hpBar = Novice::LoadTexture("./resources/backround/HPBar.png");
	float hpPosW[2] = { 384, 384 };
#pragma endregion

	bool isHeal = false;
	bool isHighHeal = false;

	int holdMaru = 0;
	int holdSankaku = 0;
	int holdSikaku = 0;
	bool isCross = false;

	bool isESC = false;
	bool isPush = false;

#pragma region BGM

	int BGM[4]{
		Novice::LoadAudio("./resources/sound/BGM/title.mp3"),
		Novice::LoadAudio("./resources/sound/BGM/sentou.mp3"),
		Novice::LoadAudio("./resources/sound/BGM/badEnd.mp3"),
		Novice::LoadAudio("./resources/sound/BGM/clear.mp3"),
	};
	int soundHandle[4] = { 0 };

#pragma endregion

#pragma region SE

	int SE[10] = {
		Novice::LoadAudio("./resources/sound/SE/click.wav"),
		Novice::LoadAudio("./resources/sound/SE/clickOutside.wav"),
		Novice::LoadAudio("./resources/sound/SE/select.wav"),
	};
	int SEHandle[10] = { 0 };
	float SECount[10] = { 0 };
	bool isSelect[3] = { false };
#pragma endregion

#pragma region End 
	int black = Novice::LoadTexture("./resources/backround/black.png");
	int badMoji = Novice::LoadTexture("./resources/backround/gameOver.png");
	int clearMoji = Novice::LoadTexture("./resources/backround/clear.png");
	int clearBg = Novice::LoadTexture("./resources/backround/clearBg.png");
	int badTitlePush[6] = {
		Novice::LoadTexture("./resources/backround/titlePush1.png"),
		Novice::LoadTexture("./resources/backround/titlePush2.png"),
		Novice::LoadTexture("./resources/backround/titlePush3.png"),
		Novice::LoadTexture("./resources/backround/badTitlePush1.png"),
		Novice::LoadTexture("./resources/backround/badTitlePush2.png"),
		Novice::LoadTexture("./resources/backround/badTitlePush3.png"),
	};
	int closePush[6]{
		Novice::LoadTexture("./resources/backround/closePush1.png"),
		Novice::LoadTexture("./resources/backround/closePush2.png"),
		Novice::LoadTexture("./resources/backround/closePush3.png"),
		Novice::LoadTexture("./resources/backround/badClosePush1.png"),
		Novice::LoadTexture("./resources/backround/badClosePush2.png"),
		Novice::LoadTexture("./resources/backround/badClosePush3.png"),
	};
	Vector2 badTitle = { 0,0 };
	Vector2 badTitleBegin = { 100,-1000 };
	Vector2 badTitleEnd = { 100,kWindowHeight / 4 };

	Vector2 badClick[2] = {
		{0,0},
		{0,0}
	};
	Vector2 badClickBegin[2] = {
		{2000,kWindowHeight / 2 + 100},
		{2000,kWindowHeight / 2 + 300},
	};
	int drawClearClick = badTitlePush[0];
	int drawClearExit = closePush[0];

	int drawBadClick = badTitlePush[0];
	int drawBadExit = closePush[0];
	Vector2 badClickEnd[2] = {
		{1200,kWindowHeight / 2 + 100},
		{1200,kWindowHeight / 2 + 300},
	};

	bool isBackTitle = false;
	bool isClose = false;
	bool isExit = false;

#pragma endregion

#pragma region STERT
	int titleMoji = Novice::LoadTexture("././resources/backround/gameName.png");
	int startBg = Novice::LoadTexture("././resources/backround/titleBg.png");
	Vector2 titleMojiResult = { 0,0 };
	Vector2 titleMojiBegin = { 100,-1000 };
	Vector2 titleMojiEnd = { 100,kWindowHeight / 8 };
	float easingTime[8] = { 0 };
	bool isTitlePosition = false;

	int titlePush[3] = {
		Novice::LoadTexture("././resources/backround/Title_Button1.png"),
		Novice::LoadTexture("././resources/backround/Title_Button2.png"),
		Novice::LoadTexture("././resources/backround/Title_Button3.png"),
	};
	int drawPush = titlePush[0];
	Vector2 titlePushResult = { 0,0 };
	Vector2 titlePushBegin = { kWindowWidth / 2 - 384 / 2,2000 };
	Vector2 titlePushEnd = { kWindowWidth / 2 - 384 / 2,kWindowHeight / 2 + 220 };

	int mouseX = 0;
	int mouseY = 0;

	bool isBack[2] = { false };
	bool isGame = false;
	bool isControl = false;

	int backTexture[3]{
		Novice::LoadTexture("././resources/backround/Back1.png"),
		Novice::LoadTexture("././resources/backround/Back2.png"),
		Novice::LoadTexture("././resources/backround/Back3.png"),
	};
	int drawBack = backTexture[0];

	Vector2 backPos = { kWindowWidth / 2 - 232 / 2 ,892 };
#pragma endregion

#pragma region  sousa
	int sousa = Novice::LoadTexture("./resources/backround/control.png");
	int ruru= Novice::LoadTexture("./resources/backround/control1.png");
	int controlPush[3] = {
		Novice::LoadTexture("./resources/backround/Control_Button1.png"),
		Novice::LoadTexture("./resources/backround/Control_Button2.png"),
		Novice::LoadTexture("./resources/backround/Control_Button3.png"),
	};
	int control = controlPush[0];

	Vector2 controlPushResult = { 0,0 };
	Vector2 controlPushBegin = { kWindowWidth / 2 - 396 / 2,2000 };
	Vector2 controlPushEnd = { kWindowWidth / 2 - 396 / 2,kWindowHeight / 2 + 380 };

	Vector2 controlPase[2] = { {0,0},{1980,0} };
	Vector2 controlPaseBegin[2] = { {0,0}, {1980,0} };
	Vector2 controlPaseEnd[2] = { { -1980,0 }, {0,0} };
	bool isNextPase = false;
	bool isPreviousPase = false;

	int ruruPush[4] = {
		Novice::LoadTexture("./resources/backround/right1.png"),
		Novice::LoadTexture("./resources/backround/right2.png"),
		Novice::LoadTexture("./resources/backround/left1.png"),
		Novice::LoadTexture("./resources/backround/left2.png"),
	};
	Vector2 controlLeft = { 1800,kWindowHeight / 2.0f };
	Vector2 controlLeftBegin = { 1800,kWindowHeight / 2.0f };
	Vector2 controlLeftend = { -180,kWindowHeight / 2.0f };
	int drawConLeft = ruruPush[0];

	Vector2 controlRight = { 2012,kWindowHeight / 2.0f };
	Vector2 controlRightBegin = { 2012,kWindowHeight / 2.0f };
	Vector2 controlRightend = { 92,kWindowHeight / 2.0f };
	int drawConRight = ruruPush[2];

	Vector2 ESCPos = { 0,0 };
	Vector2 ESCPosBegin = { 0,0 };
	Vector2 ESCPosEnd = { -1980,0 };

	Vector2 siyou = { 1980,0 };
	Vector2 siyouBegin = { 1980,0 };
	Vector2 siyouEnd = { 0,0 };
	int siyouTexture= Novice::LoadTexture("./resources/backround/control2.png");
	int kuroiBg= Novice::LoadTexture("./resources/backround/1.png");
#pragma endregion

#pragma region bgAnime
	int bgAnime[] = {
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title1.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title2.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title3.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title4.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title5.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title6.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title7.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title8.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title9.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title10.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title11.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title12.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title13.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title14.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title15.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title16.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title17.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title18.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title19.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title20.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title21.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title22.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title23.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title24.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title25.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title26.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title27.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title28.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title29.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title30.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title31.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title32.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title33.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title34.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title35.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title36.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title37.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title38.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title39.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title40.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title41.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title42.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title43.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title44.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title45.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title46.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title47.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title48.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title49.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title50.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title51.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title52.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title53.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title54.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title55.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title56.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title57.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title58.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title59.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title60.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title61.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title62.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title63.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title64.png"),
	Novice::LoadTexture("./resources/bgAnime/PJWH_Title65.png"),
	};
	
	int anime = 0;
	float bgTime = 600;
#pragma endregion

	//float angle[2] = { 0 };
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		//Novice::SetMouseCursorVisibility(mouseDisplay);

		///
		/// ↓ゲームの処理ここから
		///
		Novice::GetMousePosition(&mouseX, &mouseY);
#pragma region FULLScreen
		if ((keys[DIK_LMENU] && preKeys[DIK_LMENU] && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) && !isFullScreen) {
			isFullScreen = true;
		}
		else if ((keys[DIK_LMENU] && preKeys[DIK_LMENU] && keys[DIK_RETURN] && !preKeys[DIK_RETURN]) && isFullScreen) {
			isFullScreen = false;
		}
		if (isFullScreen) {
			Novice::SetWindowMode(kFullscreen);
		}
		else {
			Novice::SetWindowMode(kWindowed);
		}
#pragma endregion

#pragma region initialostion
		if (preScene != scene) {
			switch (scene) {

			case title:
				Novice::StopAudio(soundHandle[2]);
				Novice::StopAudio(soundHandle[3]);
				easingTime[0] = 0;
				easingTime[1] = 0;
				isTitlePosition = false;
				isBack[0] = false;
				isGame = false;
				isControl = false;
				anime = 0;
				bgTime = 600;
				break;
			case playerControl:
				controlPase[0] = {0,0};
				controlPase[1] = { 1980,0 };
				controlLeft = { 1800,kWindowHeight / 2.0f };
				controlRight = { 2012,kWindowHeight / 2.0f };
				isPreviousPase = false;
				isNextPase = false;
				easingTime[6] = 0;
				break;
			case game:
				Novice::StopAudio(soundHandle[0]);
				isSamonBoss = false;
				isItemRiset = true;
				hpPosW[0] = 384;
				hpPosW[1] = 384;
				easingTime[2] = 0;
				startBoss = { startBossBegin.x,startBossBegin.y };
				player = playerInitialize(player);
				itemInitialize(item);
				itemCounter.heartNum = 0;
				itemCounter.crossNum = 0;
				itemCounter.maruNum = 0;
				itemCounter.squareNum = 0;
				itemCounter.triangleNum = 0;
				itemCounter.bossNum = 0;
				isItemRiset = true;
				initializeTmer();
				for (int i = 0; i < ITEMTYPE; i++) {
					for (int j = 0; j < ITEMNUM; j++) {
						item[i][j].isSpawn=false;
					}
				}
				player.isHit = false;
				enemy.isHit = false;
				bullet.position = { 0,0 };
				for (int i = 0; i < 8; i++) {
					bullet.newLeftTop[i].position = {0,0};
					bullet.newLeftBottom[i].position = {0,0};
					bullet.newRightTop[i].position = { 0,0 };
					bullet.newRightBottom[i].position = { 0,0 };
				}
				bullet.isShot[square] = false;
				bullet.isShot[maru] = false;
				bullet.isShot[triangle] = false;
				enemyBullet.isShot[0] = false;
				enemyBullet.isShot[1] = false;
				isCross = false;
				break;

			case badEnd:
				Novice::StopAudio(soundHandle[1]);
				isBack[1] = false;
				isBackTitle = false;
				isClose = false;
				isExit = false;
				easingTime[3] = 0;
				easingTime[4] = 0;
				break;

			case gameClear:
				Novice::StopAudio(soundHandle[1]);
				isBack[1] = false;
				isBackTitle = false;
				isClose = false;
				isExit = false;
				easingTime[3] = 0;
				easingTime[4] = 0;
				break;

			}
		}
		preScene = scene;
#pragma endregion

		switch (scene) {
			

#pragma region STERT
		case title:
			///
			///更新処理:ここから
			/// 
			/*if (keys[DIK_1]) {
				scene = playerControl;
			}
			if (keys[DIK_2]) {
				scene = game;
			}
			if (keys[DIK_3]) {
				scene = badEnd;
			}
			if (keys[DIK_4]) {
				scene = gameClear;
			}*/
			mouseDisplay = 1;
			if (Novice::IsPlayingAudio(soundHandle[0]) == 0 ) {
				soundHandle[0] = Novice::PlayAudio(BGM[0], true, 0.5f);
			}

			/*if (keys[DIK_C]) {
				scene = gameClear;
			}
			if (keys[DIK_B]) {
				scene = badEnd;
			}*/
			easingTime[0]+=1.0f/60.0f;
			if (titleMojiResult.y >= 50) {
				isTitlePosition = true;
			}

			if (isTitlePosition) {
				easingTime[1] += 1.0f / 60.0f;
			}
			if (!isBack[0]) {
				titleMojiResult = EasingPosition(titleMojiBegin, titleMojiEnd, 2, easingTime[0]);
				titlePushResult = EasingPosition(titlePushBegin, titlePushEnd, 2, easingTime[1]);
				controlPushResult = EasingPosition(controlPushBegin, controlPushEnd, 2, easingTime[1]);
			}
			if (easingTime[1]>=1) {
				if (Hit(titlePushResult.x, titlePushResult.y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)){
					drawPush= titlePush[1];
					if (!isSelect[0]) {
						if (SECount[2] <= 0) {
							SECount[2] = 5;
						}
						isSelect[0] = true;
					}
					if (SECount[2] > 0) {
						SECount[2]--;
					}
					
					if (Novice::IsTriggerMouse(0)) {
						drawPush = titlePush[2];
						easingTime[0] = 0;
						easingTime[1] = 0;
						isBack[0] = true;
						isGame = true;
						
							
						SECount[0] = 5;
						if (SECount[0] > 0) {
							SECount[0]--;
						}
						IsPlaySE(SE[0], SEHandle[0], SECount[0], 5);
					}
				}
				else {
					drawPush = titlePush[0];
					SECount[2] = 0;
					isSelect[0] = false;
				}
				if (Hit(controlPushResult.x, controlPushResult.y, 396, 128, (float)mouseX, (float)mouseY, 0, 0)) {
					 control = controlPush[1];
					 if (!isSelect[0]) {
					 	if (SECount[2] <= 0) {
					 		SECount[2] = 5;
					 	}
					 	isSelect[0] = true;
					 }
					 if (SECount[2] > 0) {
					 	SECount[2]--;
					 }
					 
					 if (Novice::IsTriggerMouse(0)) {
						 control = controlPush[2];
					 	easingTime[0] = 0;
					 	easingTime[1] = 0;
					 	isBack[0] = true;
						isControl = true;
					 
					 
					 	SECount[0] = 5;
					 	if (SECount[0] > 0) {
					 		SECount[0]--;
					 	}
					 	IsPlaySE(SE[0], SEHandle[0], SECount[0], 5);
					 }
				}
				else {
					control = controlPush[0];
					SECount[2] = 0;
					isSelect[0] = false;
				}
			}
			
			if (isBack[0]) {
				titleMojiResult = EasingPosition(titleMojiEnd, titleMojiBegin, 1, easingTime[0]);
				titlePushResult = EasingPosition(titlePushEnd, titlePushBegin, 1, easingTime[1]);
				controlPushResult = EasingPosition( controlPushEnd, controlPushBegin, 1, easingTime[1]);
			}
			
			if (easingTime[1] >= 1 && isBack[0]&&isGame) {
				scene = game;
			}
			if (easingTime[1] >= 1 && isBack[0] && isControl) {
				scene = playerControl;
			}
			if (!Hit(titlePushResult.x, titlePushResult.y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)) {
				//SECount[2] = 0;
				if (Novice::IsTriggerMouse(0)) {
					/*isSE[0] = true;*/
					SECount[1] = 5;
				}
				if (SECount[1] > 0) {
					SECount[1]--;
				}
			}
			IsPlaySE(SE[1], SEHandle[1], SECount[1], 5);

			//IsPlaySE(SE[2], SEHandle[2], SECount[2], 5);
			//Novice::ScreenPrintf(0, 0, "%f", SECount[2]);
			/*if (isSE[0] && SECount[0] == 0) {
				SECount[0] = 5;
			}
			if (SECount[0] > 0) {
				SECount[0]--;
			}
			if (SECount[0] <= 5) {
				if (Novice::IsPlayingAudio(SEHandle[0]) == 0) {
					SEHandle[0] = Novice::PlayAudio(SE[0], false, 1.0f / 4.0f);
				}
			}
			if (SECount[0] <= 0) {
				Novice::StopAudio(SEHandle[0]);
				isSE[0] = false;
			}*/

#pragma region bgAnime
			if (bgTime > 0) {
				bgTime--;
			}
			if (bgTime <= 0) {
				anime++;
			}
			if (anime >= 65) {
				anime = 0;
				bgTime = 600;
			}
#pragma endregion	
			
			///
			///更新処理:ここまで
			///
			
			///
			///描画処理:ここから
			/// 
			Novice::DrawSprite(0, 0, startBg, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(0, 0, kuroiBg, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite(0, 0, bgAnime[anime], 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)titleMojiResult.x, (int)titleMojiResult.y, titleMoji, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)titlePushResult.x, (int)titlePushResult.y, drawPush, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)controlPushResult.x, (int)controlPushResult.y, control, 1, 1, 0.0f, WHITE);
			///
			///描画処理:ここまで
			///
			break;

#pragma endregion


#pragma region control
			case playerControl:
				if (Hit(backPos.x, backPos.y, 232,176,(float)mouseX, (float)mouseY, 0, 0)){
					drawBack = backTexture[1];
					if (Novice::IsTriggerMouse(0)) {
						scene = title;
					}
				}
				else {
					drawBack= backTexture[0];
				}

				if (Hit(controlLeft.x, controlLeft.y, 88, 88, (float)mouseX, (float)mouseY, 0, 0)) {
					drawConLeft = ruruPush[1];
					if (Novice::IsTriggerMouse(0)) {
						easingTime[6] = 0;
						isPreviousPase = false;
						isNextPase = true;
					}
				}
				else {
					drawConLeft = ruruPush[0];
				}

				if (Hit(controlRight.x, controlRight.y, 88, 88, (float)mouseX, (float)mouseY, 0, 0)) {
					drawConRight = ruruPush[3];
					if (Novice::IsTriggerMouse(0)) {
						easingTime[6] = 0;
						isNextPase = false;
						isPreviousPase = true;
					}
				}
				else {
					drawConRight = ruruPush[2];
				}

				easingTime[6] += 1.0f / 30.0f;
				/*if (keys[DIK_A]&&!preKeys[DIK_A]) {
					
				}*/
				/*if (keys[DIK_D] && !preKeys[DIK_D]) {
					
				}*/
				
				
				if (isNextPase) {
					controlPase[0] = EasingPosition(controlPaseBegin[0], controlPaseEnd[0], 2, easingTime[6]);
					controlPase[1] = EasingPosition(controlPaseBegin[1], controlPaseEnd[1], 2, easingTime[6]);
					controlLeft = EasingPosition(controlLeftBegin, controlLeftend, 2, easingTime[6]);
					controlRight = EasingPosition(controlRightBegin, controlRightend, 2, easingTime[6]);
				}

				if (isPreviousPase) {
					controlPase[0] = EasingPosition( controlPaseEnd[0], controlPaseBegin[0], 2, easingTime[6]);
					controlPase[1] = EasingPosition( controlPaseEnd[1], controlPaseBegin[1], 2, easingTime[6]);
					controlLeft = EasingPosition( controlLeftend, controlLeftBegin, 2, easingTime[6]);
					controlRight = EasingPosition( controlRightend, controlRightBegin, 2, easingTime[6]);
				}
				Novice::DrawSprite(0, 0, startBg, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)controlPase[0].x, (int)controlPase[0].y, sousa, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)controlPase[1].x, (int)controlPase[1].y, ruru, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)controlLeft.x, (int)controlLeft.y, drawConLeft, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)controlRight.x, (int)controlRight.y, drawConRight, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)backPos.x, (int)backPos.y+50, drawBack, 1, 1, 0.0f, WHITE);
				
				break;
#pragma endregion


#pragma region GAME
		case game:
			///
			///更新処理:ここから
			/// 
			mouseDisplay = 0;
#pragma region test
			
			/*if (keys[DIK_R] && !preKeys[DIK_R]) {
				scene = badEnd;
			}

			if (keys[DIK_1] && !preKeys[DIK_1]) {
				itemCounter.maruNum += 1;
			}
			if (keys[DIK_2] && !preKeys[DIK_2]) {
				itemCounter.triangleNum += 1;
			}
			if (keys[DIK_3] && !preKeys[DIK_3]) {
				itemCounter.heartNum += 1;
			}
			if (keys[DIK_4] && !preKeys[DIK_4]) {
				itemCounter.squareNum += 1;
			}
			if (keys[DIK_0] && !preKeys[DIK_0]) {
				itemCounter.maruNum = 0;
			}*/
			/*if (keys[DIK_K]) {
				itemCounter.bossNum = 10;
			}*/
			/*if (keys[DIK_5]) {
				hpPosW[1] = 100;
			}
			if (keys[DIK_6]) {
				hpPosW[1] = 190;
			}*/
		/*	if (keys[DIK_7]) {
				hpPosW[1] = 300;
			}*/
			//if (keys[DIK_P]) {
			//	isPlayerBakuhatu = true;
			//	//isSamonBoss = true;
			//}
			//if (keys[DIK_O]) {
			//	isPlayerBakuhatu = false;
			//	//isSamonBoss = true;
			//}
			//Novice::ScreenPrintf(10, 30, "heartNum: %d", heldItems.heartNum);
			/*Novice::ScreenPrintf(10, 50, "crossNum: %d", heldItems.crossNum);
			Novice::ScreenPrintf(10, 70, "maruNum: %d", heldItems.maruNum);
			Novice::ScreenPrintf(10, 90, "squareNum: %d", heldItems.squareNum);
			Novice::ScreenPrintf(10, 110, "triangleNum: %d", heldItems.triangleNum);
			Novice::ScreenPrintf(10, 130, "bossNum: %d", heldItems.bossNum);*/

			//Novice::ScreenPrintf(10, 150, "heartNum: %d", itemCounter.heartNum);
			//Novice::ScreenPrintf(10, 170, "crossNum: %d", itemCounter.crossNum);
			/*Novice::ScreenPrintf(10, 190, "maruNum: %d", itemCounter.maruNum);
			Novice::ScreenPrintf(10, 210, "squareNum: %d", itemCounter.squareNum);
		    Novice::ScreenPrintf(10, 230, "triangleNum: %d", itemCounter.triangleNum);*/
			//Novice::ScreenPrintf(10, 250, "bossNum: %d", itemCounter.bossNum);
#pragma endregion
			if (!keys[DIK_ESCAPE] && !preKeys[DIK_ESCAPE]) {
				isPush = true;
	        }
			if (keys[DIK_ESCAPE] && !preKeys[DIK_ESCAPE]&&isPush) {
				isESC = false;
			}
			if (isESC) {
				if (Hit(controlLeft.x, controlLeft.y, 88, 88, (float)mouseX, (float)mouseY, 0, 0)) {
					drawConLeft = ruruPush[1];
					if (Novice::IsTriggerMouse(0)) {
						easingTime[6] = 0;
						isPreviousPase = false;
						isNextPase = true;
					}
				}
				else {
					drawConLeft = ruruPush[0];
				}

				if (Hit(controlRight.x, controlRight.y, 88, 88, (float)mouseX, (float)mouseY, 0, 0)) {
					drawConRight = ruruPush[3];
					if (Novice::IsTriggerMouse(0)) {
						easingTime[6] = 0;
						isNextPase = false;
						isPreviousPase = true;
					}
				}
				else {
					drawConRight = ruruPush[2];
				}

				easingTime[6] += 1.0f / 30.0f;
				

				if (isNextPase) {
					controlLeft = EasingPosition(controlLeftBegin, controlLeftend, 2, easingTime[6]);
					controlRight = EasingPosition(controlRightBegin, controlRightend, 2, easingTime[6]);
					ESCPos = EasingPosition(ESCPosBegin, ESCPosEnd, 2, easingTime[6]);
					siyou = EasingPosition(siyouBegin, siyouEnd, 2, easingTime[6]);
				}

				if (isPreviousPase) {
					controlLeft = EasingPosition(controlLeftend, controlLeftBegin, 2, easingTime[6]);
					controlRight = EasingPosition(controlRightend, controlRightBegin, 2, easingTime[6]);
					ESCPos = EasingPosition(ESCPosEnd, ESCPosBegin,  2, easingTime[6]);
					siyou = EasingPosition(siyouEnd, siyouBegin, 2, easingTime[6]);
				}
		}
			if (!isESC) {
				ESCPos = { 0,0 };
				siyou = { 1980,0 };
				controlLeft = { 1800,kWindowHeight / 2.0f };
				controlRight = { 2012,kWindowHeight / 2.0f };
				isPreviousPase = false;
				isNextPase = false;
				easingTime[6] = 0;
				if (!keys[DIK_ESCAPE] && !preKeys[DIK_ESCAPE]) {
					isPush = false;
				}
				if (keys[DIK_ESCAPE] && !preKeys[DIK_ESCAPE]&&!isPush) {
					isESC = true;
				}
				if (itemCounter.heartNum >= 3) {
					isHeal = true;
					if (itemCounter.heartNum >= 5) {
						isHighHeal = true;
					}
				}

				if (itemCounter.heartNum == 0) {
					isHeal = false;
					isHighHeal = false;
				}
				if (isHeal) {
					if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
						IsPlaySE(soundEffect.audio[8], soundEffect.handler[8], soundEffect.count[8], 5);
						hpPosW[0] += 50;
					}
				}
				if (isHighHeal) {
					if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
						hpPosW[0] += 80;
					}
				}
				if (Novice::IsPlayingAudio(soundHandle[1]) == 0 && isSamonBoss) {
					soundHandle[1] = Novice::PlayAudio(BGM[1], true, 0.2f);
				}

				/*if (bullet.isHit[maru] == true) {
					enemy.isHit = true;
				}*/

				//isHitItem = HitItem(item, greenBullet[0].position);

#pragma region player

		//プレイヤーの回転
				player.newLeftTop = MovePlayer(keys, player.pos, player.kLeftTop, hpPosW[0], isSamonBoss);
				player.newLeftBottom = MovePlayer(keys, player.pos, player.kLeftBottom, hpPosW[0], isSamonBoss);
				player.newRightTop = MovePlayer(keys, player.pos, player.kRightTop, hpPosW[0], isSamonBoss);
				player.newRightBottom = MovePlayer(keys, player.pos, player.kRightBottom, hpPosW[0], isSamonBoss);

				//プレイヤーの後ろのエフェクト
				playerEffectPos.kLeftTop = player.kLeftTop;
				playerEffectPos.kLeftBottom = player.kLeftBottom;
				playerEffectPos.kRightTop = player.kRightTop;
				playerEffectPos.kRightBottom = player.kRightBottom;

				playerEffectPos.newLeftTop = MovePlayer(keys, playerEffectPos.position, playerEffectPos.kLeftTop, hpPosW[0], isSamonBoss);
				playerEffectPos.newLeftBottom = MovePlayer(keys, playerEffectPos.position, playerEffectPos.kLeftBottom, hpPosW[0], isSamonBoss);
				playerEffectPos.newRightTop = MovePlayer(keys, playerEffectPos.position, playerEffectPos.kRightTop, hpPosW[0], isSamonBoss);
				playerEffectPos.newRightBottom = MovePlayer(keys, playerEffectPos.position, playerEffectPos.kRightBottom, hpPosW[0], isSamonBoss);

				//プレイヤー左
				playerLeftEffect.kLeftTop = player.kLeftTop;
				playerLeftEffect.kLeftBottom = player.kLeftBottom;
				playerLeftEffect.kRightTop = player.kRightTop;
				playerLeftEffect.kRightBottom = player.kRightBottom;

				playerLeftEffect.newLeftTop = MovePlayer(keys, playerLeftEffect.position, playerLeftEffect.kLeftTop, hpPosW[0], isSamonBoss);
				playerLeftEffect.newLeftBottom = MovePlayer(keys, playerLeftEffect.position, playerLeftEffect.kLeftBottom, hpPosW[0], isSamonBoss);
				playerLeftEffect.newRightTop = MovePlayer(keys, playerLeftEffect.position, playerLeftEffect.kRightTop, hpPosW[0], isSamonBoss);
				playerLeftEffect.newRightBottom = MovePlayer(keys, playerLeftEffect.position, playerLeftEffect.kRightBottom, hpPosW[0], isSamonBoss);

				if (playerEffectLeftCount > 0) {
					playerEffectLeftCount--;
				}
				else {
					playerEffectLeftCount = 40;
				}

				if (playerEffectLeftCount <= 40) {
					drawLeftEff = playerLeftEffectTexture[0];
				}
				if (playerEffectLeftCount <= 30) {
					drawLeftEff = playerLeftEffectTexture[1];
				}
				if (playerEffectLeftCount <= 20) {
					drawLeftEff = playerLeftEffectTexture[2];
				}
				if (playerEffectLeftCount <= 10) {
					drawLeftEff = playerLeftEffectTexture[3];
				}

				//プレイヤー右
				playerRightEffect.kLeftTop = player.kLeftTop;
				playerRightEffect.kLeftBottom = player.kLeftBottom;
				playerRightEffect.kRightTop = player.kRightTop;
				playerRightEffect.kRightBottom = player.kRightBottom;

				playerRightEffect.newLeftTop = MovePlayer(keys, playerRightEffect.position, playerRightEffect.kLeftTop, hpPosW[0], isSamonBoss);
				playerRightEffect.newLeftBottom = MovePlayer(keys, playerRightEffect.position, playerRightEffect.kLeftBottom, hpPosW[0], isSamonBoss);
				playerRightEffect.newRightTop = MovePlayer(keys, playerRightEffect.position, playerRightEffect.kRightTop, hpPosW[0], isSamonBoss);
				playerRightEffect.newRightBottom = MovePlayer(keys, playerRightEffect.position, playerRightEffect.kRightBottom, hpPosW[0], isSamonBoss);

				if (playerEffectRightCount > 0) {
					playerEffectRightCount--;
				}
				else {
					playerEffectRightCount = 40;
				}

				if (playerEffectRightCount <= 40) {
					drawRightEff = playerRightEffectTexture[0];
				}
				if (playerEffectRightCount <= 30) {
					drawRightEff = playerRightEffectTexture[1];
				}
				if (playerEffectRightCount <= 20) {
					drawRightEff = playerRightEffectTexture[2];
				}
				if (playerEffectRightCount <= 10) {
					drawRightEff = playerRightEffectTexture[3];
				}
				//プレイヤー爆破エフェクト
				playerBakuhatu.kLeftTop = player.kLeftTop;
				playerBakuhatu.kLeftBottom = player.kLeftBottom;
				playerBakuhatu.kRightTop = player.kRightTop;
				playerBakuhatu.kRightBottom = player.kRightBottom;

				playerBakuhatu.newLeftTop = MovePlayer(keys, playerBakuhatu.position, playerBakuhatu.kLeftTop, hpPosW[0], isSamonBoss);
				playerBakuhatu.newLeftBottom = MovePlayer(keys, playerBakuhatu.position, playerBakuhatu.kLeftBottom, hpPosW[0], isSamonBoss);
				playerBakuhatu.newRightTop = MovePlayer(keys, playerBakuhatu.position, playerBakuhatu.kRightTop, hpPosW[0], isSamonBoss);
				playerBakuhatu.newRightBottom = MovePlayer(keys, playerBakuhatu.position, playerBakuhatu.kRightBottom, hpPosW[0], isSamonBoss);
#pragma endregion

#pragma region enemy
				//エネミー登場
				if (!isSamonBoss) {
					easingTime[2] += 1.0f / 60.0f;
				}
				startBoss = EasingPosition(startBossBegin, startBossEnd, 2, easingTime[2]);
				if (easingTime[2] >= 1) {
					if (startBossTime > 0) {
						startBossTime--;
					}
					else {
						startBossTime = 60;
					}
					if (startBossTime <= 0) {
						isSamonBoss = true;
					}

				}

				//Novice::ScreenPrintf(0, 0, "%f", startBossTime);

				if (isSamonBoss) {
					//エネミー回転
					enemy.newLeftEnemyTop = MoveEnemy(enemy.pos, enemy.kLeftEnemyTop, hpPosW[1]);
					enemy.newLeftEnemyBottom = MoveEnemy(enemy.pos, enemy.kLeftEnemyBottom, hpPosW[1]);
					enemy.newRightEnemyTop = MoveEnemy(enemy.pos, enemy.kRightEnemyTop, hpPosW[1]);
					enemy.newRightEnemyBottom = MoveEnemy(enemy.pos, enemy.kRightEnemyBottom, hpPosW[1]);

					enemyBakuhatu.kLeftTop = enemy.kLeftEnemyTop;
					enemyBakuhatu.kLeftBottom = enemy.kLeftEnemyBottom;
					enemyBakuhatu.kRightTop = enemy.kRightEnemyTop;
					enemyBakuhatu.kRightBottom = enemy.kRightEnemyBottom;

					enemyBakuhatu.newLeftTop = MoveEnemy(enemyBakuhatu.position, enemyBakuhatu.kLeftTop, hpPosW[1]);
					enemyBakuhatu.newLeftBottom = MoveEnemy(enemyBakuhatu.position, enemyBakuhatu.kLeftBottom, hpPosW[1]);
					enemyBakuhatu.newRightTop = MoveEnemy(enemyBakuhatu.position, enemyBakuhatu.kRightTop, hpPosW[1]);
					enemyBakuhatu.newRightBottom = MoveEnemy(enemyBakuhatu.position, enemyBakuhatu.kRightBottom, hpPosW[1]);

					enemyLeft.kLeftTop = enemy.kLeftEnemyTop;
					enemyLeft.kLeftBottom = enemy.kLeftEnemyBottom;
					enemyLeft.kRightTop = enemy.kRightEnemyTop;
					enemyLeft.kRightBottom = enemy.kRightEnemyBottom;

					enemyLeft.newLeftTop = MoveEnemy(enemyLeft.position, enemyLeft.kLeftTop, hpPosW[1]);
					enemyLeft.newLeftBottom = MoveEnemy(enemyLeft.position, enemyLeft.kLeftBottom, hpPosW[1]);
					enemyLeft.newRightTop = MoveEnemy(enemyLeft.position, enemyLeft.kRightTop, hpPosW[1]);
					enemyLeft.newRightBottom = MoveEnemy(enemyLeft.position, enemyLeft.kRightBottom, hpPosW[1]);

					if (enemyEffectLeftCount > 0) {
						enemyEffectLeftCount--;
					}
					else {
						enemyEffectLeftCount = 40;
					}

					if (enemyEffectLeftCount <= 40) {
						drawEnemyMoveLeft = enemyMoveEff[4];
					}
					if (enemyEffectLeftCount <= 30) {
						drawEnemyMoveLeft = enemyMoveEff[5];
					}
					if (enemyEffectLeftCount <= 20) {
						drawEnemyMoveLeft = enemyMoveEff[6];
					}
					if (enemyEffectLeftCount <= 10) {
						drawEnemyMoveLeft = enemyMoveEff[7];
					}

					enemyRight.kLeftTop = enemy.kLeftEnemyTop;
					enemyRight.kLeftBottom = enemy.kLeftEnemyBottom;
					enemyRight.kRightTop = enemy.kRightEnemyTop;
					enemyRight.kRightBottom = enemy.kRightEnemyBottom;

					enemyRight.newLeftTop = MoveEnemy(enemyRight.position, enemyRight.kLeftTop, hpPosW[1]);
					enemyRight.newLeftBottom = MoveEnemy(enemyRight.position, enemyRight.kLeftBottom, hpPosW[1]);
					enemyRight.newRightTop = MoveEnemy(enemyRight.position, enemyRight.kRightTop, hpPosW[1]);
					enemyRight.newRightBottom = MoveEnemy(enemyRight.position, enemyRight.kRightBottom, hpPosW[1]);

					if (enemyEffectRightCount > 0) {
						enemyEffectRightCount--;
					}
					else {
						enemyEffectRightCount = 40;
					}

					if (enemyEffectRightCount <= 40) {
						drawEnemyMoveRight = enemyMoveEff[0];
					}
					if (enemyEffectRightCount <= 30) {
						drawEnemyMoveRight = enemyMoveEff[1];
					}
					if (enemyEffectRightCount <= 20) {
						drawEnemyMoveRight = enemyMoveEff[2];
					}
					if (enemyEffectRightCount <= 10) {
						drawEnemyMoveRight = enemyMoveEff[3];
					}

					//アイテム移動
					ItemSpawn(item, hpPosW[1]);
				}
				itemCounter = chkItemCounter(item, player, enemy, itemCounter, soundEffect,isCross);

				//bullet.squareTama = TransferAngle(bullet.squareTama);
#pragma endregion


				if (itemCounter.bossNum >= 10) {
					hitTime = 120;
				}
				if (hitTime > 0) {
					hitTime--;
				}

				bullet = chkAtkHit(bullet, enemy, soundEffect);

				enemyBullet = chkEnemyAtkHit(enemyBullet, item, player, soundEffect);
				itemHit = chkItemBulletHit(item, bullet);


				//itemCounter = chkItemCounter(item, player, enemy, itemCounter);

				bullet = setBulletType(keys, preKeys, bullet, itemCounter, player, soundEffect);
				itemCounter = updateCounter(keys, preKeys, itemCounter);
				bullet = playerAtkMove(keys, bullet, enemy);

				enemyBullet = setEnemyBullet(enemyBullet, itemCounter, enemy, soundEffect);
				enemyBullet = enemyAtkMove(enemyBullet, player, hitTime);


#pragma region hp and kougeki
				if (itemCounter.maruNum > 0 || itemCounter.triangleNum > 0 || itemCounter.squareNum > 0 || itemCounter.crossNum > 0) {
					if (!keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
						holdMaru = itemCounter.maruNum;
						holdSankaku = itemCounter.triangleNum;
						holdSikaku = itemCounter.squareNum;
					}
				}
				if (enemy.isHit) {
					if (holdSikaku <= 3) {
						itemCounter.bossNum -= 4;
						hpPosW[1] -= 5;
					}
					else if (holdSikaku >= 5) {
						itemCounter.bossNum -= 7;
						hpPosW[1] -= 10;
					}
					if (holdSankaku <= 3) {
						hpPosW[1] -=0.001f;
					}
					else if (holdSankaku >= 5) {
						hpPosW[1] -= 0.001f;
					}
					if (holdMaru <= 3) {
						hpPosW[1] -= 10;
					}
					else if (holdMaru >= 5) {
						hpPosW[1] -= 20;
					}

					holdSikaku = 0;
					holdSankaku = 0;
					holdMaru = 0;
				}
				//Novice::ScreenPrintf(0, 0, "%d",holdMaru);
				if (/*keys[DIK_9]&&preKeys[DIK_9]*/player.isHit || isCross) {
					hpPosW[0] -= 12;
					isPlayerBakuhatu = true;
					player.isHit = false;
					isCross = false;
				}
				if (/*keys[DIK_8] && preKeys[DIK_8]*/enemy.isHit) {
					isEnemyBakuhatu = true;
					enemy.isHit = false;
				}
				if (hpPosW[0] > 384) {
					hpPosW[0] = 384;
				}
				if (hpPosW[1] > 384) {
					hpPosW[1] = 384;
				}
				//Novice::ScreenPrintf(0, 0, "%d", /*itemCounter.crossNum*/holdBatu);

#pragma endregion

#pragma region sceneChange
				if (hpPosW[0] <= 0) {
					scene = badEnd;
				}
				if (hpPosW[1] <= 0) {
					scene = gameClear;
				}
#pragma endregion

#pragma region anime
#pragma region maru
				//マル用
				if (itemCounter.maruNum >= 1) {
					isItemUI[0] = true;
				}
				if (itemCounter.maruNum <= 0) {
					isItemUI[0] = false;
					if (!isItemUI[0]) {
						isItemErazeUI[0] = true;
						if (itemErazeTime[0] <= 0) {
							itemErazeTime[0] = 30;
						}

					}
				}
				if (isItemErazeUI[0]) {
					if (itemErazeTime[0] > 0) {
						itemErazeTime[0]--;
					}
				}
				if (itemErazeTime[0] <= 30) {
					drawEraze[0] = maruAnime[0];
				}
				if (itemErazeTime[0] <= 20) {
					drawEraze[0] = maruAnime[1];
				}
				if (itemErazeTime[0] <= 10) {
					drawEraze[0] = maruAnime[2];
				}
				if (itemErazeTime[0] <= 0) {
					isItemErazeUI[0] = false;
					isMaru[0] = false;
					isMaru[1] = false;
					isMaru[2] = false;
					isMaru[3] = false;
					isMaru[4] = false;
				}
				if (isItemUI[0]) {
					if (itemCounter.maruNum >= 1) {
						isMaru[0] = true;
					}
					if (itemCounter.maruNum >= 2) {
						isMaru[1] = true;
					}
					if (itemCounter.maruNum >= 3) {
						isMaru[2] = true;
					}
					if (itemCounter.maruNum >= 4) {
						isMaru[3] = true;
					}
					if (itemCounter.maruNum >= 5) {
						isMaru[4] = true;
					}
				}
#pragma endregion

#pragma region sankaku
				//三角用
				if (itemCounter.triangleNum >= 1) {
					isItemUI[1] = true;
				}
				if (itemCounter.triangleNum <= 0) {
					isItemUI[1] = false;
					if (!isItemUI[1]) {
						isItemErazeUI[1] = true;
						if (itemErazeTime[1] <= 0) {
							itemErazeTime[1] = 30;
						}

					}
				}
				if (isItemErazeUI[1]) {
					if (itemErazeTime[1] > 0) {
						itemErazeTime[1]--;
					}
				}
				if (itemErazeTime[1] <= 30) {
					drawEraze[1] = sankakuAnime[0];
				}
				if (itemErazeTime[1] <= 20) {
					drawEraze[1] = sankakuAnime[1];
				}
				if (itemErazeTime[1] <= 10) {
					drawEraze[1] = maruAnime[2];
				}
				if (itemErazeTime[1] <= 0) {
					isItemErazeUI[1] = false;
					isSankaku[0] = false;
					isSankaku[1] = false;
					isSankaku[2] = false;
					isSankaku[3] = false;
					isSankaku[4] = false;
				}
				if (isItemUI[1]) {
					if (itemCounter.triangleNum >= 1) {
						isSankaku[0] = true;
					}
					if (itemCounter.triangleNum >= 2) {
						isSankaku[1] = true;
					}
					if (itemCounter.triangleNum >= 3) {
						isSankaku[2] = true;
					}
					if (itemCounter.triangleNum >= 4) {
						isSankaku[3] = true;
					}
					if (itemCounter.triangleNum >= 5) {
						isSankaku[4] = true;
					}
				}
#pragma endregion

#pragma region heart
				//ハート用
				if (itemCounter.heartNum >= 1) {
					isItemUI[2] = true;
				}
				if (itemCounter.heartNum <= 0) {
					isItemUI[2] = false;
					if (!isItemUI[2]) {
						isItemErazeUI[2] = true;
						if (itemErazeTime[2] <= 0) {
							itemErazeTime[2] = 30;
						}

					}
				}
				if (isItemErazeUI[2]) {
					if (itemErazeTime[2] > 0) {
						itemErazeTime[2]--;
					}
				}
				if (itemErazeTime[2] <= 30) {
					drawEraze[2] = maruAnime[0];
				}
				if (itemErazeTime[2] <= 20) {
					drawEraze[2] = maruAnime[1];
				}
				if (itemErazeTime[2] <= 10) {
					drawEraze[2] = maruAnime[2];
				}
				if (itemErazeTime[2] <= 0) {
					isItemErazeUI[2] = false;
					isHeart[0] = false;
					isHeart[1] = false;
					isHeart[2] = false;
					isHeart[3] = false;
					isHeart[4] = false;
				}
				if (isItemUI[2]) {
					if (itemCounter.heartNum >= 1) {
						isHeart[0] = true;
					}
					if (itemCounter.heartNum >= 2) {
						isHeart[1] = true;
					}
					if (itemCounter.heartNum >= 3) {
						isHeart[2] = true;
					}
					if (itemCounter.heartNum >= 4) {
						isHeart[3] = true;
					}
					if (itemCounter.heartNum >= 5) {
						isHeart[4] = true;
					}
				}
#pragma endregion

#pragma region square
				//四角用
				if (itemCounter.squareNum >= 1) {
					isItemUI[3] = true;
				}
				if (itemCounter.squareNum <= 0) {
					isItemUI[3] = false;
					if (!isItemUI[3]) {
						isItemErazeUI[3] = true;
						if (itemErazeTime[3] <= 0) {
							itemErazeTime[3] = 30;
						}

					}
				}
				if (isItemErazeUI[3]) {
					if (itemErazeTime[3] > 0) {
						itemErazeTime[3]--;
					}
				}
				if (itemErazeTime[3] <= 30) {
					drawEraze[3] = sikakuAnime[0];
				}
				if (itemErazeTime[3] <= 20) {
					drawEraze[3] = sikakuAnime[1];
				}
				if (itemErazeTime[3] <= 10) {
					drawEraze[3] = maruAnime[2];
				}
				if (itemErazeTime[3] <= 0) {
					isItemErazeUI[3] = false;
					isSikaku[0] = false;
					isSikaku[1] = false;
					isSikaku[2] = false;
					isSikaku[3] = false;
					isSikaku[4] = false;
				}
				if (isItemUI[3]) {
					if (itemCounter.squareNum >= 1) {
						isSikaku[0] = true;
					}
					if (itemCounter.squareNum >= 2) {
						isSikaku[1] = true;
					}
					if (itemCounter.squareNum >= 3) {
						isSikaku[2] = true;
					}
					if (itemCounter.squareNum >= 4) {
						isSikaku[3] = true;
					}
					if (itemCounter.squareNum >= 5) {
						isSikaku[4] = true;
					}
				}
				//Novice::ScreenPrintf(100, 100, "%f", itemErazeTime);

#pragma endregion

#pragma region PlayerFlyEffectAnime
				if (effectAnimeTime > 0) {
					effectAnimeTime--;
				}
				else {
					effectAnimeTime = 60;
				}
				if (effectAnimeTime <= 60) {
					drawPlayerEffect = playerEffect[0];
				}
				if (effectAnimeTime <= 50) {
					drawPlayerEffect = playerEffect[1];
				}
				if (effectAnimeTime <= 40) {
					drawPlayerEffect = playerEffect[2];
				}
				if (effectAnimeTime <= 30) {
					drawPlayerEffect = playerEffect[3];
				}
				if (effectAnimeTime <= 20) {
					drawPlayerEffect = playerEffect[4];
				}
				if (effectAnimeTime <= 10) {
					drawPlayerEffect = playerEffect[5];
				}
#pragma endregion

#pragma region greenBulletAnime

				/*if (greenBulletAnime > 0) {
					greenBulletAnime--;
				}
				else {
					greenBulletAnime = 40;
				}
				if (greenBulletAnime <= 40) {
					drawBullet = greenTexture[0];
				}
				if (greenBulletAnime <= 30) {
					drawBullet = greenTexture[1];
				}
				if (greenBulletAnime <= 20) {
					drawBullet = greenTexture[2];
				}
				if (greenBulletAnime <= 10) {
					drawBullet = greenTexture[3];
				}*/
#pragma endregion

#pragma region enemy bakuhatu
				if (isEnemyBakuhatu) {
					bakuhatuCount[0]--;
				}
				else {
					bakuhatuCount[0] = 45;
				}
				if (bakuhatuCount[0] <= 45) {
					drawBakuhatu[0] = enemy.bakuhatu[0];
				}
				if (bakuhatuCount[0] <= 42) {
					drawBakuhatu[0] = enemy.bakuhatu[1];
				}
				if (bakuhatuCount[0] <= 39) {
					drawBakuhatu[0] = enemy.bakuhatu[2];
				}
				if (bakuhatuCount[0] <= 36) {
					drawBakuhatu[0] = enemy.bakuhatu[3];
				}
				if (bakuhatuCount[0] <= 33) {
					drawBakuhatu[0] = enemy.bakuhatu[4];
				}
				if (bakuhatuCount[0] <= 30) {
					drawBakuhatu[0] = enemy.bakuhatu[5];
				}
				if (bakuhatuCount[0] <= 27) {
					drawBakuhatu[0] = enemy.bakuhatu[6];
				}
				if (bakuhatuCount[0] <= 24) {
					drawBakuhatu[0] = enemy.bakuhatu[7];
				}
				if (bakuhatuCount[0] <= 21) {
					drawBakuhatu[0] = enemy.bakuhatu[8];
				}
				if (bakuhatuCount[0] <= 18) {
					drawBakuhatu[0] = enemy.bakuhatu[9];
				}
				if (bakuhatuCount[0] <= 15) {
					drawBakuhatu[0] = enemy.bakuhatu[10];
				}
				if (bakuhatuCount[0] <= 12) {
					drawBakuhatu[0] = enemy.bakuhatu[11];
				}
				if (bakuhatuCount[0] <= 9) {
					drawBakuhatu[0] = enemy.bakuhatu[12];
				}
				if (bakuhatuCount[0] <= 6) {
					drawBakuhatu[0] = enemy.bakuhatu[13];
				}
				if (bakuhatuCount[0] <= 3) {
					drawBakuhatu[0] = enemy.bakuhatu[14];
				}
				if (bakuhatuCount[0] <= 0) {
					isEnemyBakuhatu = false;
				}
#pragma endregion

#pragma region player bakuhatu
				if (isPlayerBakuhatu) {
					bakuhatuCount[1]--;
				}
				else {
					bakuhatuCount[1] = 45;
				}
				if (bakuhatuCount[1] <= 45) {
					drawBakuhatu[1] = enemy.bakuhatu[0];
				}
				if (bakuhatuCount[1] <= 42) {
					drawBakuhatu[1] = enemy.bakuhatu[1];
				}
				if (bakuhatuCount[1] <= 39) {
					drawBakuhatu[1] = enemy.bakuhatu[2];
				}
				if (bakuhatuCount[1] <= 36) {
					drawBakuhatu[1] = enemy.bakuhatu[3];
				}
				if (bakuhatuCount[1] <= 33) {
					drawBakuhatu[1] = enemy.bakuhatu[4];
				}
				if (bakuhatuCount[1] <= 30) {
					drawBakuhatu[1] = enemy.bakuhatu[5];
				}
				if (bakuhatuCount[1] <= 27) {
					drawBakuhatu[1] = enemy.bakuhatu[6];
				}
				if (bakuhatuCount[1] <= 24) {
					drawBakuhatu[1] = enemy.bakuhatu[7];
				}
				if (bakuhatuCount[1] <= 21) {
					drawBakuhatu[1] = enemy.bakuhatu[8];
				}
				if (bakuhatuCount[1] <= 18) {
					drawBakuhatu[1] = enemy.bakuhatu[9];
				}
				if (bakuhatuCount[1] <= 15) {
					drawBakuhatu[1] = enemy.bakuhatu[10];
				}
				if (bakuhatuCount[1] <= 12) {
					drawBakuhatu[1] = enemy.bakuhatu[11];
				}
				if (bakuhatuCount[1] <= 9) {
					drawBakuhatu[1] = enemy.bakuhatu[12];
				}
				if (bakuhatuCount[1] <= 6) {
					drawBakuhatu[1] = enemy.bakuhatu[13];
				}
				if (bakuhatuCount[1] <= 3) {
					drawBakuhatu[1] = enemy.bakuhatu[14];
				}
				if (bakuhatuCount[1] <= 0) {
					isPlayerBakuhatu = false;
				}
#pragma endregion

#pragma region bossAnime
				if (itemCounter.bossNum <= 0) {
					itemCounter.bossNum = 0;
				}
				drawEnemy = enemy.texture[itemCounter.bossNum];
#pragma endregion

#pragma endregion

			}

		///
		///更新処理:ここから
		/// 
		
		///
		/// 描画処理:ここから
		///
		backround = DrawBackround(backround);

		player = DrawPlayer(player);

		
		if (isSamonBoss) {
			DrawItem(item,itemHit);
			
			bullet = DrawBullet(bullet);
			enemyBullet = DrawEnemyBullet(enemyBullet);

			if (isEnemyBakuhatu) {
				Novice::DrawQuad(
					(int)enemyBakuhatu.newLeftTop.position.x,
					(int)enemyBakuhatu.newLeftTop.position.y,
					(int)enemyBakuhatu.newRightTop.position.x,
					(int)enemyBakuhatu.newRightTop.position.y,
					(int)enemyBakuhatu.newLeftBottom.position.x,
					(int)enemyBakuhatu.newLeftBottom.position.y,
					(int)enemyBakuhatu.newRightBottom.position.x,
					(int)enemyBakuhatu.newRightBottom.position.y,
					0, 0, 128, 128, drawBakuhatu[0], WHITE);
			}

			if (enemyLeft.newLeftTop.type==1) {
				Novice::DrawQuad(
					(int)enemyLeft.newLeftTop.position.x,
					(int)enemyLeft.newLeftTop.position.y,
					(int)enemyLeft.newRightTop.position.x,
					(int)enemyLeft.newRightTop.position.y,
					(int)enemyLeft.newLeftBottom.position.x,
					(int)enemyLeft.newLeftBottom.position.y,
					(int)enemyLeft.newRightBottom.position.x,
					(int)enemyLeft.newRightBottom.position.y,
					0, 0, 128, 128, drawEnemyMoveLeft, WHITE);
			}

			if (enemyLeft.newLeftTop.type == 0) {
				Novice::DrawQuad(
					(int)enemyRight.newLeftTop.position.x,
					(int)enemyRight.newLeftTop.position.y,
					(int)enemyRight.newRightTop.position.x,
					(int)enemyRight.newRightTop.position.y,
					(int)enemyRight.newLeftBottom.position.x,
					(int)enemyRight.newLeftBottom.position.y,
					(int)enemyRight.newRightBottom.position.x,
					(int)enemyRight.newRightBottom.position.y,
					0, 0, 128, 128, drawEnemyMoveRight, WHITE);
			}

			if (isPlayerBakuhatu) {
				Novice::DrawQuad(
					(int)playerBakuhatu.newLeftTop.position.x,
					(int)playerBakuhatu.newLeftTop.position.y,
					(int)playerBakuhatu.newRightTop.position.x,
					(int)playerBakuhatu.newRightTop.position.y,
					(int)playerBakuhatu.newLeftBottom.position.x,
					(int)playerBakuhatu.newLeftBottom.position.y,
					(int)playerBakuhatu.newRightBottom.position.x,
					(int)playerBakuhatu.newRightBottom.position.y,
					0, 0, 128, 128, drawBakuhatu[1], WHITE);
			}

			enemy = DrawEnemy(enemy, drawEnemy);
#pragma region  player effect
			Novice::DrawQuad((int)playerEffectPos.newLeftTop.position.x,
				(int)playerEffectPos.newLeftTop.position.y,
				(int)playerEffectPos.newRightTop.position.x,
				(int)playerEffectPos.newRightTop.position.y,
				(int)playerEffectPos.newLeftBottom.position.x,
				(int)playerEffectPos.newLeftBottom.position.y,
				(int)playerEffectPos.newRightBottom.position.x,
				(int)playerEffectPos.newRightBottom.position.y,
				0, 0, 128, 128, drawPlayerEffect, WHITE);

			if (keys[DIK_A] || keys[DIK_LEFT]) {
				Novice::DrawQuad(
					(int)playerLeftEffect.newLeftTop.position.x,
					(int)playerLeftEffect.newLeftTop.position.y,
					(int)playerLeftEffect.newRightTop.position.x,
					(int)playerLeftEffect.newRightTop.position.y,
					(int)playerLeftEffect.newLeftBottom.position.x,
					(int)playerLeftEffect.newLeftBottom.position.y,
					(int)playerLeftEffect.newRightBottom.position.x,
					(int)playerLeftEffect.newRightBottom.position.y,
					0, 0, 128, 128, drawLeftEff, WHITE);
			}
			if (keys[DIK_D] || keys[DIK_RIGHT]) {
				Novice::DrawQuad(
					(int)playerRightEffect.newLeftTop.position.x,
					(int)playerRightEffect.newLeftTop.position.y,
					(int)playerRightEffect.newRightTop.position.x,
					(int)playerRightEffect.newRightTop.position.y,
					(int)playerRightEffect.newLeftBottom.position.x,
					(int)playerRightEffect.newLeftBottom.position.y,
					(int)playerRightEffect.newRightBottom.position.x,
					(int)playerRightEffect.newRightBottom.position.y,
					0, 0, 128, 128, drawRightEff, WHITE);
			}
#pragma endregion


#pragma region bullet
			
			////Novice::DrawBox(int(target[0].x), int(target[0].y), 20, 20, 0.0f, WHITE, kFillModeWireFrame);
			//if (isShot[0]) {
			//	Novice::DrawSprite((int)posX[0], (int)posY[0], drawBullet, 2, 2, angle[0], WHITE);
			//}

			///*if (isShot[1]) {
			//	Novice::DrawSprite((int)posX[1], (int)posY[1], drawBullet, 1, 1, angle[1], WHITE);
			//}*/
			
#pragma endregion
		}

		if (!isSamonBoss) {
			Novice::DrawSprite((int)startBoss.x, (int)startBoss.y, enemy.img[0], 1.0f / 1.5f, 1.0f / 1.5f, 90 / float(M_PI) * 180.0f + 0.3f, WHITE);
		}

#pragma region DrawMaru
		if (isItemUI[0]) {
			if (isMaru[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, item[maru][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isMaru[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, item[maru][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isMaru[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, item[maru][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isMaru[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, item[maru][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isMaru[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, item[maru][0].img, 1, 1, 0.0f, WHITE);
			}
		}

		if (isItemErazeUI[0]) {
			if (isMaru[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isMaru[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isMaru[2]){
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isMaru[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isMaru[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
		}
#pragma endregion

#pragma region Draw sankaku
		if (isItemUI[1]) {
			if (isSankaku[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, item[triangle][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, item[triangle][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, item[triangle][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, item[triangle][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, item[triangle][0].img, 1, 1, 0.0f, WHITE);
			}
		}

		if (isItemErazeUI[1]) {
			if (isSankaku[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
			if (isSankaku[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, drawEraze[0], 1, 1, 0.0f, WHITE);
			}
		}
#pragma endregion

#pragma region DrawHeart
		if (isItemUI[2]) {
			if (isHeart[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, item[heart][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isHeart[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, item[heart][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isHeart[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, item[heart][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isHeart[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, item[heart][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isHeart[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, item[heart][0].img, 1, 1, 0.0f, WHITE);
			}
		}

		if (isItemErazeUI[2]) {
			if (isHeart[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, drawEraze[2], 1, 1, 0.0f, WHITE);
			}
			if (isHeart[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, drawEraze[2], 1, 1, 0.0f, WHITE);
			}
			if (isHeart[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, drawEraze[2], 1, 1, 0.0f, WHITE);
			}
			if (isHeart[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, drawEraze[2], 1, 1, 0.0f, WHITE);
			}
			if (isHeart[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, drawEraze[2], 1, 1, 0.0f, WHITE);
			}
		}
#pragma endregion

#pragma region DrawSikaku
		if (isItemUI[3]) {
			if (isSikaku[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, item[square][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, item[square][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, item[square][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, item[square][0].img, 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, item[square][0].img, 1, 1, 0.0f, WHITE);
			}
		}

		if (isItemErazeUI[3]) {
			if (isSikaku[0]) {
				Novice::DrawSprite((int)itemUI[0].x, (int)itemUI[0].y, drawEraze[3], 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[1]) {
				Novice::DrawSprite((int)itemUI[1].x, (int)itemUI[1].y, drawEraze[3], 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[2]) {
				Novice::DrawSprite((int)itemUI[2].x, (int)itemUI[2].y, drawEraze[3], 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[3]) {
				Novice::DrawSprite((int)itemUI[3].x, (int)itemUI[3].y, drawEraze[3], 1, 1, 0.0f, WHITE);
			}
			if (isSikaku[4]) {
				Novice::DrawSprite((int)itemUI[4].x, (int)itemUI[4].y, drawEraze[3], 1, 1, 0.0f, WHITE);
			}
		}
#pragma endregion

#pragma region HPBAR
		Novice::DrawQuad((int)playerHP.leftTop.x, (int)playerHP.leftTop.y,
			(int)playerHP.rightTop.x+(int)hpPosW[0], (int)playerHP.rightTop.y,
			(int)playerHP.leftBottom.x, (int)playerHP.leftBottom.y,
			(int)playerHP.rightBottom.x + (int)hpPosW[0], (int)playerHP.rightBottom.y,
			0, 0, (int)hpPosW[0], 64, hpBar, WHITE);

		Novice::DrawQuad((int)enemyHP.leftTop.x, (int)enemyHP.leftTop.y,
			(int)enemyHP.rightTop.x + (int)hpPosW[1], (int)enemyHP.rightTop.y,
			(int)enemyHP.leftBottom.x, (int)enemyHP.leftBottom.y,
			(int)enemyHP.rightBottom.x + (int)hpPosW[1], (int)enemyHP.rightBottom.y,
			0, 0, (int)hpPosW[1], 64, hpBar, WHITE);
#pragma endregion

		if (isESC) {
			Novice::DrawSprite((int)ESCPos.x, (int)ESCPos.y, sousa, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)siyou.x, (int)siyou.y, siyouTexture, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)controlLeft.x, (int)controlLeft.y, drawConLeft, 1, 1, 0.0f, WHITE);
			Novice::DrawSprite((int)controlRight.x, (int)controlRight.y, drawConRight, 1, 1, 0.0f, WHITE);
		}
		
		///
		///描画処理:ここまで
		///
		

			
			break;

#pragma endregion


#pragma region BADEND
			case badEnd:
				///
				///更新処理:ここから
				/// 
				mouseDisplay = 1;
				if (Novice::IsPlayingAudio(soundHandle[2]) == 0) {
					soundHandle[2] = Novice::PlayAudio(BGM[2], true, 0.5f);
				}
				/*if (keys[DIK_K]) {
					scene = game;
				}*/
				easingTime[3] += 1.0f / 60.0f;
				easingTime[4] += 1.0f / 60.0f;
				if (!isBack[1]) {
					badTitle = EasingPosition(badTitleBegin, badTitleEnd, 2, easingTime[3]);
					badClick[0] = EasingPosition(badClickBegin[0], badClickEnd[0], 2, easingTime[4]);
					badClick[1] = EasingPosition(badClickBegin[1], badClickEnd[1], 2, easingTime[4]);
				}
				
				if (easingTime[4] >= 1) {
					if (Hit(badClick[0].x, badClick[0].y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)) {
						drawBadClick = badTitlePush[1];
						if (Novice::IsTriggerMouse(0)) {
							drawBadClick = badTitlePush[2];
							easingTime[3] = 0;
							easingTime[4] = 0;
							isBack[1] = true;
							isBackTitle = true;
							if (!isSelect[1]) {
								if (SECount[3] <= 0) {
									SECount[3] = 5;
								}
								isSelect[1] = true;
							}
							if (SECount[3] > 0) {
								SECount[3]--;
							}
						}
					}
					
					else if (Hit(badClick[1].x, badClick[1].y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)) {
						drawBadExit = closePush[2];
						if (Novice::IsTriggerMouse(0)) {
							drawBadExit = closePush[1];
							easingTime[3] = 0;
							easingTime[4] = 0;
							isBack[1] = true;
							isClose = true;
							if (!isSelect[2]) {
								if (SECount[4] <= 0) {
									SECount[4] = 5;
								}
								isSelect[2] = true;
							}
							if (SECount[4] > 0) {
								SECount[4]--;
							}
						}
					}
					else {
						drawBadExit = closePush[0];
						SECount[4] = 0;
						isSelect[2] = false;
					    drawBadClick = badTitlePush[0];
					    SECount[3] = 0;
					    isSelect[1] = false;
					}
				}
				if (isBack[1]) {
					badTitle = EasingPosition(badTitleEnd, badTitleBegin, 1, easingTime[3]);
					badClick[0] = EasingPosition( badClickEnd[0], badClickBegin[0], 1, easingTime[4]);
					badClick[1] = EasingPosition( badClickEnd[1], badClickBegin[1], 1, easingTime[4]);
				}

				if (isBackTitle && easingTime[4] >= 1) {
					scene = title;
				}
				if (isClose && easingTime[4] >= 1) {
					isExit = true;
				}
				if (!Hit(titlePushResult.x, titlePushResult.y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)) {
					//SECount[2] = 0;
					if (Novice::IsTriggerMouse(0)) {
						/*isSE[0] = true;*/
						SECount[5] = 5;
					}
					if (SECount[5] > 0) {
						SECount[5]--;
					}
				}
				else {
					SECount[5] = 0;
				}
				IsPlaySE(SE[1], SEHandle[5], SECount[5], 5);
				/*IsPlaySE(SE[2], SEHandle[3], SECount[3], 5);
				IsPlaySE(SE[2], SEHandle[4], SECount[4], 5);*/
				//Novice::ScreenPrintf(0, 0, "%f", SECount[5]);
				///
				///更新処理:ここまで
				/// 
				
				///
				///	描画処理:ここから
				/// 
				Novice::DrawSprite(0, 0, black, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)badTitle.x, (int)badTitle.y, badMoji, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)badClick[0].x,(int)badClick[0].y, drawBadClick, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)badClick[1].x, (int)badClick[1].y, drawBadExit, 1, 1, 0.0f, WHITE);

				///
				///描画処理:ここまで
				/// 
				break;
#pragma endregion


#pragma region CLER
			case gameClear:
				///
				///更新処理:ここから
				/// 
				
				mouseDisplay = 1;
				if (Novice::IsPlayingAudio(soundHandle[3]) == 0) {
					soundHandle[3] = Novice::PlayAudio(BGM[3], true, 0.5f);
				}

				easingTime[3] += 1.0f / 60.0f;
				easingTime[4] += 1.0f / 60.0f;
				if (!isBack[1]) {
					badTitle = EasingPosition(badTitleBegin, badTitleEnd, 2, easingTime[3]);
					badClick[0] = EasingPosition(badClickBegin[0], badClickEnd[0], 2, easingTime[4]);
					badClick[1] = EasingPosition(badClickBegin[1], badClickEnd[1], 2, easingTime[4]);
				}

				if (easingTime[4] >= 1) {
					if (Hit(badClick[0].x, badClick[0].y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)) {
						drawClearClick = badTitlePush[1];
						if (Novice::IsTriggerMouse(0)) {
							drawClearClick = badTitlePush[2];
							easingTime[3] = 0;
							easingTime[4] = 0;
							isBack[1] = true;
							isBackTitle = true;
							/*if (!isSelect[1]) {
								if (SECount[3] <= 0) {
									SECount[3] = 5;
								}
								isSelect[1] = true;
							}
							if (SECount[3] > 0) {
								SECount[3]--;
							}*/
						}
					}
				

					else if (Hit(badClick[1].x, badClick[1].y, 384, 128, (float)mouseX, (float)mouseY, 0, 0)) {
						drawClearExit = closePush[2];
						if (Novice::IsTriggerMouse(0)) {
							drawClearExit = closePush[1];
							easingTime[3] = 0;
							easingTime[4] = 0;
							isBack[1] = true;
							isClose = true;
							/*if (!isSelect[2]) {
								if (SECount[4] <= 0) {
									SECount[4] = 5;
								}
								isSelect[2] = true;
							}
							if (SECount[4] > 0) {
								SECount[4]--;
							}*/
						}
					}
					else {
						drawClearExit = closePush[0];
						drawClearClick = badTitlePush[0];
						//SECount[4] = 0;
						//isSelect[2] = false;
					}
				}
				if (isBack[1]) {
					badTitle = EasingPosition(badTitleEnd, badTitleBegin, 1, easingTime[3]);
					badClick[0] = EasingPosition(badClickEnd[0], badClickBegin[0], 1, easingTime[4]);
					badClick[1] = EasingPosition(badClickEnd[1], badClickBegin[1], 1, easingTime[4]);
				}

				if (isBackTitle && easingTime[4] >= 1) {
					scene = title;
				}
				if (isClose && easingTime[4] >= 1) {
					isExit = true;
				}
				///
				///更新処理:ここまで
				/// 

				///
				///	描画処理:ここから
				/// 
				//Novice::DrawSprite(0, 0, black, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite(0, 0, clearBg, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)badTitle.x, (int)badTitle.y, clearMoji, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)badClick[0].x, (int)badClick[0].y, drawClearClick, 1, 1, 0.0f, WHITE);
				Novice::DrawSprite((int)badClick[1].x, (int)badClick[1].y, drawClearExit, 1, 1, 0.0f, WHITE);
				///
				///描画処理:ここまで
				/// 
				break;
#pragma endregion

		}
		///
		/// ↑ゲームの処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (/*preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0||*/isExit) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
