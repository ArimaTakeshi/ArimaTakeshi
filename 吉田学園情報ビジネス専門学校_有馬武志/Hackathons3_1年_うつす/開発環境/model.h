//=============================================================================
//
// モデル処理 [model.h]
// Author : 
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// モデルの構造体
//*****************************************************************************
typedef struct
{
	LPD3DXMESH pMeshModel = NULL;			//メッシュ情報へのポインタ
	LPD3DXBUFFER pBuffMatModel = NULL;		//マテリアルの情報へのポインタ
	DWORD nNumMatModel = 0;					//マテリアルの情報数
	D3DXMATRIX mtxWorldModel;				//ワールドマトリックス
	D3DXVECTOR3 pos;						//位置
	D3DXVECTOR3 rot;						//向き
}Model;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitModel(void);
void UninitModel(void);
void UpdateModel(void);
void DrawModel(void);
Model *GetModel(void);

#endif
