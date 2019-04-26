//=============================================================================
//
// ライフ処理 [life.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "life.h"
#include "player.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LIFE		"data/TEXTURE/number000.png"	// 読み込むテクスチャファイル名
#define	TEXTURE_LIFE1		"data/TEXTURE/Life.png"			// 読み込むテクスチャファイル名
#define MAX_POLYGON			(22)							//スコアの最大桁数
#define MAX_TEXTURE			(2)								//スコアの最大桁数
#define MAX_LIFE_TEX		(20)							//スコアの最大桁数
#define MAX_LIFE_NUM		(2)								//スコアの最大桁数

#define LIFE_SIZE			(25)
#define TEXLIFE_SIZE_X		(12)
#define TEXLIFE_SIZE_Y		(24)
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureLife[MAX_TEXTURE] = {};		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLife = NULL;					// 頂点バッファへのポインタ
int						g_nLife;								// スコア
D3DXVECTOR3				g_posLife;
D3DXVECTOR3				g_posTexLife;
bool					g_bLifeTex[MAX_LIFE_TEX];

//=============================================================================
// 初期化処理
//=============================================================================
void InitLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posLife = D3DXVECTOR3(50, 630, 0.0f);

	g_posTexLife = D3DXVECTOR3(30, 680, 0.0f);

	for (int nCount = 0; nCount < MAX_LIFE_TEX; nCount++)
	{
		g_bLifeTex[nCount] = true;
	}

	// スコアの初期化
	g_nLife = 0;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
							TEXTURE_LIFE,			// ファイルの名前
							&g_pTextureLife[0]);		// テクスチャへのポインタ

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,				// デバイスへのポインタ
							TEXTURE_LIFE1,			// ファイルの名前
							&g_pTextureLife[1]);	// テクスチャへのポインタ

	// 頂点情報の作成
	MakeVertexLife(pDevice);

	AddLife(20, LifeTex_Init);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitLife(void)
{
	int nCountTex;
	// テクスチャの開放
	for (nCountTex = 0; nCountTex < MAX_TEXTURE; nCountTex++)
	{
		if (g_pTextureLife[nCountTex] != NULL)
		{
			g_pTextureLife[nCountTex] -> Release();
			g_pTextureLife[nCountTex] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffLife != NULL)
	{
		g_pVtxBuffLife->Release();
		g_pVtxBuffLife = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateLife(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawLife(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	int nCountTex;
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffLife, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	for (nCountTex = 0; nCountTex < MAX_POLYGON; nCountTex++)
	{
		if (nCountTex < MAX_LIFE_NUM)
		{
			pDevice->SetTexture(0, g_pTextureLife[0]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex, 2);
		}
		else if (g_bLifeTex[nCountTex - MAX_LIFE_NUM] == true)
		{
			pDevice->SetTexture(0, g_pTextureLife[1]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCountTex , 2);
		}
	}
		// ポリゴンの描画
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexLife(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntLife;

	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_POLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLife,
		NULL);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntLife = 0; nCntLife < MAX_POLYGON; nCntLife++)
	{
		if (nCntLife < MAX_LIFE_NUM)
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posLife.x - LIFE_SIZE, g_posLife.y - LIFE_SIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posLife.x + LIFE_SIZE, g_posLife.y - LIFE_SIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posLife.x - LIFE_SIZE, g_posLife.y + LIFE_SIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posLife.x + LIFE_SIZE, g_posLife.y + LIFE_SIZE, 0.0f);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

			g_posLife.x += 50;
		}
		else
		{
			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_posTexLife.x - TEXLIFE_SIZE_X, g_posTexLife.y - TEXLIFE_SIZE_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_posTexLife.x + TEXLIFE_SIZE_X, g_posTexLife.y - TEXLIFE_SIZE_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_posTexLife.x - TEXLIFE_SIZE_X, g_posTexLife.y + TEXLIFE_SIZE_Y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_posTexLife.x + TEXLIFE_SIZE_X, g_posTexLife.y + TEXLIFE_SIZE_Y, 0.0f);
			//テクスチャ座標
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			g_posTexLife.x += 18;
		}
		
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		if (nCntLife < MAX_POLYGON - 5)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f);
		}

		pVtx += 4;	//頂点データのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}

//=============================================================================
// スコアの加算
//=============================================================================
void AddLife(int nLife, LIFETEX Life)
{
	int nCntLife;
	int aNumber[MAX_LIFE_NUM];

	g_nLife += nLife;

	if (Life == LifeTex_DAMAGE)
	{
		Player *pPlayer = GetPlayer();
		g_bLifeTex[pPlayer->nLife] = false;
	}

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffLife->Lock(0, 0, (void**)&pVtx, 0);

	aNumber[0] = g_nLife % 100 / 10;
	aNumber[1] = g_nLife % 10;

	for (nCntLife = 0; nCntLife < MAX_LIFE_NUM; nCntLife++)
	{
		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + aNumber[nCntLife] * 0.1f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aNumber[nCntLife] * 0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aNumber[nCntLife] * 0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aNumber[nCntLife] * 0.1f, 1.0f);

		if (g_nLife <= 5)
		{
			//頂点カラー
			pVtx[0].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 0.1f, 0.0f, 1.0f);
		}

		pVtx += 4;	//頂点データのポインタを4つ進める
	}

	// 頂点バッファをアンロックする
	g_pVtxBuffLife->Unlock();
}