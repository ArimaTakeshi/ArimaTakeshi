//=============================================================================
//
// スコア処理 [score.h]
// Author :  有馬　武志
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"

//*************************************************************************************************************************
// ブロックの構造体
//*************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//カラー
	int nNumScore;			//箱
	float ScoreWidth;		//幅
	float ScoreHeight;		//高さ
	bool bUse;				//使用しているかどうか
}Score;

typedef enum
{
	SCORE_NONE = 0,
	SCORE_MENIYBOX,
	SCORE_RAKING,
	SCORE_COIN,
	SCORE_SHOP,
	SCORE_TIMER,
	SCORE_MAX				//最大数
}SCORESTATE;

typedef enum
{
	GETCOIN_NORMAL = 0,
	GETCOIN_X2
}GETCOINSTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue, SCORESTATE state);
void SetCoinState(GETCOINSTATE state);
void SetScore(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
Score *GetScore(void);

#endif
