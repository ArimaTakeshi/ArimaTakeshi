//=========================================================================================================================
//
// 背景の処理 [warning.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _WARNING_H_
#define _WARNING_H_

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitWarning(void);							//ワーニング初期化処理
void UninitWarning(void);						//ワーニング終了処理
void UpdateWarning(void);						//ワーニング更新処理
void DrawWarning(void);							//ワーニング描画処理

void SetWarning(void);							//ワーニングセット
#endif