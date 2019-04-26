//=========================================================================================================================
//
// タイトルの処理 [title.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

//*************************************************************************************************************************
// 構造体
//*************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動値
	int nCounterAnim;		//アニメーションカウンター
	int nPatteunAnim;		//アニメーションパターンNo.
	int nType;				//種類
}Title;

typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	bool bUse;				//使用しているかどうか
	float EnterWidth;		//幅
	float EnterHeight;		//高さ
}PressEnter;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitTitle(void);							//タイトル初期化処理
void UninitTitle(void);							//タイトル終了処理
void UpdateTitle(void);							//タイトル更新処理
void DrawTitle(void);							//タイトル描画処理

void SetPressEnter(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight);//セットプレスエンター

#endif