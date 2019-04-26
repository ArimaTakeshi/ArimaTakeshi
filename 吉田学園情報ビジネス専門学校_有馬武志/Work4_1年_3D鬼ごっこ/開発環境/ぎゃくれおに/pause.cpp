//=========================================================================================================================
//
// ポーズの処理 [pause.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "pause.h"		//ポーズ
#include "input.h"		//キーボード
#include "fade.h"		//フェード
#include "game.h"		//ポーズ
#include "sound.h"		//サウンド

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define PAUSE_TEXTURE_NAME		"data\\TEXTURE\\ポーズ.png"		//読み込むテクスチャファイル
#define PAUSE_TEXTURE_NAME0		"data\\TEXTURE\\pause000.png"	//読み込むテクスチャファイル
#define PAUSE_TEXTURE_NAME1		"data\\TEXTURE\\pause001.png"	//読み込むテクスチャファイル
#define PAUSE_TEXTURE_NAME2		"data\\TEXTURE\\pause002.png"	//読み込むテクスチャファイル
#define MAX_TEXTURE				(4)								//テクスチャの最大数
#define PAUSE_POS_X				(0)								//ポーズの左上X座標
#define PAUSE_POS_Y				(0)								//ポーズの左上Y座標
#define PAUSE_WIDTH				(SCREEN_WIDTH)					//ポーズの幅
#define PAUSE_HEIGHT			(SCREEN_HEIGHT)					//ポーズの高さ
#define PAUSE_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
#define PAUSE_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲
#define PAUSE_SPEED				(0.003f)						//ポーズスピード

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEXTURE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;		 //頂点バッファへのポインタ
PAUSE g_Pause;										 //ポスの情報

//=========================================================================================================================
// ポーズ初期化処理
//=========================================================================================================================
void InitPause(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_Pause.pos = D3DXVECTOR3((PAUSE_POS_X + PAUSE_WIDTH) / 2, (PAUSE_POS_Y + PAUSE_HEIGHT) / 2, 0.0f);
	g_Pause.SelectNum = 0;
	g_Pause.SelectColor = 1.0f;

	//ポーズの座標
	float PosPause = (SCREEN_HEIGHT / 2) - 300;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//１枚目の画像
		pDevice,
		PAUSE_TEXTURE_NAME,
		&g_pTexturePause[0]
	);
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		PAUSE_TEXTURE_NAME0,
		&g_pTexturePause[1]
	);
	D3DXCreateTextureFromFile
	(//３枚目の画像
		pDevice,
		PAUSE_TEXTURE_NAME1,
		&g_pTexturePause[2]
	);
	D3DXCreateTextureFromFile
	(//４枚目の画像
		pDevice,
		PAUSE_TEXTURE_NAME2,
		&g_pTexturePause[3]
	);

	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
		if (nCount == 0)
		{//カウント０だった場合

			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(PAUSE_POS_X, PAUSE_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH, PAUSE_HEIGHT, 0.0f);
			//頂点カラー設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{//それ以外の場合
		 //頂点設定
			pVtx[0].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 - 250, PosPause, 0.0f);			//左上
			pVtx[1].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 + 250, PosPause, 0.0f);			//右上
			pVtx[2].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 - 250, PosPause + 200, 0.0f);		//左下
			pVtx[3].pos = D3DXVECTOR3(PAUSE_WIDTH / 2 + 250, PosPause + 200, 0.0f);		//右下

			if (nCount == 1)
			{
				//頂点カラー設定
				pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
				pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			}
			else
			{
				//頂点カラー設定
				pVtx[0].col = D3DCOLOR_RGBA(127, 127, 127, 255);
				pVtx[1].col = D3DCOLOR_RGBA(127, 127, 127, 255);
				pVtx[2].col = D3DCOLOR_RGBA(127, 127, 127, 255);
				pVtx[3].col = D3DCOLOR_RGBA(127, 127, 127, 255);
			}
			//選択欄の幅
			PosPause += 200;
		}

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, PAUSE_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(PAUSE_TEXTURE_UV_U, PAUSE_TEXTURE_UV_V);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();
}

//=========================================================================================================================
// ポーズ終了処理
//=========================================================================================================================
void UninitPause(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTexturePause[nCount] != NULL)
		{
			g_pTexturePause[nCount] -> Release();
			g_pTexturePause[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//=========================================================================================================================
// ポーズ更新処理
//=========================================================================================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロック
	g_pVtxBuffPause->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);
	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_18, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_10, 0) == true)
	{//矢印キーの上を押したとき
		// 頂点カラー設定
		pVtx[g_Pause.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Pause.SelectNum = (g_Pause.SelectNum + 2) % 3;
		g_Pause.SelectColor = 1.0f;

		PlaySound(SOUND_LABEL_SE_UPDWON);
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(DIJS_BUTTON_19, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_11, 0) == true)
	{//矢印キーの下を押したとき
		// 頂点カラー設定
		pVtx[g_Pause.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Pause.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Pause.SelectNum = (g_Pause.SelectNum + 1) % 3;
		g_Pause.SelectColor = 1.0f;
		PlaySound(SOUND_LABEL_SE_UPDWON);
	}

	//点滅処理
	//選択しているカラーの値を減らしていく
	g_Pause.SelectColor -= 0.01f;

	if (g_Pause.SelectColor < 0.5f)
	{//信託しているカラーが0.5を切ったらカラーの値が増えてく
		g_Pause.SelectColor = 1.0f;
	}

	// 頂点カラー設定
	pVtx[g_Pause.SelectNum * 4 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);
	pVtx[g_Pause.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);
	pVtx[g_Pause.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);
	pVtx[g_Pause.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(g_Pause.SelectColor, g_Pause.SelectColor, g_Pause.SelectColor, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffPause->Unlock();

	if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
	{
		if (g_Pause.SelectNum == 0)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//キャンセル
			SetPauseState(false);
		}
		else if (g_Pause.SelectNum == 1)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//ゲームの最初に戻る
			SetFade(MODE_GAME);
		}
		else if (g_Pause.SelectNum == 2)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//ゲームのタイトルに戻る
			SetFade(MODE_TITLE);
		}
	}
}

//=========================================================================================================================
// ポーズ描画処理
//=========================================================================================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffPause,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTexturePause[nCount]);

		//ポーズの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}