//=========================================================================================================================
//
// タイトルの処理 [tutolial.cpp]
// Author :  有馬武志　＆　加藤
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "main.h"			//メイン
#include "tutolial.h"		//チュートリアル
#include "input.h"			//入力処理
#include "fade.h"			//フェード
#include "sound.h"			//サウンド
#include "enter.h"			//エンター

//*************************************************************************************************************************
// マクロ定義
//*******************************************************w******************************************************************
#define TUTORIAL_TEXTURE_NAME  "data/TEXTURE/.png"									//読み込むテクスチャファイル
#define TUTORIAL_TEXTURE_NAME1 "data/TEXTURE/チュートリアルコントローラー版.png"	//読み込むテクスチャファイル
#define TUTORIAL_TEXTURE_NAME2 "data/TEXTURE/Tutorial2.png"							//読み込むテクスチャファイル
#define TUTORIAL_POS_X		   (300)												//チュートリアルの左上X座標
#define TUTORIAL_POS_Y		   (600)												//チュートリアルの左上Y座標
#define TUTORIAL_WIDTH		   (1000)												//チュートリアルの幅
#define TUTORIAL_HEIGHT		   (700)											    //チュートリアルの高さ
#define MAX_TEXTURE			   (3)													//テクスチャ枚数
#define MAX_TUTORIAL		   (2)													//チュートリアルの最大数

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9		g_pTextureTutorial[MAX_TEXTURE] = {};   //テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTutorial = NULL;				//頂点バッファへのポインタ
int						g_nCntTimeTutorial = 0;					//カウンター
float					g_nColor2 = 1.0f;						//指示表示の透明度
Tutorial				g_aTutorial[MAX_TUTORIAL];				//チュートリアルの情報
int						g_nPage;								//ページ数

//=========================================================================================================================
// タイトル初期化処理
//=========================================================================================================================
void InitTutolial(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
	VERTEX_2D		  *pVtx;				 //頂点情報へのポインタ
	int				  nCntTutorial;			 //チュートリアルのカウント
	int				  nInterval;			 //間隔(位置)

	//初期化
	for (nCntTutorial = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++)
	{
		g_aTutorial[nCntTutorial].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTutorial[nCntTutorial].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	g_nPage = 1; //ページの初期化

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_NAME, &g_pTextureTutorial[0]);  //指示表示
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_NAME1, &g_pTextureTutorial[1]);  //指示表示
	D3DXCreateTextureFromFile(pDevice, TUTORIAL_TEXTURE_NAME2, &g_pTextureTutorial[2]); //チュートリアル1
	
	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTutorial,
		NULL
	);

	//頂点バッファをロック
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	//指示表示の初期化
	//頂点設定
	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);

	//1.0fで固定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//テクスチャ設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//チュートリアル情報の初期化
	for (nCntTutorial = 0, nInterval = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, nInterval += SCREEN_WIDTH)
	{
		pVtx += 4;	//頂点データのポインタを4つ進める

		//頂点設定
		pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);

		//頂点カラー設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//1.0fで固定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}
	//頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();

	//エンター
	InitEnter();
}

//=========================================================================================================================
// タイトル終了処理
//=========================================================================================================================
void UninitTutolial(void)
{
	//ローカル変数宣言
	int nCntTutorial; //チュートリアルのカウント

	//テクスチャの破棄
	for (nCntTutorial = 0; nCntTutorial < MAX_TEXTURE; nCntTutorial++)
	{
		if (g_pTextureTutorial[nCntTutorial] != NULL)
		{
			g_pTextureTutorial[nCntTutorial]->Release();
			g_pTextureTutorial[nCntTutorial] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTutorial != NULL)
	{
		g_pVtxBuffTutorial->Release();
		g_pVtxBuffTutorial = NULL;
	}

	//エンター
	UninitEnter();
}

//=========================================================================================================================
// タイトル更新処理
//=========================================================================================================================
void UpdateTutolial(void)
{
	FADE pFade = GetFade();

	//ローカル変数宣言
	VERTEX_2D *pVtx;			  //頂点情報へのポインタ
	int		  nCntTutorial;		  //チュートリアルのカウント
	int		  nInterval;		  //間隔(位置)

	g_nCntTimeTutorial++; //時間のカウント

	//頂点バッファをロック
	g_pVtxBuffTutorial->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nCntTimeTutorial % 10) == 0) //10フレーム毎
	{//一定時間で指示表示の点滅
		g_nColor2 -= 0.05f;

		if (g_nColor2 <= 0.2f)
		{//元に戻す
			g_nColor2 = 1.0f;
		}
	}

	//頂点カラー設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_nColor2);

	//ページの進むor戻る
	if (GetKeyboardTrigger(DIK_RIGHT) == true && g_nPage < 2 || GetJoyPadTrigger(DIJS_BUTTON_12, 0) == true && g_nPage < 2)
	{//次のページへ進む
		for (nCntTutorial = 0, nInterval = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, nInterval += SCREEN_WIDTH)
		{
			
			g_aTutorial[nCntTutorial].move.x = -SCREEN_WIDTH;

			//位置を更新(移動)
			g_aTutorial[nCntTutorial].pos.x += g_aTutorial[nCntTutorial].move.x;
			g_aTutorial[nCntTutorial].pos.y += g_aTutorial[nCntTutorial].move.y;

			pVtx += 4;	//頂点データのポインタを4つ進める

			//頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
		}

		g_nPage += 1; //ページを進める
	}
	else if (GetKeyboardTrigger(DIK_LEFT) == true && g_nPage > 1 || GetJoyPadTrigger(DIJS_BUTTON_13, 0) == true && g_nPage > 1)
	{//前のページへ戻る
		for (nCntTutorial = 0, nInterval = 0; nCntTutorial < MAX_TUTORIAL; nCntTutorial++, nInterval += SCREEN_WIDTH)
		{
			g_aTutorial[nCntTutorial].move.x = SCREEN_WIDTH;

			//位置を更新(移動)
			g_aTutorial[nCntTutorial].pos.x += g_aTutorial[nCntTutorial].move.x;
			g_aTutorial[nCntTutorial].pos.y += g_aTutorial[nCntTutorial].move.y;

			pVtx += 4;	//頂点データのポインタを4つ進める

						//頂点設定
			pVtx[0].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aTutorial[nCntTutorial].pos.x + SCREEN_WIDTH + nInterval, g_aTutorial[nCntTutorial].pos.y + SCREEN_HEIGHT, 0.0f);
		}

		g_nPage -= 1; //ページを戻す
	}

	//頂点バッファをアンロック
	g_pVtxBuffTutorial->Unlock();

	if (pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) == true || GetJoyPadTrigger(3, 0) == true)
		{
			//決定音
			PlaySound(SOUND_LABEL_SE_DECIDE);
			//モード設定
			SetFade(MODE_GAME);
		}
	}

	//エンター
	UpdateEnter();
}

//=========================================================================================================================
// タイトル描画処理
//=========================================================================================================================
void DrawTutolial(void)
{
	//ローカル変数宣言
	LPDIRECT3DDEVICE9 pDevice = GetDevice(); //デバイスの取得
	int				  nCntTutorial;			 //チュートリアルのカウント

	 //頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTutorial, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTutorial = 0; nCntTutorial < MAX_TEXTURE; nCntTutorial++)
	{
		//テクスチャ設定
		pDevice->SetTexture(0, g_pTextureTutorial[nCntTutorial]);

		//チュートリアルの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTutorial * 4, 2);
	}
	//エンター
	DrawEnter();
}