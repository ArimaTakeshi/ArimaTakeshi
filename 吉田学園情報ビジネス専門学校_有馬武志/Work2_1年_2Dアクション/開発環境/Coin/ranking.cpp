//=========================================================================================================================
//
// ランキングの処理 [ranking.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"
#include "ranking.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "score.h"

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define RANKING_TEXTURE_NAME		"data\\TEXTURE\\ランキング2.jpg"	//読み込むテクスチャファイル
#define RANKING_POS_X				(0)								//背景の左上X座標
#define RANKING_POS_Y				(0)								//背景の左上Y座標
#define RANKING_WIDTH				(SCREEN_WIDTH)					//背景の幅
#define RANKING_HEIGHT				(SCREEN_HEIGHT)					//背景の高さ
#define RANKING_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define RANKING_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureRANKING = NULL;			//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRANKING = NULL;		//頂点バッファへのポインタ
D3DXVECTOR3 g_posRANKING;								//背景の位置
D3DXVECTOR3 g_moveRANKING;								//背景の移動

//=========================================================================================================================
// 背景初期化処理
//=========================================================================================================================
void InitRanking(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//初期値
	g_posRANKING = D3DXVECTOR3((RANKING_POS_X + RANKING_WIDTH) / 2, (RANKING_POS_Y + RANKING_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(
		pDevice,
		RANKING_TEXTURE_NAME,
		&g_pTextureRANKING
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRANKING,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

						//頂点バッファをロック
	g_pVtxBuffRANKING->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(RANKING_POS_X, RANKING_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(RANKING_WIDTH, RANKING_HEIGHT, 0.0f);
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
	pVtx[1].tex = D3DXVECTOR2(RANKING_TEXTURE_UV_U, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, RANKING_TEXTURE_UV_V);
	pVtx[3].tex = D3DXVECTOR2(RANKING_TEXTURE_UV_U, RANKING_TEXTURE_UV_V);

	//頂点バッファをアンロック
	g_pVtxBuffRANKING->Unlock();

	//スコアの初期化
	InitScore();

	//************************************
	// ランキング表示
	//************************************
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 290, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 160, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 - 30, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 + 90, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	SetScore(D3DXVECTOR3(SCREEN_WIDTH / 2 + 505, SCREEN_HEIGHT / 2 + 220, 0.0f), D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f), 65, 75);
	AddScore(0,SCORE_RAKING);
}

//=========================================================================================================================
// 背景終了処理
//=========================================================================================================================
void UninitRanking(void)
{
	//テクスチャーの破棄
	if (g_pTextureRANKING != NULL)
	{
		g_pTextureRANKING->Release();
		g_pTextureRANKING = NULL;
	}
	//頂点バッファの破棄
	if (g_pVtxBuffRANKING != NULL)
	{
		g_pVtxBuffRANKING->Release();
		g_pVtxBuffRANKING = NULL;
	}
	//スコアの終了処理
	UninitScore();
}

//=========================================================================================================================
// 背景更新処理
//=========================================================================================================================
void UpdateRanking(void)
{
	//フェードのポインタ
	FADE pFade = *GetFade();

	static int nCount = 0;

	nCount++;
	if (pFade == FADE_NONE)
	{
		//設定キー（ENTERキー）が押されたかどうか
		if (GetKeyboardTrigger(DIK_RETURN) == true || (nCount % 350) == 0)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFadeMode(MODE_TITLE);
		}
	}
	//スコアの更新処理
	UpdateScore();
}

//=========================================================================================================================
// 背景描画処理
//=========================================================================================================================
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

									//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffRANKING,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureRANKING);

	//背景の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//スコアの描画処理
	DrawScore();
}
