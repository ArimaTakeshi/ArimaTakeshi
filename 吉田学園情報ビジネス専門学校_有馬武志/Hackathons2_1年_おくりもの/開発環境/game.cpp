//=========================================================================================================//
//
// ゲーム処理 [game.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "fade.h"
#include "main.h"
#include "sound.h"

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
bool bPause;		//Pauseしてるかどうか
bool bStart;		//起動時のエンター
int g_nCountTime;		//時間カウント

//=========================================================================================================//
// * ゲームの初期化処理
//=========================================================================================================//
void InitGame(void)
{
	PLAYER *pPlayer = GetPlayer();
	char aStr[8] = "SCORE ";
	InitDigital();
	InitFont();
	InitEnemy();
	InitBlock();
	InitBullet();
	InitExplosion();
	InitAnimation();
	InitPlayer();
	InitGameWindow();

	bPause = false;
	g_nCountTime = 0;
	
	//SetFontDamage({ 0, 10, SCREEN_WIDTH, 100 }, D3DCOLOR_RGBA(255, 255, 5, 255), &aStr[0], 1, FONTSTATE_NONE);
	SetBlock(D3DXVECTOR3(0, FIELD + 3000, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1000000, 5, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_OUT);

	SetBlock(D3DXVECTOR3(400, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(1200, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 1, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(1300, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(1800, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(1900, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(2400, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 2, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(2500, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(3200, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 100, 1, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(3400, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_SLIME, 50, 1, 1, 1, 1, 1, 777, D3DX_PI, ENEMYTYPE_NORMALENEMY);

	SetBlock(D3DXVECTOR3(4300, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 100, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(4500, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(5300, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 100, 2, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(5500, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(6300, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 100, 2, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(6300, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_BAT, 50, 1, 1, 1, 1, 1, 1500, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(6500, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(6900, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(7500, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(7400, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);
	SetEnemy(D3DXVECTOR3(7600, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_SLIME, 50, 1, 1, 1, 1, 1, 500, D3DX_PI, ENEMYTYPE_NORMALENEMY);

	SetBlock(D3DXVECTOR3(8300, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(8500, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(9000, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(9500, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(9500, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_BAT, 50, 1, 1, 1, 1, 1, 1500, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(9100, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);
	SetBlock(D3DXVECTOR3(9900, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(10600, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 100, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(10600, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(11400, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(11300, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_BAT, 50, 1, 1, 1, 1, 1, 1500, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(11500, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(12000, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(11900, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_SLIME, 50, 1, 1, 1, 1, 1, 777, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(12100, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(12600, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 1, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(12500, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_SLIME, 50, 1, 1, 1, 1, 1, 777, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(12500, FIELD + 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(13300, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 300, 100, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(14300, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(14300, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_INSECT, 50, 1, 1, 1, 1, 1, 3700, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(13900, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);
	SetBlock(D3DXVECTOR3(14700, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(15200, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(16100, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 500, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetEnemy(D3DXVECTOR3(16100, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_INSECT, 50, 1, 1, 1, 1, 1, 3700, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetBlock(D3DXVECTOR3(15700, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);
	SetBlock(D3DXVECTOR3(16500, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(16900, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(17300, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(17250, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);
	SetEnemy(D3DXVECTOR3(17300, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_BAT, 50, 1, 1, 1, 1, 1, 1500, D3DX_PI, ENEMYTYPE_NORMALENEMY);

	SetBlock(D3DXVECTOR3(17700, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(17650, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	SetBlock(D3DXVECTOR3(18100, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(18500, FIELD - 100, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 50, 30, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);
	SetEnemy(D3DXVECTOR3(18100, FIELD - 490, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_BAT, 50, 1, 1, 1, 1, 1, 1500, D3DX_PI, ENEMYTYPE_NORMALENEMY);

	SetBlock(D3DXVECTOR3(18500, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(19000, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 200, 100, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(19500, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 20, 5, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(23000, FIELD - 90, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 3000, 20, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_CLEAR);
	//SetBlock(D3DXVECTOR3(800, FIELD + 190, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 3, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN0);

	//SetAnimation((D3DXVECTOR3(-950, FIELD - 20, 0.0f)), 20, 17, 1, 1, 999999, 4, 0, ANIMATION_LOOP, ANIMTYPE_POWERUP);


	SetGameWindow(D3DXVECTOR3(800.0f, 5, 0.0f), D3DXCOLOR(0.3f, 0.0f, 0.0f, 1.0f), 200, 50, 1, 0, WINDOWSTATE_NORMAL, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.87f - 35.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 36, 90, 0, 0, WINDOWSTATE_NORMAL, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f - 5.0f, SCREEN_HEIGHT * 0.87f - 5.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 400, 60, 0, 0, WINDOWSTATE_MAXEXPGAGE, WINDOWUSE_PLAYER);
	////SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f - 5.0f, SCREEN_HEIGHT * 0.87f - 5.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 400, 45, 0, 0, WINDOWSTATE_MAXLIFEGAGE, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f, 0.0f), D3DXCOLOR(0.8f, 0.1f, 0.02f, 1.0f), 100, 35, 0, 0, WINDOWSTATE_AUTOLIFEGAGE, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f, 0.0f), D3DXCOLOR(0.25f, 1.0f, 0.1f, 1.0f), 300, 35, 0, 0, WINDOWSTATE_LIFEGAGE, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f + 40.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 400, 10, 0, 0, WINDOWSTATE_EXPGAGE, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f + 40.0f, 0.0f), D3DXCOLOR(0.4f, 0.98f, 1.0f, 1.0f), 400, 10, 0, 0, WINDOWSTATE_AUTOEXPGAGE, WINDOWUSE_PLAYER);
	//SetFont({ 200, 590, SCREEN_WIDTH, 700 }, D3DCOLOR_RGBA(255, 255, 255, 255), &aStr[0], 0, 12, 30, FONTSTATE_NONE);
	//SetFont({ 200, 625, SCREEN_WIDTH, 700 }, D3DCOLOR_RGBA(255, 255, 255, 255), &aStr[0], 1, 12, 30, FONTSTATE_NONE);

	//SetAnimation(D3DXVECTOR3(SCREEN_WIDTH * 0.07f, SCREEN_HEIGHT * 0.87f, 0.0f), 130, 80, 11, 1, 9999, 1, 0, ANIMATION_PLAYER, ANIMTYPE_NONE);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5, 0.0f), COLLAR{ 200,200,200, 255 }, 1.0f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, WINDOWSTATE_BG);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.001f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, WINDOWSTATE_SCROLL1);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0008f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, WINDOWSTATE_SCROLL1);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0006f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, WINDOWSTATE_SCROLL0);
	//SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 200 }, 0.0012f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, WINDOWSTATE_SCROLL1);

	SetGameState(GAMESTATE_NORMAL, MODE_GAME, 0);
	SetFont({ SCREEN_WIDTH / 2 - 100, 10, SCREEN_WIDTH, 100 }, D3DCOLOR_RGBA(255, 255, 255, 255), &aStr[0], 2, 12, 30, FONTSTATE_NONE);

	SettingPlayer();
	StopSound();

	PlaySound(SOUND_LABEL_FBGM000);
	
	InitScroll();

}
//=========================================================================================================//
// * ゲームの更新処理
//=========================================================================================================//
void InitGame0(void)
{
	bStart = true;
}
//=========================================================================================================//
// * ゲームの終了処理
//=========================================================================================================//
void UninitGame(void)
{
	GAME *pGame;	//現在の状態をポインタで取得
	pGame = GetGameState();
	pGame[0].now = GAMESTATE_NONE;
	BreakFont();
	BreakBGWindow();
	BreakWindow();
	UninitPlayer();
	UninitFont();
	UninitEnemy();
	BreakBlock();
	UninitBlock();
	UninitBullet();
	UninitExplosion();
	UninitAnimation();
	UninitGameWindow();
	UninitDigital();

	StopSound();
}
//=========================================================================================================//
// * ゲームの更新処理
//=========================================================================================================//
void UpdateGame(void)
{
	GAME *pGame;	//現在の状態をポインタで取得
	static int nNumber;
	PLAYER *pPlayer = GetPlayer();

	pGame = GetGameState();

	if (GetKeyboardTrigger(DIK_RETURN) == true) { bStart = false; }
	if (bStart == false)
	{
		switch (pGame[0].now)
		{//ゲーム状態に応じた処理開始
		case GAMESTATE_NONE:
			break;

		case GAMESTATE_NORMAL:
			if (bPause == false)
			{
				nNumber = 0;
				if (pPlayer[0].nTime[0] > 0)
				{
					UpdateBGWindow();
					UpdateFont();
					UpdateEnemy();
					UpdateBullet();
					UpdatePlayer();
					UpdateBlock();
					WideScroll();
					UpdateExplosion();
					UpdateAnimation();
					UpdateGameWindow();
					UpdateDigital();
				}
			}
			else
			{
				if (GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_UP) == true)
				{//上移動
					PlaySound(SOUND_LABEL_BOTTON001);
					nNumber = (nNumber + 2) % 3;
				}
				if (GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_DOWN) == true)
				{//下移動
					PlaySound(SOUND_LABEL_BOTTON001);
					nNumber = (nNumber + 1) % 3;
				}

				SelectWindow(nNumber);
				if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_Z) == true)
				{
					PlaySound(SOUND_LABEL_BOTTON000);
					bPause = false;
					if (nNumber == 0)
					{//戻る
						BackWindow(4);
					}
					else if (nNumber == 1)
					{//初めから
						pPlayer[0].nEXP = 0;
						InitPlayer0();
						SetFade(MODE_GAME, 0);
					}
					else if (nNumber == 2)
					{//Titleへ
						SetFade(MODE_TITLE, 0);		//Titleへ
					}
				}
			}
			if (GetKeyboardTrigger(DIK_P) == true && bPause == false)
			{//Pを押したらpause画面
				PlaySound(SOUND_LABEL_BOTTON000);
				BackWindow(1);
				bPause = true;
				SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 4, 0, 0, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL);
				SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXCOLOR{ 0.23f,0.23f,0.23f, 1.0f }, 150, 30, 5, 0, 0, WINDOWSTATE_SELECTOFF, WINDOWUSE_SELECT);
				SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 0.23f,0.23f,0.23f, 1.0f }, 150, 30, 6, 1, 0, WINDOWSTATE_SELECTOFF, WINDOWUSE_SELECT);
				SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXCOLOR{ 0.23f,0.23f,0.23f, 1.0f }, 150, 30, 7, 2, 0, WINDOWSTATE_SELECTOFF, WINDOWUSE_SELECT);
			}
			else if (GetKeyboardTrigger(DIK_P) == true)
			{//Pを押したらpause解く
				PlaySound(SOUND_LABEL_BOTTON000);
				bPause = false;
				BackWindow(4);
				//SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.9f, 0.0f), D3DXCOLOR{ 1.0f,0.99f,0.04f, 0 }, 150, 30, 0, 0, 0, WINDOWSTATE_FLASH, WINDOWUSE_NORMAL);
			}
			break;

		case GAMESTATE_END:	//終了までのカウントダウン
			pGame[0].nCntGameState++;
			if (pGame[0].nCntGameState > 200)
			{
				pGame[0].now = GAMESTATE_NONE;
				SetFade(pGame[0].CHANGE, 0);
			}
			break;
		}
	}
}
//=========================================================================================================//
// * ゲームの描画処理
//=========================================================================================================//
void DrawGame(void)
{
	DrawBlock(false);
	DrawAnimation(ANIMTYPE_COIN);
	DrawEnemy();
	DrawBlock(true);
	DrawExplosion();
	DrawBullet();

	DrawGameWindow();
	DrawAnimation(ANIMTYPE_NONE);
	DrawFont();
	DrawDigital();
	DrawPlayer();
}
//=========================================================================================================//
// * ゲームの状態管理　取得
//=========================================================================================================//
GAME *GetGameState(void)
{
	static GAME game = GAME{ GAMESTATE_NORMAL , MODE_GAME , 0 };	//初回初期化

	return &game;
}
//=========================================================================================================//
// * ゲームの状態管理　set
//=========================================================================================================//
void SetGameState(GAMESTATE game, MODE mode, int nCntGameState)
{
	GAME *pGame;	//現在の状態をポインタで取得

	pGame = GetGameState();

	pGame[0].now = game;
	pGame[0].CHANGE = mode;
	pGame[0].nCntGameState = nCntGameState;
}

