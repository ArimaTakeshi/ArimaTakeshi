////=========================================================================================================================
////
//// チュートリアルの処理 [tutorial.cpp]
//// Author :  有馬　武志
////
////=========================================================================================================================
//
////*************************************************************************************************************************
//// インクルードファイル
////*************************************************************************************************************************
//#include "main.h"
//#include "tutorial.h"
//#include "input.h"
//#include "fade.h"
//#include "sound.h"
//
////*************************************************************************************************************************
//// マクロ定義
////*************************************************************************************************************************
//#define TUTORIAL_TEXTURE_NAME		"data\\TEXTURE\\チュートリアル.png"	//読み込むテクスチャファイル
//#define TUTORIAL_POS_X				(0)								//背景の左上X座標
//#define TUTORIAL_POS_Y				(0)								//背景の左上Y座標
//#define TUTORIAL_WIDTH				(SCREEN_WIDTH)					//背景の幅
//#define TUTORIAL_HEIGHT				(SCREEN_HEIGHT)					//背景の高さ
//#define TUTORIAL_MAX				(2)								//背景の高さ
//#define TUTORIAL_TEXTURE_SPEED		(5)								//テクスチャアニメーションスピード
//#define TUTORIAL_TEXTURE_PATTERN	(10)							//テクスチャアニメーションパターン数
//#define TUTORIAL_TEXTURE_UV_U		(1.0f)							//テクスチャアニメーションU範囲
//#define TUTORIAL_TEXTURE_UV_V		(1.0f)							//テクスチャアニメーションV範囲
//#define TUTORIAL_BACKTEXTURE_UV_U	(1.0f)							//前テクスチャアニメーションU範囲
//#define TUTORIAL_BACKTEXTURE_UV_V	(1.0f)							//前テクスチャアニメーションV範囲
//#define TUTORIAL_SPEED				(0.003f)						//背景スピード
//
////*************************************************************************************************************************
//// グローバル変数
////*************************************************************************************************************************
//LPDIRECT3DTEXTURE9 g_pTextureTUTORIAL = NULL;			//テクスチャへのポインタ
//LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTUTORIAL = NULL;		//頂点バッファへのポインタ
//D3DXVECTOR3 g_posTUTORIAL;								//背景の位置
//D3DXVECTOR3 g_moveTUTORIAL;								//背景の移動
//
////=========================================================================================================================
//// 背景初期化処理
////=========================================================================================================================
//void InitTutorial(void)
//{
//	//デバイスポインタ
//	LPDIRECT3DDEVICE9 pDevice;
//
//	//デバイスの取得
//	pDevice = GetDevice();
//
//	g_posTUTORIAL = D3DXVECTOR3((TUTORIAL_POS_X + TUTORIAL_WIDTH) / 2, (TUTORIAL_POS_Y + TUTORIAL_HEIGHT) / 2, 0.0f);		//ポリゴンの中心値
//	g_moveTUTORIAL = D3DXVECTOR3(0.0f, TUTORIAL_SPEED, 0.0f);		//ポリゴン移動値
//
//														//テクスチャの読み込み
//	D3DXCreateTextureFromFile
//	(
//		pDevice,
//		TUTORIAL_TEXTURE_NAME,
//		&g_pTextureTUTORIAL
//	);
//
//	//頂点バッファ生成
//	pDevice->CreateVertexBuffer
//	(
//		sizeof(VERTEX_2D) * 4,
//		D3DUSAGE_WRITEONLY,
//		FVF_VERTEX_2D,
//		D3DPOOL_MANAGED,
//		&g_pVtxBuffTUTORIAL,
//		NULL
//	);
//
//	VERTEX_2D *pVtx;	//頂点情報へのポインタ
//
//						//頂点バッファをロック
//	g_pVtxBuffTUTORIAL->Lock
//	(
//		0,
//		0,
//		(void**)&pVtx,
//		0
//	);
//
//	//頂点設定
//	pVtx[0].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_POS_Y, 0.0f);
//	pVtx[1].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_POS_Y, 0.0f);
//	pVtx[2].pos = D3DXVECTOR3(TUTORIAL_POS_X, TUTORIAL_HEIGHT, 0.0f);
//	pVtx[3].pos = D3DXVECTOR3(TUTORIAL_WIDTH, TUTORIAL_HEIGHT, 0.0f);
//	//1.0fで固定
//	pVtx[0].rhw = 1.0f;
//	pVtx[1].rhw = 1.0f;
//	pVtx[2].rhw = 1.0f;
//	pVtx[3].rhw = 1.0f;
//	//頂点カラー設定
//	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
//	//テクスチャ設定
//	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
//	pVtx[1].tex = D3DXVECTOR2(TUTORIAL_TEXTURE_UV_U, 0.0f);
//	pVtx[2].tex = D3DXVECTOR2(0.0f, TUTORIAL_TEXTURE_UV_V);
//	pVtx[3].tex = D3DXVECTOR2(TUTORIAL_TEXTURE_UV_U, TUTORIAL_TEXTURE_UV_V);
//
//	//頂点バッファをアンロック
//	g_pVtxBuffTUTORIAL->Unlock();
//}
//
////=========================================================================================================================
//// 背景終了処理
////=========================================================================================================================
//void UninitTutorial(void)
//{
//	//テクスチャーの破棄
//	if (g_pTextureTUTORIAL != NULL)
//	{
//		g_pTextureTUTORIAL->Release();
//		g_pTextureTUTORIAL = NULL;
//	}
//	//頂点バッファの破棄
//	if (g_pVtxBuffTUTORIAL != NULL)
//	{
//		g_pVtxBuffTUTORIAL->Release();
//		g_pVtxBuffTUTORIAL = NULL;
//	}
//}
//
////=========================================================================================================================
//// 背景更新処理
////=========================================================================================================================
//void UpdateTutorial(void)
//{
//	//設定キー（ENTERキー）が押されたかどうか
//	if (GetKeyboardTrigger(DIK_RETURN) == true)
//	{
//		//決定音
//		PlaySound(SOUND_LABEL_SE_DECIDE);
//		//モード設定
//		SetFade(MODE_GAME);
//	}
//}
//
////=========================================================================================================================
//// 背景描画処理
////=========================================================================================================================
//void DrawTutorial(void)
//{
//	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ
//
//									//デバイスの取得
//	pDevice = GetDevice();
//
//	//頂点バッファをデバイスのデータストリームに設定
//	pDevice->SetStreamSource
//	(
//		0,
//		g_pVtxBuffTUTORIAL,
//		0,
//		sizeof(VERTEX_2D)
//	);
//
//	//頂点フォーマット
//	pDevice->SetFVF(FVF_VERTEX_2D);
//
//	//テクスチャ設定
//	pDevice->SetTexture(0, g_pTextureTUTORIAL);
//
//	//背景の描画
//	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
//}
