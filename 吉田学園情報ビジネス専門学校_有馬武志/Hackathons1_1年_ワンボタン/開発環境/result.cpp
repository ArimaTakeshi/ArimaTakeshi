//=========================================================================================================//
//
// タイトルの処理 [Title.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS	//Fire Wall突破
#include <stdio.h>				//インクルドファイル セーブロードのため
#include "game.h"
#include "main.h"
#include"input.h"
#include "score.h"
#include "fade.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//


//=========================================================================================================//
// * ゲームの初期化処理
//=========================================================================================================//
void InitResult(void)
{
	SetBGWindow(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), COLLAR{ 255,255,255, 255 }, 0.0f, 1.0f, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 4, WINDOWSTATE_NORMAL);

	InitScore();
	SetScore(D3DXVECTOR3((SCREEN_WIDTH / 2) - 50, 430, 0.0f), D3DXVECTOR3(50.0f, 57.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	SetScore(D3DXVECTOR3((SCREEN_WIDTH / 2) + 410, 120, 0.0f), D3DXVECTOR3(30.0f, 37.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	SetScore(D3DXVECTOR3((SCREEN_WIDTH / 2) + 410, 220, 0.0f), D3DXVECTOR3(30.0f, 37.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	SetScore(D3DXVECTOR3((SCREEN_WIDTH / 2) + 410, 320, 0.0f), D3DXVECTOR3(30.0f, 37.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	SetScore(D3DXVECTOR3((SCREEN_WIDTH / 2) + 410, 420, 0.0f), D3DXVECTOR3(30.0f, 37.0f, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	LoadScore();
	PlaySound(SOUND_LABEL_BGM000);
}
//=========================================================================================================//
// * ゲームの終了処理
//=========================================================================================================//
void UninitResult(void)
{
	UninitScore();
}
//=========================================================================================================//
// * ゲームの更新処理
//=========================================================================================================//
void UpdateResult(void)
{
	//UpdateFont();
	UpdateScore();
	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		SetFade(MODE_TITLE, 0);
	}
}
//=========================================================================================================//
// * ゲームの描画処理
//=========================================================================================================//
void DrawResult(void)
{
	DrawScore();
}
