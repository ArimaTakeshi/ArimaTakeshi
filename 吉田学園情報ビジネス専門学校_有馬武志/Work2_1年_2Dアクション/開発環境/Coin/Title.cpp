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
#include "input.h"		//入力
#include "fade.h"		//フェード
#include "sound.h"		//サウンド
#include "menu.h"		//メニュー
#include "enter.h"		//エンター

//*************************************************************************************************************************
// マクロ定義
//*******************************************************w******************************************************************
#define TITLE_TEXTURE_NAME		"data\\TEXTURE\\芝生.png"		//読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME1		"data\\TEXTURE\\雲1.png"		//読み込むテクスチャファイル
#define TITLE_TEXTURE_NAME2		"data\\TEXTURE\\タイトルロゴ.png"//読み込むテクスチャファイル
#define MAX_TEX					(3)								//テクスチャの最大数
#define TITLE_POS_X				(0)								//タイトルの左上X座標
#define TITLE_POS_Y				(0)								//タイトルの左上Y座標
#define TITLE_WIDTH				(SCREEN_WIDTH)					//タイトルの幅
#define TITLE_HEIGHT			(SCREEN_HEIGHT)					//タイトルの高さ
#define TITLE_SPEED0			(0.0003f)						//背景スピード
#define TITLE_SPEED01			(0.0005f)						//背景スピード
#define TITLE_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define TITLE_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TEX] = {};	//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点バッファへのポインタ

Title g_Title;										//タイトルの情報
int g_nCounterGameState1;
//=========================================================================================================================
// タイトル初期化処理
//=========================================================================================================================
void InitTitle(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//ポリゴンの中心値
	g_Title.pos = D3DXVECTOR3((TITLE_POS_X + TITLE_WIDTH) / 2, (TITLE_POS_Y + TITLE_HEIGHT) / 2, 0.0f);
	//ポリゴン移動値
	g_Title.move = D3DXVECTOR3(0.0f, TITLE_SPEED0, 0.0f);
	g_Title.nCounterAnim = 0;
	g_Title.nPatteunAnim = 0;
	g_nCounterGameState1 = 0;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//１枚目の画像
		pDevice,
		TITLE_TEXTURE_NAME,
		&g_pTextureTitle[0]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		TITLE_TEXTURE_NAME1,
		&g_pTextureTitle[1]
	);
	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//３枚目の画像
		pDevice,
		TITLE_TEXTURE_NAME2,
		&g_pTextureTitle[2]
	);


	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEX ,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL
	);

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;	

	//頂点バッファをロック
	g_pVtxBuffTitle->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{//全テクスチャのカウント
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

		//頂点ずらし
		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	InitEnter();
}

//=========================================================================================================================
// タイトル終了処理
//=========================================================================================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount] ->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}
	UninitEnter();
}

//=========================================================================================================================
// タイトル更新処理
//=========================================================================================================================
void UpdateTitle(void)
{
	//位置の更新
	g_Title.pos.y += g_Title.move.y;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	FADE pFade = *GetFade();

	//頂点バッファをロック
	g_pVtxBuffTitle->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//２枚目の画像を横スクロール
	pVtx += 4;

	//テクスチャ設定 縦スクロール用
	pVtx[0].tex = D3DXVECTOR2(0.0f, g_Title.pos.y - 1.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, g_Title.pos.y - 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, g_Title.pos.y);
	pVtx[3].tex = D3DXVECTOR2(1.0f, g_Title.pos.y);

	////テクスチャ設定 横スクロール用
	//pVtx[0].tex = D3DXVECTOR2(g_Title.pos.x + 0.0f, 0.0f);
	//pVtx[1].tex = D3DXVECTOR2(g_Title.pos.x + 0.25f, 0.0f);
	//pVtx[2].tex = D3DXVECTOR2(g_Title.pos.x + 0.0f, 1.0f);
	//pVtx[3].tex = D3DXVECTOR2(g_Title.pos.x + 0.25f, 1.0f);

	//頂点バッファをアンロック
	g_pVtxBuffTitle->Unlock();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{//エンターキーが押されたら
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFadeMode(MODE_SERECT);
		}
		else
		{
			g_nCounterGameState1++;

			if (g_nCounterGameState1 >= 1200)
			{
				// = GAMESTATE_NONE;
				//画面（モード）の設定
				SetFadeMode(MODE_RANKING);
				//タイトルの曲を止める
				StopSound(SOUND_LABEL_BGM005);
			}
		}
	}
	UpdateEnter();
}

//=========================================================================================================================
// タイトル描画処理
//=========================================================================================================================
void DrawTitle(void)
{

	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice= GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffTitle,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//タイトルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
	DrawEnter();
}