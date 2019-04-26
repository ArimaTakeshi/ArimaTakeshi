//=============================================================================
//
// サウンド処理 [sound.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*************************************
// サウンドファイル
//*************************************
typedef enum
{
	SOUND_LABEL_COMBATBGM000 = 0,		// 戦争中
	SOUND_LABEL_PLANEBGM001,			// 飛行機中
	SOUND_LABEL_PLANEBGM002,			// タイトル
	SOUND_LABEL_PLANEBGM003,			// ゲーム中
	SOUND_LABEL_SE_SHOOT,				// 撃つ音
	SOUND_LABEL_SE_DOWN000,				// 閉じる
	SOUND_LABEL_SE_OPEN000,				// 開く
	SOUND_LABEL_SE_DECIDE,				// 決定音
	SOUND_LABEL_SE_MENUUPDOWN,			// メニュー移動
	SOUND_LABEL_SE_HERI,				// メニュー移動
	SOUND_LABEL_MAX						// サウンドの最大数
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label); //ゲームの初期化近く　
void StopSound(SOUND_LABEL label);	  //同じ名前を書いてストップさせっる
void StopSound(void);

#endif
