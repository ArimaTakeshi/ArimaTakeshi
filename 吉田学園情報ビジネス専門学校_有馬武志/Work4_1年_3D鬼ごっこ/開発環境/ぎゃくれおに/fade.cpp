//=============================================================================
//
// フェード処理 [fade.cpp]
// Author : 有馬　武志
//
//=============================================================================
#include "fade.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NUM_POLYGON				(2)
#define FADE_POS_X				(0)								//フェードの左上X座標
#define FADE_POS_Y				(0)								//フェードの左上Y座標
#define FADE_WIDTH				(SCREEN_WIDTH)					//フェードの幅
#define FADE_HEIGHT				(SCREEN_HEIGHT)					//フェードの高さ
#define FADE_TEXTURE_UV_U		(1.0f)							//フェードU範囲
#define FADE_TEXTURE_UV_V		(1.0f)							//フェードV範囲
#define FADE_TIME				(0.02f)							//フェードの時間

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFade = NULL;	// 頂点バッファへのポインタ

FADE					g_fade;					// フェード状態
MODE					g_modeNext;				// 次のモード
D3DXCOLOR				g_colorFade;			// フェード色

//=============================================================================
// 初期化処理
//=============================================================================
void InitFade(MODE modeNext)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 値の初期化
	g_fade = FADE_IN;									//フェードイン状態
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//黒い不透明にしておく

	// 頂点情報の設定
	MakeVertexFade(pDevice);
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitFade(void)
{
	//テクスチャーの破棄
	if (g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffFade != NULL)
	{
		g_pVtxBuffFade->Release();
		g_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateFade(void)
{
	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)				//フェードイン
		{
			g_colorFade.a -= FADE_TIME;		//画面を透明にしていく
			if (g_colorFade.a <= 0.0f)
			{
				g_colorFade.a = 0.0f;
				g_fade = FADE_NONE;			//何もしていない
			}
		}
		else if (g_fade == FADE_OUT)
		{
			g_colorFade.a += FADE_TIME;		//画面を不透明にしていく
			if (g_colorFade.a >= 1.0f)
			{
				g_colorFade.a = 1.0f;
				g_fade = FADE_IN;			//フェードイン

				//モード設定
				SetMode(g_modeNext);
			}
		}

		VERTEX_2D *pVtx;					//頂点情報へのポインタ


		//頂点バッファをロック
		g_pVtxBuffFade->Lock
		(
			0,
			0,
			(void**)&pVtx,
			0
		);

		//頂点カラーの更新
		pVtx[0].col = g_colorFade;
		pVtx[1].col = g_colorFade;
		pVtx[2].col = g_colorFade;
		pVtx[3].col = g_colorFade;

		//頂点バッファをアンロック
		g_pVtxBuffFade->Unlock();
	}
}

//=============================================================================
// フェード画面
//=============================================================================
void DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, g_pTextureFade);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice)
{
	// 頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffFade,
		NULL);

	// 頂点バッファの情報を設定
	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffFade->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(FADE_WIDTH, FADE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(FADE_POS_X, FADE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(FADE_WIDTH, FADE_HEIGHT, 0.0f);
	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(FADE_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, FADE_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(FADE_TEXTURE_UV_U, FADE_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffFade->Unlock();
}

//=============================================================================
// フェードの設定
//=============================================================================
void SetFade(MODE modeNext)
{
	g_fade = FADE_OUT;										//フェードアウト
	g_modeNext = modeNext;
	g_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);		//黒い画面（透明）にしておく
}

//=============================================================================
// フェードの取得
//=============================================================================
FADE GetFade(void)
{
	return g_fade;
}

