//=========================================================================================================================
//
// 背景の処理 [bg.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "bg.h"		//背景

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define BG_TEXTURE_NAME		"data\\TEXTURE\\道.jpg"			//読み込むテクスチャファイル
//#define BG_TEXTURE_NAME1	"data\\TEXTURE\\雲の影1.png"	//読み込むテクスチャファイル
#define BG_POS_X			(0)								//背景の左上X座標
#define BG_POS_Y			(0)								//背景の左上Y座標
#define BG_WIDTH			(SCREEN_WIDTH)					//背景の幅
#define BG_HEIGHT			(SCREEN_HEIGHT)					//背景の高さ
#define BG_MAX				(2)								//背景の高さ
#define BG_TEXTURE_SPEED	(5)								//テクスチャアニメーションスピード
#define BG_TEXTURE_PATTERN	(10)							//テクスチャアニメーションパターン数
#define BG_BACKTEXTURE_UV_U	(1.0f)							//前テクスチャアニメーションU範囲
#define BG_BACKTEXTURE_UV_V	(1.0f)							//前テクスチャアニメーションV範囲
#define BG_SPEED			(0.003f)						//背景スピード
#define MAX_TEXTURE			(2)								//テクスチャ枚数

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureBG = NULL/*[MAX_TEXTURE] = {}*/;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBG = NULL;			//頂点バッファへのポインタ
D3DXVECTOR3 g_posBG;									//背景の位置
D3DXVECTOR3 g_moveBG;									//背景の移動

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitBG(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_posBG = D3DXVECTOR3((BG_POS_X + BG_WIDTH) / 2, (BG_POS_Y + BG_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値
	g_moveBG = D3DXVECTOR3(0.0f, BG_SPEED, 0.0f);		//ポリゴン移動値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		BG_TEXTURE_NAME,
		&g_pTextureBG/*[0]*/
	);
	////テクスチャの読み込み
	//D3DXCreateTextureFromFile
	//(
	//	pDevice,
	//	BG_TEXTURE_NAME1,
	//	&g_pTextureBG[1]
	//);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBG,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffBG->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	////pVtx += 4;

	////頂点設定
	//pVtx[4].pos = D3DXVECTOR3(BG_POS_X, BG_POS_Y, 0.0f);
	//pVtx[5].pos = D3DXVECTOR3(BG_WIDTH, BG_POS_Y, 0.0f);
	//pVtx[6].pos = D3DXVECTOR3(BG_POS_X, BG_HEIGHT, 0.0f);
	//pVtx[7].pos = D3DXVECTOR3(BG_WIDTH, BG_HEIGHT, 0.0f);
	////1.0で固定
	//pVtx[4].rhw = 1.0f;
	//pVtx[5].rhw = 1.0f;
	//pVtx[6].rhw = 1.0f;
	//pVtx[7].rhw = 1.0f;
	////頂点カラー設定
	//pVtx[4].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[5].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[6].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	//pVtx[7].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	////テクスチャ設定
	//pVtx[4].tex = D3DXVECTOR2(0.0f, 0.0f);
	//pVtx[5].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, 0.0f);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, BG_TEXTURE_UV_V);
	//pVtx[7].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, BG_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitBG(void)
{
	/*for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{*/
		//テクスチャーの破棄
		if (g_pTextureBG != NULL)
		{
			g_pTextureBG/*[nCount]*/ -> Release();
			g_pTextureBG/*[nCount]*/ = NULL;
		}
	/*}*/
	//頂点バッファの破棄
	if (g_pVtxBuffBG != NULL)
	{
		g_pVtxBuffBG->Release();
		g_pVtxBuffBG = NULL;
	}
}

//=========================================================================================================================
// 背景更新処理
//=========================================================================================================================
void UpdateBG(void)
{
	g_posBG -= g_moveBG;	//位置の更新

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffBG->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_posBG.y- BG_BACKTEXTURE_UV_V);
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_posBG.y - BG_BACKTEXTURE_UV_V);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_posBG.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_posBG.y);

	/*pVtx += 4;*/

	////テクスチャ設定
	//pVtx[4].tex = D3DXVECTOR2(0.0f, g_posBG.y - BG_BACKTEXTURE_UV_V);
	//pVtx[5].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, g_posBG.y - BG_BACKTEXTURE_UV_V);
	//pVtx[6].tex = D3DXVECTOR2(0.0f, g_posBG.y);
	//pVtx[7].tex = D3DXVECTOR2(BG_TEXTURE_UV_U, g_posBG.y);
	
	if (g_posBG.y + (SCREEN_HEIGHT / 2) >= SCREEN_HEIGHT)
	{//画面外のテクスチャを上に更新
		g_posBG.y = 0;
	}

	//頂点バッファをアンロック
	g_pVtxBuffBG->Unlock();
}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawBG(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffBG,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	/*for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{*/
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureBG/*[nCount]*/);

		//背景の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	/*}*/
}