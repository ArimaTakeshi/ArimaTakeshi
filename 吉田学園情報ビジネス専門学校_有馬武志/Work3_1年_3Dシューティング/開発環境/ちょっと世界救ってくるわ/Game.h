//============================================================================
//
// ゲームの処理 [game.h]
// Author : 有馬　武志
//
//============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"
//*****************************************************************************
// 構造体
//*****************************************************************************
typedef enum
{
	GAMESTATE_NONE = 0,		//何もしていない状態
	GAMESTATE_NORMAL,		//通常状態
	GAMESTATE_CLEAR,		//クリア
	GAMESTATE_OVER,			//ゲームオーバー
	GAMESTATE_END,
	GAMESTATE_MAX			//最大数
}GAMESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitGame(void);							//タイトル初期化処理
void UninitGame(void);							//タイトル終了処理
void UpdateGame(void);							//タイトル更新処理
void DrawGame(void);							//タイトル描画処理
void SetGameState(GAMESTATE state);
GAMESTATE GetGameState(void);
void SetPauseState(bool bPause);

#endif