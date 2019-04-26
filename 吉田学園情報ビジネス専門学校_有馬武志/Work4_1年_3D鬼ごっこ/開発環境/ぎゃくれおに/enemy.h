//=============================================================================
//
// 鬼処理 [enemy.h]
// Author : 有馬 武志
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//*****************************************************************************
// 鬼の構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshEnemy = NULL;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatEnemy = NULL;		//マテリアルの情報へのポインタ
	DWORD nNumMatEnemy = 0;					//マテリアルの情報数
	D3DXMATRIX mtxWorldEnemy;				//ワールドマトリックス
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
	D3DXVECTOR3 move;						//動き
	D3DXVECTOR3	posOld;						//過去の位置
	D3DXVECTOR3 vtxMinModel;				//鬼の最小値
	D3DXVECTOR3 vtxMaxModel;				//鬼の最大値
	int nCntPlayer;							//プレイヤー
	bool bUse;								//使用していたら
}Enemy;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
Enemy *GetEnemy(void);

bool CollisionEnemy(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld, D3DXVECTOR3  * pMove);
bool CollisionEnemy2(D3DXVECTOR3 * pPos, D3DXVECTOR3  * pPosOld, D3DXVECTOR3  * pMove);

#endif
