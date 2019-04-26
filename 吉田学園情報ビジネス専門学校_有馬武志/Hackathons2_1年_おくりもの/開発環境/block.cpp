//=========================================================================================================//
//
// window処理 [window.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "enemy.h"
#include "fade.h"
#include "sound.h"

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define BLOCK_VERTEX_NUM			(4)								// 頂点の数
#define BLOCK_PRIMITIVE_NUM			(2)								// プリミティブの数
#define BLOCK_MAX_TEXTURE			(8)
#define BLOCK_TextureName0		"data/TEXTURE/BlueRoof.jpg"			//レンガ
#define BLOCK_TextureName1		"data/TEXTURE/YellowRoof.jpg"		//すり抜け床
#define BLOCK_TextureName2		"data/TEXTURE/RedRoof.jpg"		//レンガ 背景
#define BLOCK_TextureName3		"data/TEXTURE/Chimney.jpg"		//石
#define BLOCK_TextureName4		"data/TEXTURE/GreenRoof.jpg"		//石
#define BLOCK_TextureName5		"data/TEXTURE/cloud.png"		//石
#define BLOCK_TextureName6		"data/TEXTURE/Stone.png"		//石
#define BLOCK_TextureName7		"data/TEXTURE/Ruins-2.png"		//石
#define	MAX_BLOCK			(1024)		// windowの最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posold;		//位置
	D3DXVECTOR3 move;		//移動量
	D3DXCOLOR col;			//色
	int nLengthX;			//横幅
	int nLengthY;			//高さ
	int nType;				//画像
	float fSpeed;			//SPEED
	float fmoveSteep;		//移動方向の角度
	float fCurve;			//毎回加算するカーブ値
	BLOCKSTATE state;		//
	int nCounterState[2];	//エネミーの状態管理用
	float fSteep;
	bool bUse;
}BLOCK;

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9		g_pTextureBlock[BLOCK_MAX_TEXTURE] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ
BLOCK					g_aBlock[MAX_BLOCK];
float					g_ScrollWide;
float					g_ScrollHeight;

//=========================================================================================================//
// * 背景の描画処理1	初期化処理
//=========================================================================================================//
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntWindow;

	// 弾の情報の初期化
	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		//g_aWindow[nCntWindow].pos = { 0.0f, 0.0f, 0.0f };
		//g_aWindow[nCntWindow].nLengthX = 0;
		//g_aWindow[nCntWindow].nLengthY = 0;
		//g_aWindow[nCntWindow].nType = 0;
		//g_aWindow[nCntWindow].col = { 1.0f, 1.0f, 1.0f, };
		g_aBlock[nCntWindow].bUse = false;
	}
	g_ScrollWide = 0.0f;
	g_ScrollHeight = 0.0f;

	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName0, &g_pTextureBlock[0]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName1, &g_pTextureBlock[1]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName2, &g_pTextureBlock[2]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName3, &g_pTextureBlock[3]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName4, &g_pTextureBlock[4]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName5, &g_pTextureBlock[5]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName6, &g_pTextureBlock[6]);
	D3DXCreateTextureFromFile(pDevice, BLOCK_TextureName7, &g_pTextureBlock[7]);

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * BLOCK_VERTEX_NUM * MAX_BLOCK,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffBlock,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		//頂点座標の設定
		//pVtx[nCntWindow * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

		pVtx[nCntWindow * 4].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 1].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 2].rhw = 1.0f;
		pVtx[nCntWindow * 4 + 3].rhw = 1.0f;

		//カラー設定
		//pVtx[nCntWindow * 4].col = D3DCOLOR_RGBA(0, 0, 0, 255);	// A = 透明度
		//pVtx[nCntWindow * 4 + 1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		//pVtx[nCntWindow * 4 + 2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		//pVtx[nCntWindow * 4 + 3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

		////テクスチャ座標設定
		//pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 20.0f) * 1.0f, 0.0f);
		//pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, (g_aBlock[nCntWindow].nLengthY / 20.0f) * 1.0f);
		//pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 20.0f) * 1.0f, (g_aBlock[nCntWindow].nLengthY / 20.0f) * 1.0f);
	}

	//頂点BUFFERをアンロックする
	g_pVtxBuffBlock->Unlock();
}
//=========================================================================================================//
// * 背景の描画処理2	終了処理
//=========================================================================================================//
void UninitBlock(void)
{//テクスチャの破棄
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < BLOCK_MAX_TEXTURE; nCntTexture++)
	{
		if (g_pTextureBlock[nCntTexture] != NULL)
		{
			g_pTextureBlock[nCntTexture]->Release();
			g_pTextureBlock[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
}
//=========================================================================================================//
// * 背景の描画処理3	更新処理
//=========================================================================================================//
void UpdateBlock(void)
{
	int nCntBlock;
	PLAYER *pPlayer = GetPlayer();

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//全ウィンドウ文回る
		if (g_aBlock[nCntBlock].bUse == true)
		{//使っていたら
			g_aBlock[nCntBlock].posold = g_aBlock[nCntBlock].pos;
			g_aBlock[nCntBlock].fmoveSteep += g_aBlock[nCntBlock].fCurve;
			g_aBlock[nCntBlock].move += D3DXVECTOR3(sinf(g_aBlock[nCntBlock].fmoveSteep), cosf(g_aBlock[nCntBlock].fmoveSteep), 0.0f) * g_aBlock[nCntBlock].fSpeed;
			g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;
			g_aBlock[nCntBlock].move.x += (0.0f - g_aBlock[nCntBlock].move.x) * 0.12f;
			g_aBlock[nCntBlock].move.y += (0.0f - g_aBlock[nCntBlock].move.y) * 0.12f;
			switch (g_aBlock[nCntBlock].state)
			{
			case BLOCKSTATE_FADE:
				if (pPlayer[0].pos.x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - PLAYER_CollisionX && pPlayer[0].pos.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + PLAYER_CollisionX &&
					pPlayer[0].pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - PLAYER_CollisionY + 1 && pPlayer[0].pos.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + PLAYER_CollisionY - 1)
				{//範囲内なら
					g_aBlock[nCntBlock].col.a -= 0.1f;
					if (g_aBlock[nCntBlock].col.a < 0.0f) { g_aBlock[nCntBlock].col.a = 0.0f; }
				}
				else
				{//範囲外なら
					g_aBlock[nCntBlock].col.a += 0.002f;
					if (g_aBlock[nCntBlock].col.a >= 1.0f) { g_aBlock[nCntBlock].col.a = 1.0f; }
				}
				break;
			}
		}
	}
	//頂点BUFFERをアンロックする
	g_pVtxBuffBlock->Unlock();

	SettingPlayer();
}
//=========================================================================================================//
// * 背景の描画処理4	描画処理
//=========================================================================================================//
void DrawBlock(bool bBG)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntWindow;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, PRIMITIVE_NUM);
	// ポリゴンの描画
	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		if (bBG == false && g_aBlock[nCntWindow].state != BLOCKSTATE_FADE)
		{
			if (g_aBlock[nCntWindow].bUse == true && g_aBlock[nCntWindow].pos.x - g_aBlock[nCntWindow].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntWindow].pos.x + g_aBlock[nCntWindow].nLengthX >= 0 && g_aBlock[nCntWindow].pos.y - g_aBlock[nCntWindow].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntWindow].pos.y + g_aBlock[nCntWindow].nLengthY >= 0)
			{// テクスチャの設定
				SettingBlock();
				pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntWindow].nType]);
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWindow * 4, BLOCK_PRIMITIVE_NUM);
			}
		}
		else if(bBG == true && g_aBlock[nCntWindow].state == BLOCKSTATE_FADE)
		{
			if (g_aBlock[nCntWindow].bUse == true && g_aBlock[nCntWindow].pos.x - g_aBlock[nCntWindow].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntWindow].pos.x + g_aBlock[nCntWindow].nLengthX >= 0 && g_aBlock[nCntWindow].pos.y - g_aBlock[nCntWindow].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntWindow].pos.y + g_aBlock[nCntWindow].nLengthY >= 0)
			{// テクスチャの設定
				SettingBlock();
				pDevice->SetTexture(0, g_pTextureBlock[g_aBlock[nCntWindow].nType]);
				pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntWindow * 4, BLOCK_PRIMITIVE_NUM);
			}
		}
	}

	//頂点BUFFERをアンロックする
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void SettingBlock(void)
{
	int nCntWindow;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		if (g_aBlock[nCntWindow].nType == 5) { g_aBlock[nCntWindow].nLengthY += 50; }
		else { g_aBlock[nCntWindow].nLengthY += 30; }
		//頂点座標の設定
		pVtx[nCntWindow * 4].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		pVtx[nCntWindow * 4 + 1].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		pVtx[nCntWindow * 4 + 2].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) + (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		pVtx[nCntWindow * 4 + 3].pos = D3DXVECTOR3(g_aBlock[nCntWindow].pos.x - (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX), g_aBlock[nCntWindow].pos.y + (sinf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthX) - (cosf(g_aBlock[nCntWindow].fSteep) * g_aBlock[nCntWindow].nLengthY), 0.0f);
		if (g_aBlock[nCntWindow].nType == 5) { g_aBlock[nCntWindow].nLengthY -= 50; }
		else { g_aBlock[nCntWindow].nLengthY -= 30; }


		//テクスチャ座標設定
		if (g_aBlock[nCntWindow].state == BLOCKSTATE_THIN0 || g_aBlock[nCntWindow].state == BLOCKSTATE_THIN1 || g_aBlock[nCntWindow].state == BLOCKSTATE_THIN2)
		{
			pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
		else
		{
			pVtx[nCntWindow * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[nCntWindow * 4 + 1].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 100.0f) * 1.0f, 0.0f);
			pVtx[nCntWindow * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[nCntWindow * 4 + 3].tex = D3DXVECTOR2((g_aBlock[nCntWindow].nLengthX / 100.0f) * 1.0f,1.0f);
		}
		//カラー設定
		pVtx[nCntWindow * 4].col = g_aBlock[nCntWindow].col;// A = 透明度
		pVtx[nCntWindow * 4 + 1].col = g_aBlock[nCntWindow].col;
		pVtx[nCntWindow * 4 + 2].col = g_aBlock[nCntWindow].col;
		pVtx[nCntWindow * 4 + 3].col = g_aBlock[nCntWindow].col;
	}
	//頂点BUFFERをアンロックする
	g_pVtxBuffBlock->Unlock();
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void SetBlock(D3DXVECTOR3 pos, D3DXCOLOR col, int nLengthX, int nLengthY, int nType, float fSteep, float fCurve, float fmoveSteep, float fSpeed, BLOCKSTATE state)
{
	int nCntWindow;

	for (nCntWindow = 0; nCntWindow < MAX_BLOCK; nCntWindow++)
	{
		if (g_aBlock[nCntWindow].bUse == false)
		{
			g_aBlock[nCntWindow] = { pos, pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), col, nLengthX, nLengthY, nType, fSpeed, fmoveSteep, fCurve, state, {0,0},fSteep, true };
			break;
		}
	}
}
//=============================================================================
// ブロックとの衝突判定
//=============================================================================
bool CollisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosold, D3DXVECTOR3 *pMove, float *fRide, bool bRide, PLAYERSTATE *state, int nLengthX, int nLengthY, int nCntEnemy, USETYPE type)
{
	int nCntBlock;
	int nLength;

	bool bJump = false;
	bool bWall = false;
	PLAYER *pPlayer = GetPlayer();

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//上下の判定
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN0&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN1&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN2)
		{//使われているブロック && 判定付きのブロックなら
				if (g_aBlock[nCntBlock].posold.y - g_aBlock[nCntBlock].nLengthY >= pPosold[0].y + nLengthY && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= pPos[0].y + nLengthY)
				{//前回が上&&判定上
					if (state[0] != PLAYERSTATE_FALL || g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
					{
						nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
						if (nLength < 0) { nLength *= -1; }
						nLength -= nLengthX;
						if (nLength <= g_aBlock[nCntBlock].nLengthX)
						{
							if (g_aBlock[nCntBlock].state == BLOCKSTATE_OUT && type == USETYPE_PLAYER) { SetFade(MODE_RESULT, 0); }	//自機を殺す
							else if (g_aBlock[nCntBlock].state == BLOCKSTATE_OUT && type == USETYPE_ENEMY) {  }//敵を殺す
							else
							{
								pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY;
								pMove[0].y = 0.0f;
								bJump = true;
								if (bRide == true) { *fRide += g_aBlock[nCntBlock].move.x; }
								if (g_aBlock[nCntBlock].state == BLOCKSTATE_CLEAR && pPlayer[0].nClear == 0) { pPlayer[0].nClear = 1; }
							}
						}
					}
				}
				//else if (g_aBlock[nCntBlock].posold.y + g_aBlock[nCntBlock].nLengthY <= pPosold[0].y - nLengthY && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= pPos[0].y - nLengthY && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
				//{//前回が下&&判定下 
				//	nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
				//	if (nLength < 0) { nLength *= -1; }
				//	nLength -= nLengthX;
				//	if (nLength <= g_aBlock[nCntBlock].nLengthX)
				//	{
				//		pPos[0].y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + nLengthY;
 			//			pMove[0].y = 0.0f;
				//	}
				//}
		}
	}

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//右左の判定
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_BOARD && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN0&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN1&& g_aBlock[nCntBlock].state != BLOCKSTATE_THIN2)
		{//使われているブロック && 判定付きのブロックなら
				if (g_aBlock[nCntBlock].posold.x + g_aBlock[nCntBlock].nLengthX <= pPosold[0].x - nLengthX && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= pPos[0].x - nLengthX)
				{//前回が右&&判定右
					nLength = (int)pPos[0].y - (int)g_aBlock[nCntBlock].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= nLengthY;
					if (nLength < g_aBlock[nCntBlock].nLengthY)
					{
						pPos[0].x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + nLengthX + 1.0f;
						pMove[0].x = 0.0f;
						bWall = true;
					}
				}
				if (g_aBlock[nCntBlock].posold.x - g_aBlock[nCntBlock].nLengthX >= pPosold[0].x + nLengthX && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= pPos[0].x + nLengthX)
				{//前回が左&&判定左
					nLength = (int)pPos[0].y - (int)g_aBlock[nCntBlock].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= nLengthY;
					if (nLength < g_aBlock[nCntBlock].nLengthY)
					{
						pPos[0].x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - nLengthX - 1.0f;
						pMove[0].x = 0.0f;
						bWall = true;
					}
				}
		}
	}

	if (bWall == true && bJump == false && type == USETYPE_PLAYER)
	{//上下が通らず横のみ通った場合の貫通防止として
		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{//上下の判定
			if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= 0 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= 0 && 
				g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_BOARD)
			{//使われているブロック && 判定付きのブロックなら
					if (g_aBlock[nCntBlock].posold.y - g_aBlock[nCntBlock].nLengthY >= pPosold[0].y + nLengthY && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= pPos[0].y + nLengthY)
					{//前回が上&&判定上
						if (state[0] != PLAYERSTATE_FALL || g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
						{
							nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
							if (nLength < 0) { nLength *= -1; }
							nLength -= nLengthX;
							if (nLength <= g_aBlock[nCntBlock].nLengthX)
							{
								pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY;
								pMove[0].y = 0.0f;
								bJump = true;
							}
						}
					}
					else if (g_aBlock[nCntBlock].posold.y + g_aBlock[nCntBlock].nLengthY <= pPosold[0].y - nLengthY && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= pPos[0].y - nLengthY && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN)
					{//前回が下&&判定下
						nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
						if (nLength < 0) { nLength *= -1; }
						nLength -= nLengthX;
						if (nLength <= g_aBlock[nCntBlock].nLengthX)
						{
							pPos[0].y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + nLengthY;
							pMove[0].y = 0.0f;
						}
					}
			}
		}
	}

	//if (bJump == false && type == USETYPE_PLAYER)
	//{//着地できていない場合　崖つかまり確認
	//	PLAYER *pPlayer = GetPlayer();
	//	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//	{//上下の判定
	//		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= 0 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= 0 &&
	//			g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BREAK && g_aBlock[nCntBlock].state != BLOCKSTATE_BG && g_aBlock[nCntBlock].state != BLOCKSTATE_THIN && g_aBlock[nCntBlock].state != BLOCKSTATE_BOARD)
	//		{//使われているブロック && 判定付きのブロックなら
	//			if (g_aBlock[nCntBlock].posold.y - g_aBlock[nCntBlock].nLengthY >= pPosold[0].y - 15 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= pPos[0].y - 15)
	//			{//前回が上&&判定上
	//				nLength = (int)pPos[0].x - (int)g_aBlock[nCntBlock].pos.x;
	//				if (pPlayer[0].nAngle == PLAYERANGLE_LEFT)
	//				{//左向きなら
	//					nLength -= nLengthX + 1;
	//					if (nLength == g_aBlock[nCntBlock].nLengthX)
	//					{//長さが同じなら
	//						pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY + 15;
	//						pMove[0].y = 0.0f;
	//						state[0] = PLAYERSTATE_CATCH;
	//					}
	//				}
	//				else
	//				{//右向きなら
	//					nLength += nLengthX + 1;
	//					if (nLength == -g_aBlock[nCntBlock].nLengthX)
	//					{//長さが同じなら
	//						pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY + 15;
	//						pMove[0].y = 0.0f;
	//						state[0] = PLAYERSTATE_CATCH;
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	return bJump;
}
//=========================================================================================================//
// * 弾の当たり判定
//=========================================================================================================//
bool HitBullet(Bullet pBullet)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntBlock;
	int nScore = 0;
	float fLength[2];
	float fPercent = 1.0f;		//弾の長さの倍率
	bool bHit = false;
	if (pBullet.nShot != BULLETTYPE_EFFECT)
	{
		if (pBullet.state == BULLETSTATE_NONE) { fPercent = 0.5f; }
		fLength[0] = (sinf(pBullet.steep) * pBullet.nLengthX + sinf(pBullet.steep) * pBullet.nLengthY) * fPercent;	//弾の横の長さ
		fLength[1] = (cosf(pBullet.steep) * pBullet.nLengthX + cosf(pBullet.steep) * pBullet.nLengthY) * fPercent;	//弾の縦の長さ
		if (fLength[0] < 0) { fLength[0] *= -1; }
		if (fLength[1] < 0) { fLength[1] *= -1; }

		for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
		{
			if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG)
			{
				if (pBullet.pos.x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - fLength[0] && pBullet.pos.x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + fLength[0] &&
					pBullet.pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - fLength[1] && pBullet.pos.y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + fLength[1])
				{
					if (g_aBlock[nCntBlock].state == BLOCKSTATE_BREAK)
					{//壊れる
						bHit = true;
						g_aBlock[nCntBlock].bUse = false;
						SetExplosion(g_aBlock[nCntBlock].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), g_aBlock[nCntBlock].nLengthX * 2, g_aBlock[nCntBlock].nLengthY * 2, 5, 1, 2, 2, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
					}
					else if (pBullet.state == BULLETSTATE_GRAVITY)
					{//煙突の場合 && 重力付きプレゼントの場合
						if (g_aBlock[nCntBlock].state == BLOCKSTATE_THIN0 && pBullet.posold.y < g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - fLength[1] && pBullet.pos.y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - fLength[1])
						{//スコア+
							PlaySound(SOUND_LABEL_ATTACK002);
							g_aBlock[nCntBlock].state = BLOCKSTATE_THIN2;
							if (pBullet.nType == 0) { nScore = 3000; }
							if (pBullet.nType == 1) { nScore = 8000; }
							if (pBullet.nType == 2) { nScore = 500; }
							if (pBullet.nType == 3) { nScore = 1200; }
							pPlayer[0].nScore += nScore;
							SetDigital(g_aBlock[nCntBlock].pos - D3DXVECTOR3(0.0f, g_aBlock[nCntBlock].nLengthY * 1.0f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_WAVE, 30, 45, nScore);
							SetExplosion(g_aBlock[nCntBlock].pos - D3DXVECTOR3(0.0f, g_aBlock[nCntBlock].nLengthY * 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
							bHit = true;
						}
					}
					else if(g_aBlock[nCntBlock].state == BLOCKSTATE_THIN0 &&g_aBlock[nCntBlock].state == BLOCKSTATE_THIN1 && g_aBlock[nCntBlock].state == BLOCKSTATE_THIN2){ bHit = true; }
					
				}
			}
		}
	}
	return bHit;
}
//=============================================================================
// ブロックとの衝突判定 バグ回避(誤魔化し)用
//=============================================================================
bool SafetynBlock(D3DXVECTOR3 *pPos, int nLengthX, int nLengthY)
{
	int nCntBlock;
	bool bJump;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{//全ブロック数回る
		if (g_aBlock[nCntBlock].bUse == true && g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX <= SCREEN_WIDTH && g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX >= 0 && g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY <= SCREEN_HEIGHT && g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY >= 0 &&
			g_aBlock[nCntBlock].state != BLOCKSTATE_THIN && g_aBlock[nCntBlock].state != BLOCKSTATE_FADE && g_aBlock[nCntBlock].state != BLOCKSTATE_BG)
		{//判定のあるブロックのみ
			if (pPos[0].x < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].nLengthX + nLengthX && pPos[0].x > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].nLengthX - nLengthX&&
				pPos[0].y < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].nLengthY + nLengthY && pPos[0].y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY)
			{//ポリゴンの中に入り込んでしまった場合
				pPos[0].y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].nLengthY - nLengthY;
				MessageBox(0, "", "", MB_OK);
				bJump = true;
			}
		}

	}

	return bJump;
}
//=============================================================================
// window破壊処理
//=============================================================================
void BreakBlock(void)
{//全ウィンドウ破棄
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{
			g_aBlock[nCntBlock].bUse = false;
		}
	}
}
//=========================================================================================================//
// * 横スクロール
//=========================================================================================================//
void WideScroll(void)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntBlock;
	float fPlayerPosx = 1.0f;
	float fPlayerPosy = 0.0f;
	D3DXVECTOR3 move;
	D3DXVECTOR3 data;
	bool PlayerMove = false;

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//横スクロール
	//if (SCREEN_WIDTH * 0.4f > pPlayer[0].pos.x || SCREEN_WIDTH * 0.6f < pPlayer[0].pos.x) { fPlayerPosx = 1.0f; }
	//else if (SCREEN_WIDTH * 0.5f > pPlayer[0].pos.x || SCREEN_WIDTH * 0.5f < pPlayer[0].pos.x) { fPlayerPosx = 0.8f; }
	//else if (SCREEN_WIDTH * 0.6f > pPlayer[0].pos.x || SCREEN_WIDTH * 0.4f < pPlayer[0].pos.x) { fPlayerPosx = 0.5f; }
	//if (SCREEN_WIDTH * 0.4f < pPlayer[0].pos.x && pPlayer[0].nAngle == PLAYERANGLE_RIGHT) { g_ScrollWide -= 0.2f; }
	//if (SCREEN_WIDTH * 0.6f > pPlayer[0].pos.x && pPlayer[0].nAngle == PLAYERANGLE_LEFT) { g_ScrollWide += 0.2f; }

	////縦スクロール
	//	if (SCREEN_HEIGHT * 0.35f < pPlayer[0].pos.y && pPlayer[0].state == PLAYERSTATE_DOWN && pPlayer[0].nCntState[1] > 30) { g_ScrollHeight -= 0.6f; }
	//	else if (SCREEN_HEIGHT * 0.8f < pPlayer[0].pos.y && pPlayer[0].move.y > 0) { fPlayerPosy = 1.0f; }
	//	else if (SCREEN_HEIGHT * 0.7f < pPlayer[0].pos.y && pPlayer[0].move.y > 0) { fPlayerPosy = 0.8f; }
	//	else if (SCREEN_HEIGHT * 0.65f < pPlayer[0].pos.y) { g_ScrollHeight -= 0.5f; }
	//	if (SCREEN_HEIGHT * 0.1f > pPlayer[0].pos.y && pPlayer[0].move.y < 0) { fPlayerPosy = 1.0f; }
	//	else if (SCREEN_HEIGHT * 0.3f > pPlayer[0].pos.y && pPlayer[0].move.y < 0) { fPlayerPosy = 0.8f; }
	//	else if (SCREEN_HEIGHT * 0.45f > pPlayer[0].pos.y && pPlayer[0].state != PLAYERSTATE_DOWN) { g_ScrollHeight += 0.5f; }

	move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//スクロール
			g_aBlock[nCntBlock].pos += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f);
			g_aBlock[nCntBlock].posold += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f);

		}
	} 
	BulletScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	ExplosionScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	FontScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	BGScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	AnimationScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	EnemyScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));
	DigitalScroll(D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f));

	pPlayer[0].pos += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight, 0.0f);
	pPlayer[0].posold += D3DXVECTOR3(move.x * fPlayerPosx + g_ScrollWide, move.y * fPlayerPosy + g_ScrollHeight - 1.0f, 0.0f);

	SettingPlayer();
	//pPlayer[0].posold = pPlayer[0].pos;

	g_ScrollWide += (0.0f - g_ScrollWide) * 0.07f;
	g_ScrollHeight += (0.0f - g_ScrollHeight) * 0.2f;

	//頂点BUFFERをアンロックする
	g_pVtxBuffBlock->Unlock();

	//SettingPlayer();
}
//=========================================================================================================//
// * 横スクロール
//=========================================================================================================//
void InitScroll(void)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntBlock;

	for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//スクロール
			g_aBlock[nCntBlock].pos -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
			g_aBlock[nCntBlock].posold -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
		}
	}
	pPlayer[0].pos -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
	pPlayer[0].posold -= pPlayer[0].respawn - D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f);
	AnimationScroll(pPlayer[0].respawn * -1 + D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f));
	EnemyScroll(pPlayer[0].respawn * -1 + D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f));
	ExplosionScroll(pPlayer[0].respawn * -1 + D3DXVECTOR3(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, 0.0f));
	//fHeight = pPlayer[0].pos.y;
	//if (fHeight > SCREEN_HEIGHT * 0.5f) { fHeight -= SCREEN_HEIGHT * 0.5f; }
	//else if(fHeight < SCREEN_HEIGHT * 0.5f) { fHeight += SCREEN_HEIGHT * 0.5f; }

	//for (nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	//{
	//	if (g_aBlock[nCntBlock].bUse == true)
	//	{//スクロール
	//		g_aBlock[nCntBlock].pos += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//		g_aBlock[nCntBlock].posold += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//	}
	//}
	//pPlayer[0].pos += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//pPlayer[0].posold += D3DXVECTOR3(0.0f, fHeight, 0.0f);
	//AnimationScroll(D3DXVECTOR3(0.0f, fHeight, 0.0f));
	//EnemyScroll(D3DXVECTOR3(0.0f, fHeight, 0.0f));

}
