//=========================================================================================================================
//
// エンターの処理 [enter.cpp]
// Author : 有馬 武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "enter.h"		//エンター
#include "game.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define ENTER_TEXTURE_NAME		"data\\TEXTURE\\PressEnter2.png"	//読み込むテクスチャファイル
#define ENTER_TEXTURE_UV_U		(1.0f)								//テクスチャアニメーションU範囲
#define ENTER_TEXTURE_UV_V		(1.0f)								//テクスチャアニメーションV範囲
#define ENTER_SIZE_X			(200)
#define	ENTER_SIZE_Y			(50)
#define MAX_TEXTURE				(1)									//テクスチャ枚数

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureEnter = NULL;				//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnter = NULL;			//頂点バッファへのポインタ
Enter g_Enter;

//=========================================================================================================================
// エンター初期化処理
//=========================================================================================================================
void InitEnter(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//モードのポインタ
	MODE pMode = *GetMode();

	//デバイスの取得
	pDevice = GetDevice();

	//初期化
	g_Enter.col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 300, SCREEN_HEIGHT / 2, 0.0f);

	if (pMode == MODE_TUTORIAL)
	{
		g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 380, SCREEN_HEIGHT / 2 + 280, 0.0f);
	}
	else if (pMode == MODE_RANKING)
	{
		g_Enter.pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 400, SCREEN_HEIGHT / 2 + 280, 0.0f);
	}


	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		ENTER_TEXTURE_NAME,
		&g_pTextureEnter
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnter,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffEnter->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200,SCREEN_HEIGHT / 2 + 230, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 230, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 330, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 + 330, 0.0f);
	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, ENTER_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, ENTER_TEXTURE_UV_V);

	if (pMode == MODE_TUTORIAL)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENTER_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, ENTER_TEXTURE_UV_V);

	}
	else if (pMode == MODE_RANKING)
	{
		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Enter.pos.x - ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Enter.pos.x + ENTER_SIZE_X, g_Enter.pos.y + ENTER_SIZE_Y, 0.0f);
		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, ENTER_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(ENTER_TEXTURE_UV_U, ENTER_TEXTURE_UV_V);

	}
	//頂点バッファをアンロック
	g_pVtxBuffEnter->Unlock();
}

//=========================================================================================================================
// エンター終了処理
//=========================================================================================================================
void UninitEnter(void)
{
	//テクスチャーの破棄
	if (g_pTextureEnter != NULL)
	{
		g_pTextureEnter->Release();
		g_pTextureEnter = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffEnter != NULL)
	{
		g_pVtxBuffEnter->Release();
		g_pVtxBuffEnter = NULL;
	}
}

//=========================================================================================================================
// エンター更新処理
//=========================================================================================================================
void UpdateEnter(void)
{
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロック
	g_pVtxBuffEnter->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//点滅処理
	//選択しているカラーの値を減らしていく
	g_Enter.col.a -= 0.015f;

	if (g_Enter.col.a < 0.1f)
	{//信託しているカラーが0.5を切ったらカラーの値が増えてく
		g_Enter.col.a = 1.0f;
	}

	// 頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Enter.col.a);

	//頂点バッファをアンロック
	g_pVtxBuffEnter->Unlock();
}

//=========================================================================================================================
// エンター描画処理
//=========================================================================================================================
void DrawEnter(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffEnter,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureEnter);

	//エンターの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}