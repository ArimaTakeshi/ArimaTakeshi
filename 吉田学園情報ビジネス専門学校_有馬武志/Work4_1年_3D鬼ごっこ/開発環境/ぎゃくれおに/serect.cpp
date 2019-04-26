//=========================================================================================================================
//
// セレクトの処理 [Serect.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "serect.h"		//セレクト
#include "input.h"		//キーボード
#include "fade.h"		//フェード
#include "game.h"		//ゲーム
#include "sound.h"		//サウンド
#include "main.h"		//メイン

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define SERECT_TEXTURE_NAME		"data\\TEXTURE\\セレクト.png"		//読み込むテクスチャファイル
#define SERECT_TEXTURE_NAME0	"data\\TEXTURE\\play.png"			//読み込むテクスチャファイル
#define SERECT_TEXTURE_NAME1	"data\\TEXTURE\\End.png"			//読み込むテクスチャファイル
#define MAX_TEXTURE				(3)									//テクスチャの最大数
#define SERECT_POS_X			(0)								
//セレクトの左上X座標
#define SERECT_POS_Y			(0)									//セレクトの左上Y座標
#define SERECT_WIDTH			(SCREEN_WIDTH)						//セレクトの幅
#define SERECT_HEIGHT			(SCREEN_HEIGHT)						//セレクトの高さ
#define SERECT_TEXTURE_UV_U		(1.0f)								//テクスチャアニメーションU範囲
#define SERECT_TEXTURE_UV_V		(1.0f)								//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureSerect[MAX_TEXTURE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffSerect = NULL;		 //頂点バッファへのポインタ
SERECT g_Serect;										 //ポスの情報

//=========================================================================================================================
// セレクト初期化処理
//=========================================================================================================================
void InitSerect(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	g_Serect.pos = D3DXVECTOR3((SERECT_POS_X + SERECT_WIDTH) / 2, (SERECT_POS_Y + SERECT_HEIGHT) / 2, 0.0f);
	g_Serect.SelectNum = 0;
	g_Serect.SelectColor = 1.0f;

	//セレクトの座標
	float PosSerect = (SCREEN_HEIGHT / 2 - 240);

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//１枚目の画像
		pDevice,
		SERECT_TEXTURE_NAME,
		&g_pTextureSerect[0]
	);
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		SERECT_TEXTURE_NAME0,
		&g_pTextureSerect[1]
	);
	D3DXCreateTextureFromFile
	(//４枚目の画像
		pDevice,
		SERECT_TEXTURE_NAME1,
		&g_pTextureSerect[2]
	);
	
	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffSerect,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffSerect->Lock
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
			pVtx[0].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_POS_Y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_POS_Y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(SERECT_POS_X, SERECT_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(SERECT_WIDTH, SERECT_HEIGHT, 0.0f);
			//頂点カラー設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
		else
		{//それ以外の場合
			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(SERECT_WIDTH / 2 - 300, PosSerect, 0.0f);				//左上
			pVtx[1].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 300, PosSerect, 0.0f);				//右上
			pVtx[2].pos = D3DXVECTOR3(SERECT_WIDTH / 2 - 300, PosSerect + 150, 0.0f);		//左下
			pVtx[3].pos = D3DXVECTOR3(SERECT_WIDTH / 2 + 300, PosSerect + 150, 0.0f);		//右下
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
			PosSerect += 230;
		}

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(SERECT_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, SERECT_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(SERECT_TEXTURE_UV_U, SERECT_TEXTURE_UV_V);

		pVtx += 4;
	}
	//頂点バッファをアンロック
	g_pVtxBuffSerect->Unlock();
}

//=========================================================================================================================
// セレクト終了処理
//=========================================================================================================================
void UninitSerect(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureSerect[nCount] != NULL)
		{
			g_pTextureSerect[nCount] -> Release();
			g_pTextureSerect[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffSerect != NULL)
	{
		g_pVtxBuffSerect->Release();
		g_pVtxBuffSerect = NULL;
	}
}

//=========================================================================================================================
// セレクト更新処理
//=========================================================================================================================
void UpdateSerect(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	FADE pFade = GetFade();

	// 頂点バッファをロック
	g_pVtxBuffSerect->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	//GAMESTATE pGameState = GetGameState();

	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_W) == true || GetJoyPadTrigger(DIJS_BUTTON_18, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_10, 0) == true)
	{//矢印キーの上を押したとき
		// 頂点カラー設定
		pVtx[g_Serect.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.SelectNum = (g_Serect.SelectNum + 1) % 2;
		g_Serect.SelectColor = 1.0f;

		PlaySound(SOUND_LABEL_SE_UPDWON);
	}
	else if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_S) == true || GetJoyPadTrigger(DIJS_BUTTON_19, 0) == true || GetJoyPadTrigger(DIJS_BUTTON_11, 0) == true)
	{//矢印キーの下を押したとき
		// 頂点カラー設定
		pVtx[g_Serect.SelectNum * 4 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
		pVtx[g_Serect.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

		g_Serect.SelectNum = (g_Serect.SelectNum + 1) % 2;
		g_Serect.SelectColor = 1.0f;

		PlaySound(SOUND_LABEL_SE_UPDWON);
	}

	//点滅処理
	//選択しているカラーの値を減らしていく
	g_Serect.SelectColor -= 0.01f;

	if (g_Serect.SelectColor < 0.5f)
	{//信託しているカラーが0.5を切ったらカラーの値が増えてく
		g_Serect.SelectColor = 1.0f;
	}

	// 頂点カラー設定
	pVtx[g_Serect.SelectNum * 4 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);
	pVtx[g_Serect.SelectNum * 4 + 1 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);
	pVtx[g_Serect.SelectNum * 4 + 2 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);
	pVtx[g_Serect.SelectNum * 4 + 3 + 4].col = D3DXCOLOR(g_Serect.SelectColor, g_Serect.SelectColor, g_Serect.SelectColor, 1.0f);

	// 頂点バッファをアンロック
	g_pVtxBuffSerect->Unlock();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
		{
			if (g_Serect.SelectNum == 0)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_DECIDE);
				//ゲームに行く
				SetFade(MODE_TUTORIAL);
			}
			else if (g_Serect.SelectNum == 1)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_DECIDE);
				SetFade(MODE_END);
			}
		}
	}
}

//=========================================================================================================================
// セレクト描画処理
//=========================================================================================================================
void DrawSerect(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffSerect,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureSerect[nCount]);

		//セレクトの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
	}
}