//=========================================================================================================================
// 
// スコア処理 [score.h]
// Author : Eisuke Sakagawa
// 
//=========================================================================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// 構造体定義
//*************************************************************************************************************************
typedef enum
{// 種類
	SCORETYPE_RNKING_NO1 = 0,	// ランキングNo1
	SCORETYPE_RNKING_NO2,		// ランキングNo2
	SCORETYPE_RNKING_NO3,		// ランキングNo3
	SCORETYPE_RNKING_NO4,		// ランキングNo4
	SCORETYPE_RNKING_NO5,		// ランキングNo5
}SCORETYPE;

typedef struct
{// スコア
	int nScore;					// スコア
	D3DXVECTOR3 pos;			// 位置
	D3DXVECTOR3 posmove;		// 移動
	D3DXVECTOR3 nRadius;		// 大きさ（半径）
	D3DXCOLOR col;				// 色
	bool bUse;					// 使用しているかどうか
}Score;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitScore(void);			// スコア初期化処理
void UninitScore(void);			// スコア終了処理
void UpdateScore(void);			// スコア更新処理
void DrawScore(void);			// スコア描画

void SetScore(D3DXVECTOR3 pos, D3DXVECTOR3 nRadius, D3DXCOLOR col);		// スコア設定処理
Score GetScore(void);							// スコア取得処理
void AddScore(SCORETYPE Type, int nValue);		// スコア加算処理
void SaveScore(SCORETYPE Type);					// スコアセーブ処理
void LoadScore(void);							// スコアロード処理

#endif