//=============================================================================
//
// ポリゴン処理 [billboord.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _BILLBOORD_H_
#define _BILLBOORD_H_

#include "main.h"

//*****************************************************************************
// 壁の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posBillBoord;		//位置
	D3DXVECTOR3		rotBillBoord;		//向き
	D3DXMATRIX		mtxWorldBillBoord;	//ワールドマトリックス
	int				nType;				//種類
	int				nCounterAnim;		//アニメーションカウンター
	int				nPatteunAnim;		//アニメーションパターンNo.
	int				nIdxShadow;
	bool			bUse;				//使用してるかどうか
}BillBoord;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBillBoord(void);
void UninitBillBoord(void);
void UpdateBillBoord(void);
void DrawBillBoord(void);

void SetBillBoord(D3DXVECTOR3 pos,D3DXVECTOR3 rot, int nType);
void DeleteBillBoord(int nCntBillBoord);
void CollisionBillBoord(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pMove);

#endif
