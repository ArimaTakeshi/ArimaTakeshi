//=============================================================================
//
// アイテムの処理　[item.h]
// Author: 有馬　武志
//
//=============================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

//*****************************************************************************
//　インクルードファイル
//*****************************************************************************
#include "main.h"
#include "player.h"
#include "score.h"
#include "fade.h"
#include "sound.h"
#include "shadow.h"

//*****************************************************************************
//　アイテムの構造体
//*****************************************************************************
typedef enum
{
	ITEM_GASOLINE = 0,		//柊
	ITEM_MAX				//アイテムの最大数
}ITEMSTATE;

typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 rot;		//現在の回転(向き)
	float		fWidth;		//幅
	float		fHeight;	//高さ
	D3DXMATRIX  mtxWorld;	//ワールドマトリックス
	bool		bUse;		//使用しているかどうか
	ITEMSTATE	state;		//アイテムの状態(種類)
	int			nIdxShadow;	//影の番号
}Item;

//*****************************************************************************
//　プロトタイプ宣言
//*****************************************************************************
void InitItem(void);
void UninitItem(void);
void UpdateItem(void);
void DrawItem(void);
void SetItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, ITEMSTATE state, int nItemPossession);
Item *GetItem(void);
int *GetItemPossession(void);

#endif