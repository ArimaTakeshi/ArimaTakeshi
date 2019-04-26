//=============================================================================
//
// アイテムのカウントの表示処理 [ItemCount.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "itemcount.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_ITEMCOUNT	"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_ITEMCOUNT		(3)								//スコアの最大桁数
#define ITEMCOUNT_SIZE		(25)							//桁の幅

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexItemCount(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureItemCount = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItemCount = NULL;		// 頂点バッファへのポインタ
int						g_nItemCount;					// スコア
D3DXVECTOR3				g_posItemCount;

//=============================================================================
// 初期化処理
//=============================================================================
void InitItemCount(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//初期値
	g_posItemCount = D3DXVECTOR3(80, 32, 0.0f);

	// スコアの初期化
	g_nItemCount = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//画像１枚目
		pDevice,
		TEXTURE_ITEMCOUNT,
		&g_pTextureItemCount
	);

	// 頂点情報の作成
	MakeVertexItemCount(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitItemCount(void)
{
	// テクスチャの開放
	if (g_pTextureItemCount != NULL)
	{
		g_pTextureItemCount->Release();
		g_pTextureItemCount = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffItemCount != NULL)
	{
		g_pVtxBuffItemCount->Release();
		g_pVtxBuffItemCount = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateItemCount(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawItemCount(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItemCount, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureItemCount);

	for (int nCntItemCount = 0; nCntItemCount < MAX_ITEMCOUNT; nCntItemCount++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntItemCount, 2);
	}
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexItemCount(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntItemCount;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 8,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffItemCount,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItemCount->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItemCount = 0; nCntItemCount < MAX_ITEMCOUNT; nCntItemCount++)
	{//全テクスチャのカウント
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posItemCount.x - ITEMCOUNT_SIZE, g_posItemCount.y - ITEMCOUNT_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posItemCount.x + ITEMCOUNT_SIZE, g_posItemCount.y - ITEMCOUNT_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posItemCount.x - ITEMCOUNT_SIZE, g_posItemCount.y + ITEMCOUNT_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posItemCount.x + ITEMCOUNT_SIZE, g_posItemCount.y + ITEMCOUNT_SIZE, 0.0f);

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ進める
		g_posItemCount.x += 43;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffItemCount->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddItemCount(int nValue)
{
	int nCntItemCount;
	int aNumber[MAX_ITEMCOUNT];

	g_nItemCount += nValue;

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItemCount->Lock(0, 0, (void**)&pVtx, 0);

	//桁数文（３桁）
	aNumber[0] = g_nItemCount % 1000 / 100;
	aNumber[1] = g_nItemCount % 100 / 10;
	aNumber[2] = g_nItemCount % 10;

	for (nCntItemCount = 0; nCntItemCount < MAX_ITEMCOUNT; nCntItemCount++)
	{//全テクスチャのカウント
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntItemCount] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntItemCount] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntItemCount] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntItemCount] * 0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffItemCount->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
int GetItemCount(void)
{
	return g_nItemCount;
}