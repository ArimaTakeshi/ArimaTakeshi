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
	D3DXVECTOR3		pos;			//位置
	D3DXCOLOR		col;			//カラー
	int				nNumScore;		//箱
	float			ScoreWidth;		//幅
	float			ScoreHeight;	//高さ
	bool			bUse;			//使用しているかどうか
}Score;

typedef enum
{
	SCORE_NONE = 0,			//何もない状態
	SCORE_RAKING,			//ランキングで出すスコア
	SCORE_KILL,				//ゲーム内のKILLカウントスコア
	SCORE_MAX				//最大数
}SCORESTATE;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitScore(void);
void UninitScore(void);
void UpdateScore(void);
void DrawScore(void);

void AddScore(int nValue, SCORESTATE state);
void SetScore(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);
Score *GetScore(void);

#endif
