//=============================================================================
//
// ポリゴン処理 [bullet.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "main.h"

//*****************************************************************************
// 壁の構造体
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3		posBullet;		//位置
	D3DXVECTOR3		moveBullet;		//動き
	D3DXVECTOR3		rotBullet;		//向き
	D3DXMATRIX		mtxWorldBullet;	//ワールドマトリックス
	int				nIdxShadow;		//影の番号
	bool			bUse;			//使用してるかどうか
}Bullet;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move);
Bullet *GetBullet(void);

#endif
