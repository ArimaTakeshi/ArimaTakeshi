//=========================================================================================================================
//
// タイトルの処理 [tutolial.cpp]
// Author : 有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "tutolial.h"		//チュートリアル
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "enter.h"

//*************************************************************************************************************************
// マクロ定義
//*******************************************************w******************************************************************
#define TUTOLIAL_TEXTURE_NAME		"data\\TEXTURE\\Tutorial2.png"	//読み込むテクスチャファイル
#define TUTOLIAL_TEXTURE_NAME1		"data\\TEXTURE\\Tutorial2.png"	//読み込むテクスチャファイル
#define TUTOLIAL_POS_X				(0)								//タイトルの左上X座標
#define TUTOLIAL_POS_Y				(0)								//タイトルの左上Y座標
#define TUTOLIAL_WIDTH				(SCREEN_WIDTH)					//タイトルの幅
#define TUTOLIAL_HEIGHT				(SCREEN_HEIGHT)					//タイトルの高さ
#define TUTOLIAL_SPEED				(0.003f)						//タイトルスピード
#define MAX_TEXTURE					(1)

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTUTOLIAL[MAX_TEXTURE] = {};			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTUTOLIAL = NULL;					//頂点バッファへのポインタ
D3DXVECTOR3 g_posTUTOLIAL;											//タイトルの位置
D3DXVECTOR3 g_moveTUTOLIAL;											//タイトルの移動
int g_nCntTutorial = 0;

//=========================================================================================================================
// タイトル初期化処理
//=========================================================================================================================
void InitTutolial(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_posTUTOLIAL = D3DXVECTOR3((TUTOLIAL_POS_X + TUTOLIAL_WIDTH) / 2, (TUTOLIAL_POS_Y + TUTOLIAL_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		TUTOLIAL_TEXTURE_NAME,
		&g_pTextureTUTOLIAL[0]
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTUTOLIAL,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffTUTOLIAL->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
			//頂点設定
		pVtx[0].pos = D3DXVECTOR3(TUTOLIAL_POS_X, TUTOLIAL_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(TUTOLIAL_WIDTH, TUTOLIAL_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(TUTOLIAL_POS_X, TUTOLIAL_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(TUTOLIAL_WIDTH, TUTOLIAL_HEIGHT, 0.0f);
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
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffTUTOLIAL->Unlock();

	//エンター
	InitEnter();
}

//=========================================================================================================================
// タイトル終了処理
//=========================================================================================================================
void UninitTutolial(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャーの破棄
		if (g_pTextureTUTOLIAL[nCount] != NULL)
		{
			g_pTextureTUTOLIAL[nCount] -> Release();
			g_pTextureTUTOLIAL[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTUTOLIAL != NULL)
	{
		g_pVtxBuffTUTOLIAL->Release();
		g_pVtxBuffTUTOLIAL = NULL;
	}
	//エンター
	UninitEnter();
}

//=========================================================================================================================
// タイトル更新処理
//=========================================================================================================================
void UpdateTutolial(void)
{
	if (GetKeyboardTrigger(DIK_RETURN) == true || GetMouseTrigger(0) == true)
	{
		//決定音
		PlaySound(SOUND_LABEL_SE_DECIDE);
		//モード設定
		SetFade(MODE_GAME);
	}

	//エンター
	UpdateEnter();
}

//=========================================================================================================================
// タイトル描画処理
//=========================================================================================================================
void DrawTutolial(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTUTOLIAL,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTUTOLIAL[nCount]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	//エンター
	DrawEnter();
}