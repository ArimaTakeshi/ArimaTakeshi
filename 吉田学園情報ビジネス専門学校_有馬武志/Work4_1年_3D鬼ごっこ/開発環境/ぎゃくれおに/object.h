//=============================================================================
//
// モデル処理 [object.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH		pMeshObject = NULL;			//メッシュ情報へのポインタ
	LPD3DXBUFFER	pBuffMatObject = NULL;		//マテリアルの情報へのポインタ
	DWORD			nNumMatObject = 0;			//マテリアルの情報数
	D3DXMATRIX		mtxWorldObject;				//ワールドマトリックス
	D3DXVECTOR3		pos;						//位置
	D3DXVECTOR3		rot;						//向き
	bool			bUse;						//種類
	D3DXVECTOR3		VtxMinObject, VtxMaxObject;	//モデルの最小値・最大値
	LPDIRECT3DTEXTURE9* pMeshTextures = NULL;
}Object;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitObject(void);
void UninitObject(void);
void UpdateObject(void);
void DrawObject(void);
Object *GetObject(void);

bool CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove);
void SetObject(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

#endif
