//=============================================================================
//
// ポリゴン処理 [shadow.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SHADOW_TEXTURE_NAME		"data\\TEXTURE\\shadow000.jpg"		//読み込むテクスチャファイル
#define MAX_SHADOW				(1000)								//影の最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffShadow = NULL; //頂点バッファ
LPDIRECT3DTEXTURE9		g_pTextureShadow = NULL; //テクスチャへのポインタ
Shadow g_Shadow[MAX_SHADOW];					 //影の情報		

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得

	//影の数を数えるカウント
	int nCntShadow;

	//影の情報の初期化
	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//影をカウント
		g_Shadow[nCntShadow].pos = D3DXVECTOR3(0, 0, 0);//位置
		g_Shadow[nCntShadow].rot = D3DXVECTOR3(0, 0, 0);//向き
		g_Shadow[nCntShadow].ShadowDepth = 0;			//深さ
		g_Shadow[nCntShadow].ShadowWidth = 0;			//横幅
		g_Shadow[nCntShadow].bUse = false;				//使用しているかどうか
	}

	//頂点情報
	MakeVertexShadow(pDevice);
}
//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	//テクスチャーの破棄
	if (g_pTextureShadow != NULL)
	{
		g_pTextureShadow->Release();
		g_pTextureShadow = NULL;
	}
	// 頂点バッファの開放
	if (g_pVtxBuffShadow != NULL)
	{
		g_pVtxBuffShadow->Release();
		g_pVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	// デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;				//計算用マトリックス

	//減算合成の設定
	pDevice->SetRenderState
	(
		D3DRS_BLENDOP,
		D3DBLENDOP_REVSUBTRACT
	);
	pDevice->SetRenderState
	(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	pDevice->SetRenderState
	(
		D3DRS_DESTBLEND,
		D3DBLEND_ONE
	);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		if (g_Shadow[nCntShadow].bUse == true)
		{//影がある場合
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&g_Shadow[nCntShadow].mtxWorld);

			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_Shadow[nCntShadow].rot.y, g_Shadow[nCntShadow].rot.x, g_Shadow[nCntShadow].rot.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxRot);

			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, g_Shadow[nCntShadow].pos.x, g_Shadow[nCntShadow].pos.y, g_Shadow[nCntShadow].pos.z);

			D3DXMatrixMultiply(&g_Shadow[nCntShadow].mtxWorld, &g_Shadow[nCntShadow].mtxWorld, &mtxTrans);

			// ワールドマトリックスの設定
			pDevice->SetTransform(D3DTS_WORLD, &g_Shadow[nCntShadow].mtxWorld);

			// 頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			pDevice->SetFVF(FVF_VERTEX_3D);


			// テクスチャの設定
			pDevice->SetTexture(0, g_pTextureShadow);


			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntShadow * 4, 2);


			//テクスチャをNULLにして反映されないようにする
			pDevice->SetTexture(0, NULL);

		}
	}
	//元の設定に戻す
	pDevice->SetRenderState
	(
		D3DRS_BLENDOP,
		D3DBLENDOP_ADD
	);
	pDevice->SetRenderState
	(
		D3DRS_SRCBLEND,
		D3DBLEND_SRCALPHA
	);
	pDevice->SetRenderState
	(
		D3DRS_DESTBLEND,
		D3DBLEND_INVSRCALPHA
	);

}
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexShadow(LPDIRECT3DDEVICE9 pDevice)
{
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		SHADOW_TEXTURE_NAME,
		&g_pTextureShadow
	);

	// 頂点情報の作成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_SHADOW,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffShadow,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点バッファをロックし頂点データへのポインタを取得
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[3].pos = D3DXVECTOR3(0, 0, 0);
		//法線ベクトル
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;	//頂点データのポインタを４つ分進める
	}
	//頂点バッファのアンロックする
	g_pVtxBuffShadow->Unlock();

}
//=============================================================================
// 影の情報の作成
//=============================================================================
int SetShadow(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float ShadowWidth,float ShadowDepth)
{
	//影の数を数えるカウント
	int nCntShadow;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;			

	//頂点バッファをロック
	g_pVtxBuffShadow->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntShadow = 0; nCntShadow < MAX_SHADOW; nCntShadow++)
	{//影をカウント
		if (g_Shadow[nCntShadow].bUse == false)
		{//影が使用されていない
			g_Shadow[nCntShadow].pos = pos;					//pos値代入
			g_Shadow[nCntShadow].rot = rot;					//move値代入
			g_Shadow[nCntShadow].ShadowDepth = ShadowDepth;	//深さ
			g_Shadow[nCntShadow].ShadowWidth = ShadowWidth;	//横幅
			g_Shadow[nCntShadow].bUse = true;				//使用している状態にする

			//頂点設定
			pVtx[nCntShadow * 4].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].ShadowWidth, 0.0f, g_Shadow[nCntShadow].ShadowDepth);
			pVtx[nCntShadow * 4 + 1].pos = D3DXVECTOR3(g_Shadow[nCntShadow].ShadowWidth , 0.0f, g_Shadow[nCntShadow].ShadowDepth);
			pVtx[nCntShadow * 4 + 2].pos = D3DXVECTOR3(-g_Shadow[nCntShadow].ShadowWidth, 0.0f, -g_Shadow[nCntShadow].ShadowDepth);
			pVtx[nCntShadow * 4 + 3].pos = D3DXVECTOR3(g_Shadow[nCntShadow].ShadowWidth , 0.0f, -g_Shadow[nCntShadow].ShadowDepth);

			//影が地面に被らないように０．１上げる
			g_Shadow[nCntShadow].pos.y = 0.1f;

			break;
		}
	}

	//頂点バッファをアンロック
	g_pVtxBuffShadow->Unlock();

	//使用している影の番号(インデックス)を返す
	return nCntShadow;
}
//=============================================================================
// 影の設定
//=============================================================================
void SetPositionShadow(int nIdxShadow, D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
		if (g_Shadow[nIdxShadow].bUse == true)
		{//爆発が使用されていない
			g_Shadow[nIdxShadow].pos = pos;			//pos値代入
			g_Shadow[nIdxShadow].rot = rot;			//move値代入

			//影の位置
			g_Shadow[nIdxShadow].pos.y = 0.1f;
		}
}
//=============================================================================
// 影の削除処理
//=============================================================================
void DeleteShadow(int nIdxShadow)
{
	if (g_Shadow[nIdxShadow].bUse == true)
	{//影が使用されている場合
		//特定の番号の影を消す
		g_Shadow[nIdxShadow].bUse = false;
	}
}