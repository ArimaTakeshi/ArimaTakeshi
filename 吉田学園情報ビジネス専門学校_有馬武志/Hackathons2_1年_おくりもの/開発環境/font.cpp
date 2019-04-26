//=========================================================================================================//
//
// 背景処理 [bg.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define MAX_FONT			(16)
#define SETFONT_WIDE		(SCREEN_WIDTH * 0.35)
#define SETFONT_HEIGHT		(SCREEN_HEIGHT * 0.4)
#define Font_TextureName	"data/TEXTURE/50on.jpg"		//50音表

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9 g_pTextureFont = NULL;		//テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffFont = NULL;	//頂点BUFFERへのポインタ
LPD3DXFONT			g_pFont0 = NULL;			// フォントへのポインタ
Font				g_Font[MAX_FONT];
int					g_nSetFont = 0;
//=========================================================================================================//
// 初期化処理
//=========================================================================================================//
void InitFont(void)
{
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		//g_Font[nCntFont].rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
		g_Font[nCntFont].bUse = false;
	}

	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXCreateTextureFromFile(pDevice, Font_TextureName, &g_pTextureFont);	//タイトル

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffFont,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);		//X,Y,0.0f
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f - SETFONT_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f - SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f + SETFONT_WIDE, SCREEN_HEIGHT * 0.5f + SETFONT_HEIGHT, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//カラー設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// A = 透明度
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//テクスチャ座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.5f);

	//頂点BUFFERをアンロックする
	g_pVtxBuffFont->Unlock();

	D3DXCreateFont(pDevice, 40, 12, 0, 0, FALSE, ARABIC_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont0);
}
//=========================================================================================================//
// 終了処理
//=========================================================================================================//
void UninitFont(void)
{
	if (g_pFont0 != NULL)
	{// デバッグ表示用フォントの開放
		g_pFont0->Release();
		g_pFont0 = NULL;
	}
}
//=========================================================================================================//
// 更新処理
//=========================================================================================================//
void UpdateFont(void)
{
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_Font[nCntFont].bUse == true)
		{//文字が表示状態なら
			switch (g_Font[nCntFont].state)
			{
			case FONTSTATE_DELETE:
				g_Font[nCntFont].rect.bottom -= 2;
				g_Font[nCntFont].rect.top -= 2;
				g_Font[nCntFont].fCntState++;
				if (g_Font[nCntFont].fCntState > 20) { g_Font[nCntFont].bUse = false; }
				break;
			}
		}
	}
}

//=========================================================================================================//
// 描画処理
//=========================================================================================================//
void DrawFont(void)
{
	int nCntFont;
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	
	if (g_nSetFont != 0)
	{//50音表表示
		VERTEX_2D *pVtx;		//頂点情報へのポインタ
		//頂点BUFFERをロックし、頂点情報へのポインタを取得
		g_pVtxBuffFont->Lock(0, 0, (void**)&pVtx, 0);

		//テクスチャ座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, (g_nSetFont - 1.0f) * 0.5f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, (g_nSetFont - 1.0f) * 0.5f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, g_nSetFont * 0.5f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, g_nSetFont * 0.5f);

		//頂点BUFFERをアンロックする
		g_pVtxBuffFont->Unlock();

		LPDIRECT3DDEVICE9 pDevice;
		//デバイスを取得する
		pDevice = GetDevice();


		//頂点BUFFERをデバイスのデータストリームに設定
		pDevice->SetStreamSource(0, g_pVtxBuffFont, 0, sizeof(VERTEX_2D));

		pDevice->SetFVF(FVF_VERTEX_2D);	// 頂点フォーマットの設定

										//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureFont);
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	// テキスト描画
	// hDC      : デバイスコンテキストのハンドル
	// lpString : 描画する文字列へのポインタ
	// nCount   : 文字列の文字数
	// lpRect   : 長方形領域
	// uFormat  : テキストの整形方法を指定
	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_Font[nCntFont].bUse == true)
		{// 文字列を代入 表示
			/*D3DXCreateFont(pDevice, g_Font[nCntFont].nHeight, g_Font[nCntFont].nWide, 0, 0, FALSE, ARABIC_CHARSET,
				OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Font", &g_pFont0);*/
			g_pFont0->DrawText(NULL, &g_Font[nCntFont].aStr[0], -1, &g_Font[nCntFont].rect, DT_LEFT, g_Font[nCntFont].col);
		}
	}
}
//=========================================================================================================//
// 文字代入処理  Set!!
//=========================================================================================================//
void SetFont(RECT rect, D3DCOLOR col, char *aStr, int nNumber, int nWide, int nHeight, FONTSTATE state)
{//文字セット
	g_Font[nNumber].bUse = true;
	g_Font[nNumber].state = state;
	g_Font[nNumber].nWide = nWide;
	g_Font[nNumber].nHeight = nHeight;
	g_Font[nNumber].rect = rect;
	strcpy(&g_Font[nNumber].aStr[0], &aStr[0]);
	g_Font[nNumber].col = col;
	g_Font[nNumber].fCntState = 0;
}
//=========================================================================================================//
// 文字代入処理  Set!!
//=========================================================================================================//
void SetFontDamage(RECT rect, D3DCOLOR col, char *aStr, int nWide, int nHeight, FONTSTATE state)
{//文字セット
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		if (g_Font[nCntFont].bUse == false)
		{
			g_Font[nCntFont].bUse = true;
			g_Font[nCntFont].nWide = nWide;
			g_Font[nCntFont].nHeight = nHeight;
			g_Font[nCntFont].state = state;
			g_Font[nCntFont].rect = rect;
			strcpy(&g_Font[nCntFont].aStr[0], &aStr[0]);
			g_Font[nCntFont].col = col;
			g_Font[nCntFont].fCntState = 0;
			break;
		}
	}

}
//=========================================================================================================//
// 文字代入処理  Change!!
//=========================================================================================================//
void ChangeFont(bool bUse, char *aStr, int nNumber, FONTSTATE state, D3DCOLOR col)
{//セットされたものを変更
	g_Font[nNumber].bUse = bUse;
	g_Font[nNumber].state = state;
	g_Font[nNumber].col = col;
	if(aStr[0] != NULL) { strcpy(&g_Font[nNumber].aStr[0], &aStr[0]); }//NULLじゃなければ更新
}
//=========================================================================================================//
// 文字を全て破壊
//=========================================================================================================//
void BreakFont(void)
{//セットされた文字をすべて破壊
	int nCntFont;

	for (nCntFont = 0; nCntFont < MAX_FONT; nCntFont++)
	{
		g_Font[nCntFont].bUse = false;
	}

}
//=========================================================================================================//
// セットされている50音の取得
//=========================================================================================================//
int *GetSetFont(void)
{
	return &g_nSetFont;
}
//=========================================================================================================//
// * 全Animationスクロール処理
//=========================================================================================================//
void FontScroll(D3DXVECTOR3 move)
{
	int nCntItem;

	for (nCntItem = 0; nCntItem < MAX_FONT; nCntItem++)
	{
		if (g_Font[nCntItem].bUse == true && g_Font[nCntItem].state == FONTSTATE_DELETE)
		{//スクロール
			g_Font[nCntItem].rect.top += (int)move.y;
			g_Font[nCntItem].rect.bottom += (int)move.y;
			g_Font[nCntItem].rect.left += (int)move.x;
			g_Font[nCntItem].rect.right += (int)move.x;
		}
	}
}