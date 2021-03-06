//=========================================================================================================================
//
// ゲーム画面の処理の処理 [game.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _PLAYTUTORIAL_H_
#define _PLAYTUTORIAL_H_

#include "main.h"
//*************************************************************************************************************************
// 構造体
//*************************************************************************************************************************
typedef enum
{
	PLAYTUTORIALSTATE_NONE = 0,		//何もしていないじょゆたい
	PLAYTUTORIALSTATE_NORMAL,		//通常状態
	PLAYTUTORIALSTATE_CLEAR,
	PLAYTUTORIALESTATE_OVER,
	PLAYTUTORIALESTATE_MAX
}PLAYTUTORIALSTATE;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitPlayTutorial(void);							//タイトル初期化処理
void UninitPlayTutorial(void);							//タイトル終了処理
void UpdatePlayTutorial(void);							//タイトル更新処理
void DrawPlayTutorial(void);							//タイトル描画処理

#endif