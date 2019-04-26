//=========================================================================================================================
//
// タイトルの処理 [TITLE.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "Title.h"		//タイトル
#include "input.h"
#include "fade.h"
#include "sound.h"
//*************************************************************************************************************************
// マクロ定義
//*******************************************************w******************************************************************
#define TITLE_TEXTURE_NAME		"data\\TEXTURE\\はなむら.png"	//読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME1		"data\\TEXTURE\\さくら1.png"    //読み込むテクスチャファイル
#define TITLE_POS_X				(0)								//タイトルの左上X座標
#define TITLE_POS_Y				(0)								//タイトルの左上Y座標
#define TITLE_WIDTH				(SCREEN_WIDTH)					//タイトルの幅
#define TITLE_HEIGHT			(SCREEN_HEIGHT)					//タイトルの高さ
#define TITLE_MAX				(2)								//タイトルの高さ
#define TITLE_TEXTURE_SPEED		(5)								//テクスチャアニメーションスピード
#define TITLE_TEXTURE_PATTERN	(10)							//テクスチャアニメーションパターン数
#define TITLE_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define TITLE_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲
#define TITLE_BACKTEXTURE_UV_U	(1.0f)							//前テクスチャアニメーションU範囲
#define TITLE_BACKTEXTURE_UV_V	(1.0f)							//前テクスチャアニメーションV範囲
#define TITLE_SPEED				(0.003f)						//タイトルスピード
#define MAX_TEXTURE				(2)

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTITLE[MAX_TEXTURE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTITLE = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posTITLE;								//タイトルの位置
D3DXVECTOR3 g_moveTITLE;							//タイトルの移動

//=========================================================================================================================
// タイトル初期化処理
//=========================================================================================================================
void InitTitle(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_posTITLE = D3DXVECTOR3((TITLE_POS_X + TITLE_WIDTH) / 2, (TITLE_POS_Y + TITLE_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値
	g_moveTITLE = D3DXVECTOR3(0.0f, TITLE_SPEED, 0.0f);		//ポリゴン移動値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTITLE[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TITLE_TEXTURE_NAME1,
		&g_pTextureTITLE[1]
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * TITLE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTITLE,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffTITLE->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V);

	pVtx += 4;

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TITLE_POS_X, TITLE_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TITLE_WIDTH, TITLE_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffTITLE->Unlock();
}

//=========================================================================================================================
// タイトル終了処理
//=========================================================================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャーの破棄
		if (g_pTextureTITLE[nCount] != NULL)
		{
			g_pTextureTITLE[nCount] -> Release();
			g_pTextureTITLE[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTITLE != NULL)
	{
		g_pVtxBuffTITLE->Release();
		g_pVtxBuffTITLE = NULL;
	}
}

//=========================================================================================================================
// タイトル更新処理
//=========================================================================================================================
void UpdateTitle(void)
{
	//設定キー（ENTERキー）が押されたかどうか
	g_posTITLE -= g_moveTITLE;	//位置の更新

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

							//頂点バッファをロック
	g_pVtxBuffTITLE->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	pVtx += 4;

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_posTITLE.y - TITLE_BACKTEXTURE_UV_V);
	pVtx[1].tex = D3DXVECTOR2(TITLE_BACKTEXTURE_UV_U, g_posTITLE.y - TITLE_BACKTEXTURE_UV_V);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_posTITLE.y);
	pVtx[3].tex = D3DXVECTOR2(TITLE_BACKTEXTURE_UV_U, g_posTITLE.y);

	////テクスチャ設定
	//pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f - 0.5f);
	//pVtx[1].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, 0.0f - 0.5f);
	//pVtx[2].tex = D3DXVECTOR2(0.0f, TITLE_TEXTURE_UV_V - 0.5f);
	//pVtx[3].tex = D3DXVECTOR2(TITLE_TEXTURE_UV_U, TITLE_TEXTURE_UV_V - 0.5f);

	if (g_posTITLE.y + (SCREEN_HEIGHT / 2) >= SCREEN_HEIGHT)
	{//画面外のテクスチャを上に更新
		g_posTITLE.y = 0;
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		//決定音
		PlaySound(SOUND_LABEL_SE_DECIDE);
		//モード設定
		SetFade(MODE_PLAYTUTORIAL);
	}
	//頂点バッファをアンロック
	g_pVtxBuffTITLE->Unlock();
}

//=========================================================================================================================
// タイトル描画処理
//=========================================================================================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTITLE,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTITLE[nCount]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}