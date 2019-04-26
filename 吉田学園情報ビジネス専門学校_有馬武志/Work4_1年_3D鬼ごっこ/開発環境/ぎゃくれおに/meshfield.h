//=============================================================================
//
// メッシュフィールド処理 [meshfield.h]
// Author : 有馬　武志
//
//=============================================================================
#ifndef _MESHFIELD_H_
#define _MESHFIELD_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3		posMeshField;							//位置
	D3DXVECTOR3		rotMeshField;							//向き
	D3DXMATRIX		mtxWorldMeshField;						//ワールドマトリックス
	int				nNumVertexMeshField;					//頂点数
	int				nNumIdxMeshField;						//インデックス数
	int				nNumPolygonMeshField;					//ポリゴン数
}MeshField;
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitMeshField(void);
void UninitMeshField(void);
void UpdateMeshField(void);
void DrawMeshField(void);

#endif
