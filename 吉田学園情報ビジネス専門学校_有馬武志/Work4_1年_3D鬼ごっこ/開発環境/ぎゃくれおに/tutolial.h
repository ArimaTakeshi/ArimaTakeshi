//=========================================================================================================================
//
// 背景の処理 [tutolial.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _TUTOLIAL_H_
#define _TUTOLIAL_H_

#include "main.h"

//*************************************************************************************************************************
//　チュートリアルの構造体
//*************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;  //　位置
	D3DXVECTOR3 move; //　移動値
}Tutorial;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitTutolial(void);							//タイトル初期化処理
void UninitTutolial(void);							//タイトル終了処理
void UpdateTutolial(void);							//タイトル更新処理
void DrawTutolial(void);							//タイトル描画処理

#endif