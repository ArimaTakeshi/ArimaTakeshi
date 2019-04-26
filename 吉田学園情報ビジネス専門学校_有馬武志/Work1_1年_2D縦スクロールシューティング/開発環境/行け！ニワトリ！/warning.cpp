	//=========================================================================================================================
//
// ワーニングの処理 [warning.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "warning.h"		//ワーニング
#include "sound.h"			//サウンド

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define WARNING_TEXTURE_NAME	 "data\\TEXTURE\\ボス前.png"	//読み込むテクスチャファイル
#define WARNING_POS_X			 (0)							//ワーニングの左上X座標
#define WARNING_POS_Y			 (0)							//ワーニングの左上Y座標
#define WARNING_WIDTH			 (SCREEN_WIDTH)					//ワーニングの幅
#define WARNING_HEIGHT			 (SCREEN_HEIGHT)				//ワーニングの高さ
#define WARNING_MAX				 (2)							//ワーニングの高さ
#define WARNING_TEXTURE_SPEED	 (5)							//テクスチャアニメーションスピード
#define WARNING_TEXTURE_PATTERN	 (10)							//テクスチャアニメーションパターン数
#define WARNING_TEXTURE_UV_U	 (1.0f)							//テクスチャアニメーションU範囲
#define WARNING_TEXTURE_UV_V	 (1.0f)							//テクスチャアニメーションV範囲
#define WARNING_BACKTEXTURE_UV_U (1.0f)							//前テクスチャアニメーションU範囲
#define WARNING_BACKTEXTURE_UV_V (1.0f)							//前テクスチャアニメーションV範囲
#define WARNING_SPEED			 (0.003f)						//ワーニングスピード

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureWARNING = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffWARNING = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posWARNING;								//ワーニングの位置
D3DXVECTOR3 g_moveWARNING;								//ワーニングの移動
bool g_bUse;											//ワーニングを使用してるか使用してないか
int g_nCount;											//

//=========================================================================================================================
// ワーニング初期化処理
//=========================================================================================================================
void InitWarning(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_nCount = 0;
	g_bUse = false;

	g_posWARNING = D3DXVECTOR3((WARNING_POS_X +WARNING_WIDTH) / 2, (WARNING_POS_Y +WARNING_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値
	g_moveWARNING = D3DXVECTOR3(WARNING_SPEED, 0.0f, 0.0f);		//ポリゴン移動値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		WARNING_TEXTURE_NAME,
		&g_pTextureWARNING
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffWARNING,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffWARNING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(WARNING_POS_X,WARNING_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(WARNING_WIDTH,WARNING_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(WARNING_POS_X,WARNING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(WARNING_WIDTH,WARNING_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(WARNING_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,WARNING_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(WARNING_TEXTURE_UV_U,WARNING_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffWARNING->Unlock();
}

//=========================================================================================================================
// ワーニング終了処理
//=========================================================================================================================
void UninitWarning(void)
{
	//テクスチャーの破棄
	if (g_pTextureWARNING != NULL)
	{
		g_pTextureWARNING->Release();
		g_pTextureWARNING = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffWARNING != NULL)
	{
		g_pVtxBuffWARNING->Release();
		g_pVtxBuffWARNING = NULL;
	}
}

//=========================================================================================================================
// ワーニング更新処理
//=========================================================================================================================
void UpdateWarning(void)
{
	g_posWARNING += g_moveWARNING;	//位置の更新

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffWARNING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	g_nCount++;

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(g_posWARNING.x, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(g_posWARNING.x + WARNING_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(g_posWARNING.x, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_posWARNING.x + WARNING_TEXTURE_UV_U, 1.0f);

	if (g_posWARNING.x + (SCREEN_WIDTH / 2) <= 0)
	{//画面外のテクスチャを上に更新
		g_posWARNING.x = SCREEN_WIDTH;
	}

	if (g_nCount % 350 == 0)
	{
		g_bUse = false;

		StopSound(SOUND_LABEL_SE_SHOT);
	}


	//頂点バッファをアンロック
	g_pVtxBuffWARNING->Unlock();
}

//=========================================================================================================================
// ワーニング描画処理
//=========================================================================================================================
void DrawWarning(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffWARNING,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureWARNING);

	if (g_bUse == true)
	{
		//ワーニングの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	}
}
//=========================================================================================================================
// ワーニング
//=========================================================================================================================
void SetWarning(void)
{
	g_bUse = true;

	PlaySound(SOUND_LABEL_SE_SHOT);
}