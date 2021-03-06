
//=========================================================================================================================
//
// ランキングの処理 [ranking.h]
// Author : 有馬　武志
//
//=========================================================================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitRanking(void);							//ランキング初期化処理
void UninitRanking(void);						//ランキング終了処理
void UpdateRanking(void);						//ランキング更新処理
void DrawRanking(void);							//ランキング描画処理

#endif