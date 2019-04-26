//=============================================================================
//
// ポリゴン処理 [shadow.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// 影の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		pos;			//位置
	D3DXVECTOR3		rot;			//向き
	D3DXMATRIX		mtxWorld;		//ワールドマトリックス
	float			ShadowWidth;	//幅
	float			ShadowDepth;	//深さ
	bool			bUse;			//使用しているかどうか
}Shadow;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float ShadowWidth, float ShadowDepth);
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,D3DXVECTOR3 rot);
void DeleteShadow(int nIdxShadow);

#endif
