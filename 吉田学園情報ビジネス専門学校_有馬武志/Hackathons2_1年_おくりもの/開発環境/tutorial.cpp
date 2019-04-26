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
bool bPause0;		//Pauseしてるかどうか

//=========================================================================================================//
// * ゲームの初期化処理
//=========================================================================================================//
void InitTutorial(void)
{
	char aStr[8] = "SCORE ";
	InitPlayer();
	InitDigital();
	InitFont();
	InitEnemy();
	InitBlock();
	InitBullet();
	InitExplosion();
	InitAnimation();
	InitGameWindow();
	bPause0 = false;

	SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.85f, SCREEN_HEIGHT * 0.9f, 0.0f), D3DXCOLOR{ 1.0f,0.99f,0.04f, 1.0f }, 150, 30, 0, 0, 0, WINDOWSTATE_FLASH, WINDOWUSE_NORMAL);

	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.87f - 35.0f, 0.0f), D3DXCOLOR(0.3f, 0.0f, 0.0f, 1.0f), 446, 90, 0, 0, WINDOWSTATE_NORMAL, WINDOWUSE_PLAYER);
	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.12f, SCREEN_HEIGHT * 0.87f - 35.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 36, 90, 0, 0, WINDOWSTATE_NORMAL, WINDOWUSE_PLAYER);
	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f - 5.0f, SCREEN_HEIGHT * 0.87f - 5.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 400, 60, 0, 0, WINDOWSTATE_MAXEXPGAGE, WINDOWUSE_PLAYER);
	//SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f - 5.0f, SCREEN_HEIGHT * 0.87f - 5.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 400, 45, 0, 0, WINDOWSTATE_MAXLIFEGAGE, WINDOWUSE_PLAYER);
	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f, 0.0f), D3DXCOLOR(0.8f, 0.1f, 0.02f, 1.0f), 100, 35, 0, 0, WINDOWSTATE_AUTOLIFEGAGE, WINDOWUSE_PLAYER);
	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f, 0.0f), D3DXCOLOR(0.25f, 1.0f, 0.1f, 1.0f), 300, 35, 0, 0, WINDOWSTATE_LIFEGAGE, WINDOWUSE_PLAYER);
	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f + 40.0f, 0.0f), D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f), 400, 10, 0, 0, WINDOWSTATE_EXPGAGE, WINDOWUSE_PLAYER);
	SetGameWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.152f, SCREEN_HEIGHT * 0.87f + 40.0f, 0.0f), D3DXCOLOR(0.4f, 0.98f, 1.0f, 1.0f), 400, 10, 0, 0, WINDOWSTATE_AUTOEXPGAGE, WINDOWUSE_PLAYER);
	SetFont({ 200, 590, SCREEN_WIDTH, 700 }, D3DCOLOR_RGBA(255, 255, 255, 255), &aStr[0], 0, 12, 30, FONTSTATE_NONE);
	//SetFont({ 200, 625, SCREEN_WIDTH, 700 }, D3DCOLOR_RGBA(255, 255, 255, 255), &aStr[0], 1, 12, 30, FONTSTATE_NONE);
	SetGameWindow(D3DXVECTOR3(0.0f, -100.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 400, 400, 1, 0, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL);

	SetAnimation(D3DXVECTOR3(SCREEN_WIDTH * 0.07f, SCREEN_HEIGHT * 0.87f, 0.0f), 130, 80, 11, 1, 9999, 1, 0, ANIMATION_PLAYER, ANIMTYPE_NONE);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.001f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, WINDOWSTATE_SCROLL0);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 100 }, 0.0008f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, WINDOWSTATE_SCROLL0);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 200 }, 0.0012f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1, WINDOWSTATE_SCROLL1);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.35f, 0.0f), COLLAR{ 200,200,200, 255 }, 1.0f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, WINDOWSTATE_BG);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 1.34f, 0.0f), COLLAR{ 200,200,200, 255 }, 1.0f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, WINDOWSTATE_BG);
	SetGameState(GAMESTATE_NORMAL, MODE_GAME, 0);
	SetFont({ SCREEN_WIDTH / 2 - 100, 10, SCREEN_WIDTH, 100 }, D3DCOLOR_RGBA(255, 255, 255, 255), &aStr[0], 2, 12, 30, FONTSTATE_NONE);
	SetFont({ SCREEN_WIDTH - 150, 10, SCREEN_WIDTH, 100 }, D3DCOLOR_RGBA(255, 255, 5, 255), &aStr[0], 3, 12, 30, FONTSTATE_NONE);
	//SetFontDamage({ 0, 10, SCREEN_WIDTH, 100 }, D3DCOLOR_RGBA(255, 255, 5, 255), &aStr[0], 1, FONTSTATE_NONE);
	SetBlock(D3DXVECTOR3(0, FIELD + 3000, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 1000000, 5, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_OUT);

	SetBlock(D3DXVECTOR3(700, FIELD + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 900, 200, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(-1200, FIELD - 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000, 1000, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(5000, FIELD - 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 1000, 1000, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetBlock(D3DXVECTOR3(1450, FIELD - 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 135, 300, 2, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_BG);
	SetBlock(D3DXVECTOR3(1450, FIELD - 590, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 155, 10, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(1450, FIELD - 250, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 135, 5, 1, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN);
	SetBlock(D3DXVECTOR3(1595, FIELD - 30, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 430, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(1305, FIELD - 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 10, 250, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(1450, FIELD - 300, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 135, 300, 0, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_FADE);

	SetBlock(D3DXVECTOR3(1735, FIELD - 455, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 135, 5, 1, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_THIN);
	SetBlock(D3DXVECTOR3(2300, FIELD, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 200, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);
	SetBlock(D3DXVECTOR3(3200, FIELD + 200, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 800, 200, 4, D3DX_PI, 0.0f, D3DX_PI, 0.0f, BLOCKSTATE_NONE);

	SetAnimation((D3DXVECTOR3(800, FIELD - 150, 0.0f)), 10, 20, 4, 1, 5, 0, 0, ANIMATION_LOOP, ANIMTYPE_COIN);
	SetAnimation((D3DXVECTOR3(900, FIELD - 30, 0.0f)), 10, 20, 4, 1, 5, 0, 0, ANIMATION_LOOP, ANIMTYPE_COIN);
	SetAnimation((D3DXVECTOR3(700, FIELD - 30, 0.0f)), 10, 20, 4, 1, 5, 0, 0, ANIMATION_LOOP, ANIMTYPE_COIN);

	SetAnimation((D3DXVECTOR3(2200, FIELD - 230, 0.0f)), 10, 20, 4, 1, 5, 0, 0, ANIMATION_LOOP, ANIMTYPE_COIN);
	SetAnimation((D3DXVECTOR3(2300, FIELD - 230, 0.0f)), 10, 20, 4, 1, 5, 0, 0, ANIMATION_LOOP, ANIMTYPE_COIN);
	SetAnimation((D3DXVECTOR3(2400, FIELD - 230, 0.0f)), 10, 20, 4, 1, 5, 0, 0, ANIMATION_LOOP, ANIMTYPE_COIN);

	//SetEnemy(D3DXVECTOR3(1000, FIELD - 50, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_R_DRAGON, 30, 3000, 100, 100, 150, 10, 1000, ENEMYTYPE_NORMALENEMY);
	SetEnemy(D3DXVECTOR3(3700, FIELD - 50, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_WOLF, 30, 2000, 90, 100, 150, 10, 3000, D3DX_PI, ENEMYTYPE_TITLE);
	SetEnemy(D3DXVECTOR3(3500, FIELD - 50, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_SLIME, 30, 700, 70, 100, 150, 10, 1000, D3DX_PI, ENEMYTYPE_NORMALENEMY);
	SetEnemy(D3DXVECTOR3(800, FIELD - 30, 0.0f), ENEMYTEXTYPE_TRAP, ENEMYTEX_SLIME, 30, 3000, 100, 999, 150, 10, 1000, D3DX_PI, ENEMYTYPE_NORMALENEMY);


	//SetEnemy(D3DXVECTOR3(3600, FIELD - 50, 0.0f), ENEMYTEX_GIANT, 30, 3000, 100, 100, 150, 10, 1000, ENEMYTYPE_NORMALENEMY);
	//SetEnemy(D3DXVECTOR3(3700, FIELD - 50, 0.0f), ENEMYTEX_BAT, 30, 3000, 100, 100, 150, 10, 1000, ENEMYTYPE_NORMALENEMY);
	//SetEnemy(D3DXVECTOR3(1900, FIELD - 550, 0.0f), ENEMYTEXTYPE_ENEMY, ENEMYTEX_BAT, 30, 3000, 100, 100, 150, 10, 1000, ENEMYTYPE_NORMALENEMY);
	InitScroll();

	SettingPlayer();
	PlaySound(SOUND_LABEL_TUTORIAL000);
}
//=========================================================================================================//
// * ゲームの終了処理
//=========================================================================================================//
void UninitTutorial(void)
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
void UpdateTutorial(void)
{
	GAME *pGame;	//現在の状態をポインタで取得
	static int nNumber;
	PLAYER *pPlayer = GetPlayer();

	pGame = GetGameState();

	switch (pGame[0].now)
	{//ゲーム状態に応じた処理開始
	case GAMESTATE_NONE:
		break;

	case GAMESTATE_NORMAL:
		if (bPause0 == false)
		{
			if (pPlayer[0].nTime[0] > 0)
			{
				UpdateBGWindow();
				UpdateFont();
				UpdateEnemy();
				UpdatePlayer();
				UpdateBlock();
				WideScroll();
				UpdateBullet();
				UpdateExplosion();
				UpdateAnimation();
				UpdateGameWindow();
				UpdateDigital();

				if (pPlayer[0].nTime[0] == 30) { SetDigital(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 300, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.1f), DIGITALSTATE_NONE, 300, 400, 3); }
				if (pPlayer[0].nTime[0] == 20) { SetDigital(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 300, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.1f), DIGITALSTATE_NONE, 300, 400, 2); }
				if (pPlayer[0].nTime[0] == 10) { SetDigital(D3DXVECTOR3(SCREEN_WIDTH * 0.5f + 300, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR(1.0f, 0.1f, 0.1f, 0.1f), DIGITALSTATE_NONE, 300, 400, 1); }
			
				if (GetKeyboardTrigger(DIK_RETURN) == true) { SetFade(MODE_TITLE, 0); }
			}
			else
			{//時間切れ
				SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 500, 250, 8, 0, 0, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL);
				SetGameState(GAMESTATE_END, MODE_TITLE, 100);
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
				bPause0 = false;
				if (nNumber == 0)
				{//戻る
					BackWindow(4);
				}
				else if (nNumber == 1)
				{//初めから
					InitPlayer0();
					SetFade(MODE_TUTORIAL, 0);
				}
				else if (nNumber == 2)
				{//Titleへ
					SetFade(MODE_TITLE, 0);		//Titleへ
				}
			}
		}
		if (GetKeyboardTrigger(DIK_P) == true && bPause0 == false)
		{//Pを押したらpause画面
			PlaySound(SOUND_LABEL_BOTTON000);
			BackWindow(1);
			bPause0 = true;
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 4, 0, 0, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL);
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.3f, 0.0f), D3DXCOLOR{ 0.23f,0.23f,0.23f, 1.0f }, 150, 30, 5, 0, 0, WINDOWSTATE_SELECTOFF, WINDOWUSE_SELECT);
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXCOLOR{ 0.23f,0.23f,0.23f, 1.0f }, 150, 30, 6, 1, 0, WINDOWSTATE_SELECTOFF, WINDOWUSE_SELECT);
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.7f, 0.0f), D3DXCOLOR{ 0.23f,0.23f,0.23f, 1.0f }, 150, 30, 7, 2, 0, WINDOWSTATE_SELECTOFF, WINDOWUSE_SELECT);
		}
		else if (GetKeyboardTrigger(DIK_P) == true)
		{//Pを押したらpause解く
			PlaySound(SOUND_LABEL_BOTTON000);
			bPause0 = false;
			BackWindow(4);
			SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.8f, SCREEN_HEIGHT * 0.9f, 0.0f), D3DXCOLOR{ 1.0f,0.99f,0.04f, 0 }, 150, 30, 0, 0, 0, WINDOWSTATE_FLASH, WINDOWUSE_NORMAL);
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
//=========================================================================================================//
// * ゲームの描画処理
//=========================================================================================================//
void DrawTutorial(void)
{
	DrawBlock(false);
	DrawAnimation(ANIMTYPE_COIN);
	DrawEnemy();
	DrawBullet();
	DrawExplosion();
	DrawBlock(true);

	DrawPlayer();
	DrawGameWindow();
	DrawAnimation(ANIMTYPE_NONE);
	DrawFont();
	DrawDigital();
	/*DrawEnemy();
	DrawExplosion();
	DrawEffect();

	DrawGameWindow();
	DrawScore();
	*/
}