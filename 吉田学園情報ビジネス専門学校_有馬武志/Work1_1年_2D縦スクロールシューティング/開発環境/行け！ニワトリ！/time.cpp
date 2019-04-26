//=============================================================================
//
// タイム処理 [time.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "time.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_TIME		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define MAX_TIME			(3)								//スコアの最大桁数
#define TIME_SIZE			(25)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
//void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTime = NULL;		// テクfスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTime = NULL;		// 頂点バッファへのポインタ
int						g_nTime;					// スコア
D3DXVECTOR3				g_posTime;

//=============================================================================
// 初期化処理
//=============================================================================
void InitTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posTime = D3DXVECTOR3(SCREEN_WIDTH / 2, 40, 0.0f);

	// スコアの初期化
	g_nTime = 12000;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
							TEXTURE_TIME,			// ファイルの名前
							&g_pTextureTime);		// テクスチャへのポインタ

	// 頂点情報の作成
	//MakeVertexTime(pDevice);


	int nCntTime;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TIME,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL
	);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ進める
		g_posTime.x += 50;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();


	//AddTime(180);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTime(void)
{
	// テクスチャの開放
	if (g_pTextureTime != NULL)
	{
		g_pTextureTime->Release();
		g_pTextureTime = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTime != NULL)
	{
		g_pVtxBuffTime->Release();
		g_pVtxBuffTime = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTime(void)
{
	int nCntTime;
	int aNumber[MAX_TIME];

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	aNumber[0] = g_nTime % 100000 / 10000;
	aNumber[1] = g_nTime % 10000 / 1000;
	aNumber[2] = g_nTime % 1000 / 100;

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntTime] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntTime] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntTime] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntTime] * 0.1f, 1.0f);

		if (g_nTime <= 3000)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.3f, 0.0f, 1.0f);
		}

		pVtx += 4;	//頂点データのポインタを4つ進める
	} 
	g_nTime--;

	// 頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawTime(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTime, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureTime);

	for (int nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntTime, 2);
	}
}
/*
//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexTime(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntTime;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 3,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTime,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTime->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTime = 0; nCntTime < MAX_TIME; nCntTime++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y - TIME_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_posTime.x - TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_posTime.x + TIME_SIZE, g_posTime.y + TIME_SIZE, 0.0f);

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラー
		pVtx[0].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;	//頂点データのポインタを4つ進める
		g_posTime.x += 50;
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffTime->Unlock();
}*/