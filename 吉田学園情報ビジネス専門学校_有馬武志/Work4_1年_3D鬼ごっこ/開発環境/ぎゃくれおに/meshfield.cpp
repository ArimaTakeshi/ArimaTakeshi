//=============================================================================
//
// ポリゴン処理 [meshfield.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "meshfield.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MESHFIELD_TEXTURE_NAME		"data\\TEXTURE\\konku.png"							//読み込むテクスチャファイル
#define BULOCK_Z					(2500.0f)											//ブロックの横行
#define BULOCK_X					(2500.0f)											//ブロックの奥行
#define VERTICAL					(5)													//縦
#define CORSS						(5)													//横
#define VERTEX						((VERTICAL + 1) * (CORSS + 1))						//指定した縦と横+１の値
#define IDX							((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4 + 2)	//インデックスの式
#define POLYGON						((VERTICAL * CORSS) * 2 + (VERTICAL - 1) * 4)		//ポリゴン数の式

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMeshField = NULL; //頂点バッファ
LPDIRECT3DTEXTURE9		g_pTextureMeshField = NULL;	//テクスチャへのポインタ
LPDIRECT3DINDEXBUFFER9 g_pIdxBuffMeshField = NULL;	//インデックスバッファのポインタ
MeshField g_MeshField;

//=============================================================================
// 初期化処理
//=============================================================================
void InitMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//変数宣言
	int nCntCorss;						//横のカウント
	int nCntVertical;					//縦のカウント
	int nCntIdx;						//インデックスの頂点情報

	g_MeshField.nNumVertexMeshField = VERTEX;		//頂点数
	g_MeshField.nNumIdxMeshField = IDX;				//インデックス数
	g_MeshField.nNumPolygonMeshField = POLYGON;		//ポリゴン数


	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		MESHFIELD_TEXTURE_NAME,
		&g_pTextureMeshField
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * g_MeshField.nNumVertexMeshField,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMeshField,
		NULL
	);

	//インデックスバッファの生成
	pDevice->CreateIndexBuffer
	(
		sizeof(WORD) * g_MeshField.nNumIdxMeshField,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&g_pIdxBuffMeshField,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//インデックスデータへのポインタ
	WORD * pIdx;

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffMeshField->Lock(0, 0, (void**)&pVtx, 0);

	//旧頂点情報
#if 0
	////頂点情報
	//pVtx[0].pos = D3DXVECTOR3(-100.0f, 0.0f, 100.0f);
	//pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 100.0f);
	//pVtx[2].pos = D3DXVECTOR3(100.0f, 0.0f, 100.0f);
	//pVtx[3].pos = D3DXVECTOR3(-100.0f, 0.0f, 0.0f);
	//pVtx[4].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(-100.0f, 0.0f, -100.0f);
	//pVtx[7].pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	//pVtx[8].pos = D3DXVECTOR3(100.0f, 0.0f, -100.0f);
	
	////頂点のインデックス情報
	//pIdx[0] = 3;
	//pIdx[1] = 0;
	//pIdx[2] = 4;
	//pIdx[3] = 1;
	//pIdx[4] = 5;
	//pIdx[5] = 2;
	//pIdx[6] = 2;
	//pIdx[7] = 6;
	//pIdx[8] = 6;
	//pIdx[9] = 3;
	//pIdx[10] = 7;
	//pIdx[11] = 4;
	//pIdx[12] = 8;
	//pIdx[13] = 5;
#endif

	//頂点、法線、カラー、テクスチャの頂点設定
	for (nCntVertical = 0; nCntVertical <= VERTICAL; nCntVertical++)
	{//縦軸
		for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++)
		{//横軸
			//頂点座標
			pVtx[0].pos = D3DXVECTOR3(-BULOCK_X * 2 + (BULOCK_X * nCntCorss)*1.0f, 0.0f, BULOCK_Z * 2 - (BULOCK_Z * nCntVertical)*1.0f);

			//法線
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//テクスチャ
			pVtx[0].tex = D3DXVECTOR2(nCntCorss*1.0f, nCntVertical*1.0f);

			//ずらし
			pVtx += 1;
		}
	}

	//頂点バッファのアンロックする
	g_pVtxBuffMeshField->Unlock();

	//旧頂点情報
#if 0
	//for (nCntVertical = 0; nCntVertical < VERTICAL; nCntVertical++)
	//{//縦軸
	//	for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++)
	//	{//横軸
	//	    //pVtx[たてのカウント数　* (横のブロック数 * ポリゴン数) 折り返し分【+ カウント数 * ポリゴン数】+ 横のカウント * ポリゴン数 + 頂点番号]
	//		//                                                   .pos = D3DXVECTOR3(横カウント * ブロックの幅,Y軸は０,縦のカウント * ブロックの高さ - ブロックの高さ)
	//		//                                                   .pos = D3DXVECTOR3(横カウント * ブロックの幅,Y軸は０,縦のカウント * ブロックの高さ)
	//		pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2].pos = D3DXVECTOR3(nCntCorss * BULOCK_X, 0.0f,nCntVertical * BULOCK_Z - BULOCK_Z);	//0
	//		pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2 + 1].pos = D3DXVECTOR3(nCntCorss * BULOCK_X, 0, nCntVertical * BULOCK_Z);			//1


	//		//最後の頂点に行ったら
	//		//横のカウントがブロック数-1に行った場合と縦が空白の場所を-1して縦のブロック数が足りなくない場合
	//		if (nCntCorss == CORSS - 1 && nCntVertical - 1 != VERTICAL)
	//		{
	//			//pVtx[たてのカウント数　* (横のブロック数 * ポリゴン数) 折り返し分【+ カウント数 * ポリゴン数】+ 横のカウント * ポリゴン数 + 頂点番号]
	//			//                                                       .pos = D3DXVECTOR3(横カウント * ブロックの幅,Y軸は０,縦のカウント * ブロックの高さ - ブロックの高さ)
	//			//                                                       .pos = D3DXVECTOR3(X軸は動かないから０,Y軸は０,縦のカウント * ブロックの高さ + ブロックの高さ)
	//			pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2 + 2].pos = D3DXVECTOR3(nCntCorss * BULOCK_X, 0, nCntCorss * BULOCK_Z);	//2
	//			pVtx[nCntVertical * (CORSS * 2) + nCntVertical * 2 + nCntCorss * 2 + 3].pos = D3DXVECTOR3(0, 0, nCntVertical * BULOCK_Z + BULOCK_Z);				//3
	//		}	
	//	}
	//}

	//for (nCntNorCol = 0; nCntNorCol < g_nNumVertexMeshField; nCntNorCol++)
	//{//法線ベクトルと頂点カラーのfor文
	//	//法線ベクトル
	//	pVtx[nCntNorCol].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//	//頂点カラー
	//	pVtx[nCntNorCol].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//}
	////テクスチャ設定
	////                         X     Z
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);
	//pVtx[4].tex = D3DXVECTOR2(1.0f, 0.5f);
	//pVtx[5].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(1.0f, 0.0f);
	//pVtx[7].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[8].tex = D3DXVECTOR2(0.0f, 1.0f);
	//pVtx[9].tex = D3DXVECTOR2(0.0f, 0.5f);
	//pVtx[10].tex = D3DXVECTOR2(0.5f, 1.0f);
	//pVtx[11].tex = D3DXVECTOR2(0.5f, 0.5f);
	//pVtx[12].tex = D3DXVECTOR2(1.0f, 1.0f);
	//pVtx[13].tex = D3DXVECTOR2(1.0f, 0.5f);
#endif

	//インデックスバッファのロックし、インデックスデータへのポインタを取得
	g_pIdxBuffMeshField->Lock(0, 0, (void**)&pIdx, 0);

	//インデックスの式
	for (nCntVertical = 0, nCntIdx = 0; nCntVertical < VERTICAL; nCntVertical++)
	{//縦軸カウント
		for (nCntCorss = 0; nCntCorss < CORSS + 1; nCntCorss++, nCntIdx++)
		{//横軸カウント
			//pIdx[番号] = (指定した横 + １（この１は０からスタートした時に１足りないから） + インデックスの回数)
			pIdx[0] = (CORSS + 1) + nCntIdx;
			//
			pIdx[1] = 0 + nCntIdx;

			//２頂点ずらし
			pIdx += 2;

			if (nCntVertical < VERTICAL - 1 && nCntCorss == CORSS)
			{
				pIdx[0] = 0 + nCntIdx;
				pIdx[1] = (CORSS + 1) + nCntIdx + 1;

				//２頂点文ずらす
				pIdx += 2;
			}
		}
	}

	//インデックスのバッファのアンロック
	g_pIdxBuffMeshField->Unlock();

	//初期値
	g_MeshField.posMeshField = D3DXVECTOR3(-300.0f, 0.0f, 300.0f);
	g_MeshField.rotMeshField = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	//テクスチャーの破棄
	if (g_pTextureMeshField != NULL)
	{
		g_pTextureMeshField->Release();
		g_pTextureMeshField = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffMeshField != NULL)
	{
		g_pVtxBuffMeshField->Release();
		g_pVtxBuffMeshField = NULL;
	}
	//インデックスバッファの解放
	if (g_pIdxBuffMeshField != NULL)
	{
		g_pIdxBuffMeshField-> Release();
		g_pIdxBuffMeshField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_MeshField.mtxWorldMeshField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_MeshField.rotMeshField.y, g_MeshField.rotMeshField.x, g_MeshField.rotMeshField.z);

	D3DXMatrixMultiply(&g_MeshField.mtxWorldMeshField, &g_MeshField.mtxWorldMeshField, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_MeshField.posMeshField.x, g_MeshField.posMeshField.y, g_MeshField.posMeshField.z);

	D3DXMatrixMultiply(&g_MeshField.mtxWorldMeshField, &g_MeshField.mtxWorldMeshField, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_MeshField.mtxWorldMeshField);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMeshField, 0, sizeof(VERTEX_3D));

	//インデックスバッファデータストリームに設定
	pDevice->SetIndices(g_pIdxBuffMeshField);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	
	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureMeshField);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0,0 , g_MeshField.nNumVertexMeshField,0, g_MeshField.nNumPolygonMeshField);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexMeshField(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

