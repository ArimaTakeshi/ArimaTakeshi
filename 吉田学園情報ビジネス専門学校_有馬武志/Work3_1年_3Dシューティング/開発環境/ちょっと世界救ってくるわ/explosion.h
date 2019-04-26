//=============================================================================
//
// ポリゴン処理 [explosion.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "main.h"

//*****************************************************************************
// 壁の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posExplosion;		//位置
	D3DXVECTOR3		rotExplosion;		//向き
	D3DXMATRIX		mtxWorldExplosion;	//ワールドマトリックス
	int				nCounterAnim;		//アニメーションカウンター
	int				nPatteunAnim;		//アニメーションパターンNo.
	bool			bUse;				//使用してるかどうか
}Explosion;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);

void SetExplosion(D3DXVECTOR3 pos,D3DXVECTOR3 rot);

#endif
