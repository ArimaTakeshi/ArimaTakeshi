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
	SOUND_LABEL_TITLE000 = 0,	// taitol0
	SOUND_LABEL_TUTORIAL000,	// TUTORIAL
	SOUND_LABEL_RESULT000,	// TUTORIAL

	SOUND_LABEL_FBGM000,		// FIELDBGM0
	SOUND_LABEL_FBGM001,		// FIELDBGM0
	SOUND_LABEL_FBGM002,		// FIELDBGM0
	SOUND_LABEL_TIME000,		// 60秒を切る

	SOUND_LABEL_BOTTON000,		//決定音
	SOUND_LABEL_BOTTON001,		//カーソル移動音
	SOUND_LABEL_ATTACK000,		//空中攻撃開始時
	SOUND_LABEL_ATTACK001,		//攻撃時
	SOUND_LABEL_ATTACK002,		//攻撃合図
	SOUND_LABEL_ATTACK003,		//攻撃ヒット
	SOUND_LABEL_ATTACK004,		//攻撃爆発
	SOUND_LABEL_JUMP000,		//ジャンプ
	SOUND_LABEL_DEATH,			//死亡時
	SOUND_LABEL_Damage000,		//被ダメ
	SOUND_LABEL_Damage001,		//被ダメ
	SOUND_LABEL_Damage002,		//被ダメ
	SOUND_LABEL_LEVELUP,		//レベルアップ
	SOUND_LABEL_COIN,			//コイン
	SOUND_LABEL_CHECKPOINT,		//チェックポイント
	SOUND_LABEL_HEEL,			//回復

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
