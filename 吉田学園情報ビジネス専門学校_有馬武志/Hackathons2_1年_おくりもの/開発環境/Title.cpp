//=========================================================================================================//
//
// タイトルの処理 [Title.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "game.h"
#include "main.h"
#include"input.h"
#include "fade.h"
#include "sound.h"
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
int g_nCntTime;

//=========================================================================================================//
// * Titleの初期化処理
//=========================================================================================================//
void InitTitle(void)
{
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5, 0.0f), COLLAR{ 200,200,200, 255 }, 1.0f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, WINDOWSTATE_BG);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.001f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 2, WINDOWSTATE_SCROLL1);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0008f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, WINDOWSTATE_SCROLL1);
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0006f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3, WINDOWSTATE_SCROLL0);

	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 4, WINDOWSTATE_NORMAL);
	SetWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.85f, 0.0f), D3DXCOLOR{ 1.0f,1.0f,1.0f, 1.0f }, 150, 30, 0, 0, 0, WINDOWSTATE_FLASH, WINDOWUSE_NORMAL);
	g_nCntTime = 0;
	InitPlayer0();
	StopSound();
	PlaySound(SOUND_LABEL_TITLE000);
}
//=========================================================================================================//
// * Titleの終了処理
//=========================================================================================================//
void UninitTitle(void)
{
	BreakWindow();
	BreakBGWindow();
	StopSound();
}
//=========================================================================================================//
// * Titleの更新処理
//=========================================================================================================//
void UpdateTitle(void)
{
	static int nNumber = 0;
	UpdateBGWindow();

	g_nCntTime++;
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetKeyboardTrigger(DIK_Z) == true)
	{
		PlaySound(SOUND_LABEL_BOTTON000);
		InitGame0();
		SetFade(MODE_GAME, 2);
		g_nCntTime = 128;
	}
}
//=========================================================================================================//
// * Titleの描画処理
//=========================================================================================================//
void DrawTitle(void)
{
	DrawFont();
}