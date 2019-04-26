//=========================================================================================================//
//
// ゲーム処理 [game.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "input.h"
#include "game.h"
#include "enemy.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//=========================================================================================================//
// * ゲームの初期化処理
//=========================================================================================================//
void InitGame(void)
{
	InitPlayer();
	InitFont();
	InitEnemy();
	InitScore();
	InitGameWindow();
	SetGameWindow(D3DXVECTOR3(23, 110, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 30, 30, 0, WINDOWSTATE_NORMAL, WINDOWUSE_NORMAL);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0023f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, WINDOWSTATE_BG);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.95, 0.0f), COLLAR{ 255,255,255, 255 }, 0.006f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 10, 3, WINDOWSTATE_BG);
	char aStr[256];
	// 文字列を代入
	wsprintf(&aStr[0], "0 m");
	SetFont(RECT{ 1200 , 10, 1280, 300 }, D3DXCOLOR{ 1.0f, 1.0f, 1.0 , 1.0f }, &aStr[0], 1, FONTSTATE_NONE);
	SetFont(RECT{ 10, 10, 300, 100 }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 8, FONTSTATE_NONE);
	SetFont(RECT{ 100, 10, 300, 100 }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 4, FONTSTATE_NONE);
	SetFont(RECT{ 10, 50, 300, 150 }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 5, FONTSTATE_NONE);
	SetFont(RECT{ 50, 90, 300, 200 }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 7, FONTSTATE_NONE);
	SetFont(RECT{ 600, 10, 900, 100 }, D3DXCOLOR{ 1.0f,1.0f,1.0f,1.0f }, &aStr[0], 6, FONTSTATE_NONE);

	SetGameState(GAMESTATE_NORMAL, MODE_GAME, 0);
	PlaySound(SOUND_LABEL_FBGM000);
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
	BreakGameWindow();
	BreakBGWindow();
	UninitPlayer();
	UninitFont();
	UninitEnemy();
	LoadScore();
	SaveScore(SCORETYPE_RNKING_NO1);
	UninitScore();
	UninitGameWindow();
	StopSound();
}
//=========================================================================================================//
// * ゲームの更新処理
//=========================================================================================================//
void UpdateGame(void)
{
	GAME *pGame;	//現在の状態をポインタで取得
	static int nNumber;
	char aStr[256];
	PLAYER *pPlayer = GetPlayer();

	pGame = GetGameState();

	switch (pGame[0].now)
	{//ゲーム状態に応じた処理開始
	case GAMESTATE_NONE:
		break;

	case GAMESTATE_NORMAL:
		UpdateBGWindow();
		UpdateFont();
		UpdateEnemy();
		UpdatePlayer();
		UpdateScore();
		if (pPlayer[0].bMove == true)
		{
			// 文字列を代入
			wsprintf(&aStr[0], "%d m", pPlayer[0].nMeter / 10);
			ChangeFont(true, &aStr[0], 1, FONTSTATE_NONE);
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
void DrawGame(void)
{
	DrawPlayer();
	DrawEnemy();
	DrawExplosion();
	DrawEffect();

	DrawGameWindow();
	DrawScore();
	DrawFont();
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
