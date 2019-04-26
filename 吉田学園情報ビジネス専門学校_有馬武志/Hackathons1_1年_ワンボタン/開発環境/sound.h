//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
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
	SOUND_LABEL_RANKING000,		// RANKING
	SOUND_LABEL_FBGM000,		// FIELDBGM0

	SOUND_LABEL_BOTTON000,		//決定音 && チャージ音
	SOUND_LABEL_BOTTON001,		//攻撃
	SOUND_LABEL_BOTTON002,		//ジャンプ
	SOUND_LABEL_BOTTON003,		//ジャンプ

	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
