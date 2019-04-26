//=========================================================================================================================
//
// メニューの処理 [manu.cpp]
// Author :  有馬　武志
//
//=========================================================================================================================

//*************************************************************************************************************************
// インクルードファイル
//*************************************************************************************************************************
#include "menu.h"		//メニュー
#include "input.h"		//キーボード
#include "fade.h"		//フェード
#include "game.h"		//メニュー
#include "sound.h"		//サウンド
#include "score.h"		//スコア
#include "itemcount.h"	//アイテムカウント
#include "player.h"		//プレイヤー
#include "life.h"		//ライフ

//*************************************************************************************************************************
// マクロ定義
//*************************************************************************************************************************
#define MENU_TEXTURE_MENU		"data\\TEXTURE\\ショップ.jpg"			//読み込むテクスチャファイル
#define MENU_TEXTURE_MENU0		"data\\TEXTURE\\アイテム２倍.png"		//読み込むテクスチャファイル
#define MENU_TEXTURE_MENU1		"data\\TEXTURE\\体力+1.png"				//読み込むテクスチャファイル
#define MENU_TEXTURE_MENU2		"data\\TEXTURE\\スコア加算.png"			//読み込むテクスチャファイル
#define MENU_TEXTURE_MENU3		"data\\TEXTURE\\1歩50コイン.png"		//読み込むテクスチャファイル
#define MENU_TEXTURE_MENU4		"data\\TEXTURE\\外に出る.png"			//読み込むテクスチャファイル
#define MAX_TEXTURE				(6)										//テクスチャの最大数
#define MENU_POS_X				(0)										//メニューの左上X座標
#define MENU_POS_Y				(0)										//メニューの左上Y座標
#define MENU_WIDTH				(SCREEN_WIDTH)							//メニューの幅
#define MENU_HEIGHT				(SCREEN_HEIGHT)							//メニューの高さ
#define MENU_TEXTURE_UV_U		(1.0f)									//テクスチャアニメーションU範囲
#define MENU_TEXTURE_UV_V		(1.0f)									//テクスチャアニメーションV範囲

//*************************************************************************************************************************
// グローバル変数
//*************************************************************************************************************************
LPDIRECT3DTEXTURE9 g_pTextureMenu[MAX_TEXTURE] = {};//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMenu = NULL;		 //頂点バッファへのポインタ
MENUIN g_Menu[MAX_TEXTURE];										 //ポースの情報
int g_nSelectNum;

//=========================================================================================================================
// メニュー初期化処理
//=========================================================================================================================
void InitMenu(void)
{
	//デバイスポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int nCntMenu = 0; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{//ブロックをカウント
		g_Menu[nCntMenu].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
		g_Menu[nCntMenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_Menu[nCntMenu].MenuHeight = 0;
		g_Menu[nCntMenu].MenuWidtht = 0;
		g_Menu[nCntMenu].SelectColor = 1.0f;
		g_Menu[nCntMenu].bUse = false;
		g_Menu[nCntMenu].PosMenu = 0;
	}

	g_nSelectNum = 0;

	//テクスチャの読み込み
	D3DXCreateTextureFromFile
	(//１枚目の画像
		pDevice,
		MENU_TEXTURE_MENU,
		&g_pTextureMenu[0]
	);
	D3DXCreateTextureFromFile
	(//２枚目の画像
		pDevice,
		MENU_TEXTURE_MENU0,
		&g_pTextureMenu[1]
	);
	D3DXCreateTextureFromFile
	(//３枚目の画像
		pDevice,
		MENU_TEXTURE_MENU1,
		&g_pTextureMenu[2]
	);
	D3DXCreateTextureFromFile
	(//４枚目の画像
		pDevice,
		MENU_TEXTURE_MENU2,
		&g_pTextureMenu[3]
	);
	D3DXCreateTextureFromFile
	(//５枚目の画像
		pDevice,
		MENU_TEXTURE_MENU3,
		&g_pTextureMenu[4]
	);
	D3DXCreateTextureFromFile
	(//６枚目の画像
		pDevice,
		MENU_TEXTURE_MENU4,
		&g_pTextureMenu[5]
	);


	//頂点バッファ生成
	pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX_2D) * 4 * MAX_TEXTURE,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffMenu,
		NULL
	);

	VERTEX_2D *pVtx;	//頂点情報へのポインタ

	//頂点バッファをロック
	g_pVtxBuffMenu->Lock
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
			pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//頂点カラー設定
			pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
			pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		}
		else
		{//それ以外の場合
			//1.0fで固定
			if (nCount == 1)
			{
				//頂点カラー設定
				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else
			{
				//頂点カラー設定
				pVtx[0].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
			}

		}
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		//テクスチャ設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(MENU_TEXTURE_UV_U, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, MENU_TEXTURE_UV_V);
		pVtx[3].tex = D3DXVECTOR2(MENU_TEXTURE_UV_U, MENU_TEXTURE_UV_V);

		pVtx += 4;
	}

	//頂点バッファをアンロック
	g_pVtxBuffMenu->Unlock();

	SetMenu(D3DXVECTOR3(0, 0, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 720, 1280, 0);
	SetMenu(D3DXVECTOR3(100, 350, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130,1);
	SetMenu(D3DXVECTOR3(340, 280, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130, 2);
	SetMenu(D3DXVECTOR3(540, 80, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 170, 170, 3);
	SetMenu(D3DXVECTOR3(960, 230, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 130, 130, 4);
	SetMenu(D3DXVECTOR3(SCREEN_WIDTH / 2 - 100, 590, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 250, 5);
}

//=========================================================================================================================
// メニュー終了処理
//=========================================================================================================================
void UninitMenu(void)
{
	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{//全テクスチャのカウント
		//テクスチャーの破棄
		if (g_pTextureMenu[nCount] != NULL)
		{
			g_pTextureMenu[nCount] -> Release();
			g_pTextureMenu[nCount] = NULL;
		}
	}
	//頂点バッファの破棄
	if (g_pVtxBuffMenu != NULL)
	{
		g_pVtxBuffMenu->Release();
		g_pVtxBuffMenu = NULL;
	}
}

//=========================================================================================================================
// メニュー更新処理
//=========================================================================================================================
void UpdateMenu(void)
{
	VERTEX_2D *pVtx;	// 頂点情報へのポインタ

	Player *pPlayer = GetPlayer();
	int nGetMaxCoin = GetItemCount();

	// 頂点バッファをロック
	g_pVtxBuffMenu->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);


	if (GetKeyboardTrigger(DIK_UP) == true || GetKeyboardTrigger(DIK_S) == true || GetKeyboardTrigger(DIK_A) == true )
	{//矢印キーの上を押したとき
		//メニュー移動音
		PlaySound(SOUND_LABEL_SE_MENUUPDOWN);
		// 頂点カラー設定
		g_Menu[g_nSelectNum + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_nSelectNum = (g_nSelectNum + 4) % 5;
		g_Menu[g_nSelectNum + 1].SelectColor = 1.0f;
	}
	if (GetKeyboardTrigger(DIK_DOWN) == true || GetKeyboardTrigger(DIK_W) == true || GetKeyboardTrigger(DIK_D) == true)
	{//矢印キーの下を押したとき
		//メニュー移動音
		PlaySound(SOUND_LABEL_SE_MENUUPDOWN);
		// 頂点カラー設定
		g_Menu[g_nSelectNum + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		g_nSelectNum = (g_nSelectNum + 1) % 5;
		g_Menu[g_nSelectNum + 1].SelectColor = 1.0f;
	}

	//点滅処理
	//選択しているカラーの値を減らしていく
	g_Menu[g_nSelectNum + 1].col.r -= 0.03f;
	g_Menu[g_nSelectNum + 1].col.g -= 0.03f;
	g_Menu[g_nSelectNum + 1].col.b -= 0.03f;

	if (g_Menu[g_nSelectNum + 1].col.r < 0.5f && g_Menu[g_nSelectNum + 1].col.g < 0.5f && g_Menu[g_nSelectNum + 1].col.b < 0.5f)
	{//信託しているカラーが0.5を切ったらカラーの値が増えてく
		g_Menu[g_nSelectNum + 1].col.r = 1.0f;
		g_Menu[g_nSelectNum + 1].col.g = 1.0f;
		g_Menu[g_nSelectNum + 1].col.b = 1.0f;
	}

	for (int nCntMenu = 1; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{
		// 頂点カラー設定
		pVtx[nCntMenu * 4].col = g_Menu[nCntMenu].col;
		pVtx[nCntMenu * 4 + 1].col = g_Menu[nCntMenu].col;
		pVtx[nCntMenu * 4 + 2].col = g_Menu[nCntMenu].col;
		pVtx[nCntMenu * 4 + 3].col = g_Menu[nCntMenu].col;

	}

	if (GetKeyboardTrigger(DIK_RETURN) == true)
	{
		if (g_nSelectNum == 0)
		{//メニューの０番目
			if (nGetMaxCoin - 150 > 0)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_ITEMBEY);

				//コインの枚数をひく
				AddItemCount(-150);

				//コイン２倍
				SetCoinState(GETCOIN_X2);
			}
			else
			{
				//お金が足りないとき
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 1)
		{//メニューの１番目
			if (nGetMaxCoin - 60 > 0)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_ITEMBEY);

				//コインの枚数をひく
				AddItemCount(-60);

				if (pPlayer->nLife < 3)
				{
					pPlayer->nLife += 1;
					AddLife(1, LifeTex_HIL);
				}
			}
			else
			{
				//お金が足りないとき
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 2)
		{//メニューの２番目
			if (nGetMaxCoin - 80 > 0)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_ITEMBEY);

				//コインの枚数をひく
				AddItemCount(-80);
				// スコアを加算
				AddScore(100000, SCORE_SHOP);
			}
			else
			{
				//お金が足りないとき
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 3)
		{//メニューの３番目
			if (nGetMaxCoin - 170 > 0)
			{
				//決定音
				PlaySound(SOUND_LABEL_SE_ITEMBEY);
				//コインの枚数をひく
				AddItemCount(-170);
				if (pPlayer->nLife < 3)
				{//HP3以上になった場合増えないようにする
					pPlayer->nLife += 3;
					AddLife(3, LifeTex_HIL);
				}
			}
			else
			{
				//お金が足りないとき
				PlaySound(SOUND_LABEL_SE_NOT);
			}
		}
		else if (g_nSelectNum == 4)
		{//メニューの４番目
			//決定音
			PlaySound(SOUND_LABEL_SE_ITEMBEY);
			StopSound(SOUND_LABEL_BGM004);
			SetMenuState(false);
		}
	}
	// 頂点バッファをアンロック
	g_pVtxBuffMenu->Unlock();
}

//=========================================================================================================================
// メニュー描画処理
//=========================================================================================================================
void DrawMenu(void)
{
	LPDIRECT3DDEVICE9 pDevice;		//デバイスポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource
	(
		0,
		g_pVtxBuffMenu,
		0,
		sizeof(VERTEX_2D)
	);

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < MAX_TEXTURE; nCount++)
	{
		if (g_Menu[nCount].bUse == true)
		{
			//テクスチャ設定
			pDevice->SetTexture(0, g_pTextureMenu[g_Menu[nCount].nType]);

			//メニューの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCount * 4, 2);
		}
	}
}
//============================================
//　メニューのセット
//============================================
void SetMenu(D3DXVECTOR3 pos, D3DXCOLOR col, float fHeight, float fWidth , int nType)
{
	//ブロックカウント
	int nCntMenu;

	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

	//頂点バッファをロック
	g_pVtxBuffMenu->Lock
	(
		0,
		0,
		(void**)&pVtx,
		0
	);

	for (nCntMenu = 0; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{//ブロックをカウント
		if (g_Menu[nCntMenu].bUse == false)
		{//ブロックが使用されていない場合
			g_Menu[nCntMenu].pos = pos;				//pos値代入
			g_Menu[nCntMenu].col = col;				//カラー
			g_Menu[nCntMenu].nType = nType;			//種類
			g_Menu[nCntMenu].bUse = true;			//使用している状態にする
			g_Menu[nCntMenu].MenuHeight = fHeight;	//ブロックの高さ
			g_Menu[nCntMenu].MenuWidtht = fWidth;	//ブロックの幅

			//頂点設定
			pVtx[nCntMenu * 4].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x, g_Menu[nCntMenu].pos.y, 0.0f);
			pVtx[nCntMenu * 4 + 1].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x + g_Menu[nCntMenu].MenuWidtht, g_Menu[nCntMenu].pos.y, 0.0f);
			pVtx[nCntMenu * 4 + 2].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x, g_Menu[nCntMenu].pos.y + g_Menu[nCntMenu].MenuHeight, 0.0f);
			pVtx[nCntMenu * 4 + 3].pos = D3DXVECTOR3(g_Menu[nCntMenu].pos.x + g_Menu[nCntMenu].MenuWidtht, g_Menu[nCntMenu].pos.y + g_Menu[nCntMenu].MenuHeight, 0.0f);
			//頂点カラー設定
			pVtx[nCntMenu * 4].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			pVtx[nCntMenu * 4 + 1].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			pVtx[nCntMenu * 4 + 2].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			pVtx[nCntMenu * 4 + 3].col = D3DXCOLOR(g_Menu[nCntMenu].col.r, g_Menu[nCntMenu].col.g, g_Menu[nCntMenu].col.b, g_Menu[nCntMenu].col.a);
			break;
		}
	}
	//頂点バッファをアンロック
	g_pVtxBuffMenu->Unlock();
}

//============================================
//
//============================================
void DeleteMenu(void)
{
	for (int nCntMenu = 0; nCntMenu < MAX_TEXTURE; nCntMenu++)
	{//ブロックをカウント
		if (g_Menu[nCntMenu].bUse == true)
		{//trueだったら
			g_Menu[nCntMenu].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Menu[nCntMenu].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			g_Menu[nCntMenu].MenuHeight = 0;
			g_Menu[nCntMenu].MenuWidtht = 0;
			g_Menu[nCntMenu].SelectColor = 1.0f;
			g_Menu[nCntMenu].bUse = false;
			g_Menu[nCntMenu].PosMenu = 0;
		}
	}
}