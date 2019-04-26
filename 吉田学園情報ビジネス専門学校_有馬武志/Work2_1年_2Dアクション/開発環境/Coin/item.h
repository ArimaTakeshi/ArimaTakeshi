//=========================================================================================================================
//
// アイテム処理 [item.h]
// Author :  有馬　武志
//
//=========================================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"

//*************************************************************************************************************************
// 構造体定義
//*************************************************************************************************************************
typedef enum
{//アイテム
	ITEM_COIN = 0,			//コイン
	ITEM_MAGNET,			//磁石
	ITEM_MAX				//最大数
} ITEMTYPE;

typedef enum
{//アイテム
	ITEM_STATE_APPER = 0,
	ITEM_STATE_NORMAL,
	ITEM_STATE_DELETE,
	ITEM_STATE_MAX
}ITEMSTATE;

typedef struct
{//アイテム
	D3DXVECTOR3 pos;		//位置
	D3DXCOLOR col;			//色
	float fHeight;			//高さ
	float fWidth;			//幅
	float fAngle;			//角度
	float fLength;			//長さ
	int nCounterAnim;		//アニメーションカウンター
	int nPatteunAnim;		//アニメーションパターンNo.
	ITEMTYPE ItemType;		//アイテムの種類
	ITEMSTATE ItemState;	//アイテム
	int	nType;				//種類
	bool bUse;				//使用しているかどうか
}Item;

//*************************************************************************************************************************
// プロトタイプ宣言
//*************************************************************************************************************************
void InitItem(void);									//アイテム初期化処理
void UninitItem(void);									//アイテム終了処理
void UpdateItem(void);									//アイテム更新処理
void DrawItem(void);									//アイテム描画処理
void SetItem(D3DXVECTOR3 pos, D3DXCOLOR col ,int nType);//アイテムの設定処理
void CollisionItem(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float *fWidth, float *fHeight);
void DeleteItem(int nCntItem);							//アイテムを消す
void DeleteItem(void);
#endif
