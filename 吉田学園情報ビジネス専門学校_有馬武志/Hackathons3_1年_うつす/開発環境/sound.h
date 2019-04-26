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
	SOUND_LABEL_BGM000 = 0,		// タイトル
	SOUND_LABEL_BGM001,			// ゲーム
	SOUND_LABEL_BGM002,			// リザルト
	SOUND_LABEL_BGM003,			// ゲームオーバー
	SOUND_LABEL_SE_KARSOL,		// カーソル
	SOUND_LABEL_SE_PBUTTUN,		// Pボタン
	SOUND_LABEL_SE_ENTER,		// 決定音
	SOUND_LABEL_SE_START,		// ゲーム開始時
	SOUND_LABEL_SE_TAKESHOT,	// シャッター音
	SOUND_LABEL_SE_HART,		// 心臓音
	SOUND_LABEL_NEAR,			// 接近時
	SOUND_LABEL_DETH,			// プレイヤーの死亡音
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
