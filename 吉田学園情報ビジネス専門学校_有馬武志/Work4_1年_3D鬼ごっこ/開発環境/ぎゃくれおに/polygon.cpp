//=============================================================================
//
// ポリゴン処理 [polygon.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "polygon.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define POLYGON_TEXTURE_NAME		"data\\TEXTURE\\green.jpg"		//読み込むテクスチャファイル

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon = NULL;	//頂点バッファ
LPDIRECT3DTEXTURE9		g_pTexturePolygon = NULL;	//テクスチャへのポインタ
D3DXVECTOR3				g_posPolygon;				//位置
D3DXVECTOR3				g_rotPolygon;				//向き
D3DXMATRIX				g_mtxWorldPolygon;			//ワールドマトリックス

//=============================================================================
// 初期化処理
//=============================================================================
void InitPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		POLYGON_TEXTURE_NAME,
		&g_pTexturePolygon
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;		

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffPolygon->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(-100, 0, 100);
	pVtx[1].pos = D3DXVECTOR3(100, 0, 100);
	pVtx[2].pos = D3DXVECTOR3(-100, 0, -100);
	pVtx[3].pos = D3DXVECTOR3(100, 0, -100);
	//法線ベクトル
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//頂点カラー
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファのアンロックする
	g_pVtxBuffPolygon->Unlock();		
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitPolygon(void)
{
	//テクスチャーの破棄
	if (g_pTexturePolygon != NULL)
	{
		g_pTexturePolygon->Release();
		g_pTexturePolygon = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffPolygon != NULL)
	{
		g_pVtxBuffPolygon->Release();
		g_pVtxBuffPolygon = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePolygon(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPolygon(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&g_mtxWorldPolygon);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_rotPolygon.y, g_rotPolygon.x, g_rotPolygon.z);

	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, g_posPolygon.x, g_posPolygon.y, g_posPolygon.z);

	D3DXMatrixMultiply(&g_mtxWorldPolygon, &g_mtxWorldPolygon, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldPolygon);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePolygon);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexPolygon(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成


	// 頂点情報の設定

}

