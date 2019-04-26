//=============================================================================
//
// アイテムカウントの表示処理 [itemcount.h]
// Author :  有馬　武志
//
//=============================================================================
#ifndef _ITEMCOUNT_H_
#define _ITEMCOUNT_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitItemCount(void);
void UninitItemCount(void);
void UpdateItemCount(void);
void DrawItemCount(void);

void AddItemCount(int nValue);
int GetItemCount(void);
#endif
