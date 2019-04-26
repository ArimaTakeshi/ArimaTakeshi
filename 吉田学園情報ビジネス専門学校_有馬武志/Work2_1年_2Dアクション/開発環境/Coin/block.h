//=========================================================================================================================
//
// ブロックの処理 [block.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define	MAX_BLOCK					(300)								//ブロックの最大数

//*************************************************************************************************************************
// ブロックの構造体
//*************************************************************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posold;		//過去の位置
	D3DXVECTOR3 move;		//移動値
	D3DXCOLOR col;			//カラー
	int Rmove;				//右移動
	int Lmove;				//左移動
	float BlockWidth;		//幅
	float BlockHeight;		//高さ
	int nType;				//種類
	bool bUse;				//使用しているかどうか
}Block;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitBlock(void);																	//ブロック初期化処理
void UninitBlock(void);																	//ブロック終了処理
void UpdateBlock(void);																	//ブロック更新処理
void DrawBlock(void);																	//ブロック描画処理
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove ,float *fWidth , float *fHeight);		//ブロックの移動量
void SetBlock(D3DXVECTOR3 pos, D3DXCOLOR col, int nType ,float fHeight ,float fWidth);									//ブロックの設定処理
void DeleteBlock(void);																	//

#endif