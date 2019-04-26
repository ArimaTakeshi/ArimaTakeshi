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
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_BGM005,			// BGM5
	SOUND_LABEL_BGM006,			// BGM6
	SOUND_LABEL_BGM007,			// BGM7
	SOUND_LABEL_SE_GETCOIN,		// コインをとる音
	SOUND_LABEL_SE_DOWN000,		// 閉じる
	SOUND_LABEL_SE_OPEN000,		// 開く
	SOUND_LABEL_SE_GETMONEY,	// お金系の音
	SOUND_LABEL_SE_PRESS,		// 押すときの音
	SOUND_LABEL_SE_BREAK,		// 壊すときの音
	SOUND_LABEL_SE_FALL,		// 落ちるとき
	SOUND_LABEL_SE_TIME,		// 時計
	SOUND_LABEL_SE_FOUND,		// 発見
	SOUND_LABEL_SE_DECIDE,		// 決定音
	SOUND_LABEL_SE_JAMP,		// ジャンプ音
	SOUND_LABEL_SE_RECOVERY,	// 回復音
	SOUND_LABEL_SE_RANKING,		//ランキング
	SOUND_LABEL_SE_ITEMBEY,		//アイテム購入
	SOUND_LABEL_SE_MENUUPDOWN,	//メニュー移動
	SOUND_LABEL_SE_ITEMGET,		//アイテムとったら
	SOUND_LABEL_SE_GAMEOVER,	//ゲームオーバー
	SOUND_LABEL_SE_NOT,			//無効
	SOUND_LABEL_MAX,
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
