//=========================================================================================================//
//
// [弾発射]->弾移動:爆発処理 [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "sound.h"
#include <stdlib.h>				//ランド用
#include <time.h>				//同じくランド用

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define EXPLOSION_VERTEX_NUM		(4)					// 頂点の数
#define EXPLOSION_PRIMITIVE_NUM		(2)					// プリミティブの数
#define EXPLOSION_MAX_TEX			(10)
#define EXPLOSION_TextureName		"data/TEXTURE/coin000.png"
#define EXPLOSION_TextureName1		"data/TEXTURE/icon000.png"
#define EXPLOSION_TextureName2		"data/TEXTURE/checkpoint000.png"
#define EXPLOSION_TextureName3		"data/TEXTURE/checkpoint001.png"
#define EXPLOSION_TextureName4		"data/TEXTURE/heart000.png"
#define EXPLOSION_TextureName5		"data/TEXTURE/food000.png"
#define EXPLOSION_TextureName6		"data/TEXTURE/food001.png"
#define EXPLOSION_TextureName7		"data/TEXTURE/food002.png"
#define EXPLOSION_TextureName8		"data/TEXTURE/food003.png"
#define EXPLOSION_TextureName9		"data/TEXTURE/Clock000.png"
#define	MAX_EXPLOSION				(64)		// 弾の最大数
#define HALFEXPLOSION				(30)

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9			g_pTextureAnimation[EXPLOSION_MAX_TEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffAnimation = NULL;						// 頂点バッファへのポインタ
Animation					g_aAnimation[MAX_EXPLOSION];					//最大のAnimation数

//=========================================================================================================//
// * 背景の描画処理1	初期化処理
//=========================================================================================================//
void InitAnimation(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = GetDevice();
	int nCntBullet;

	// 弾の情報の初期化
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//g_aExplosion[nCntBullet].pos = { 0.0f, 0.0f, 0.0f };
		//g_aExplosion[nCntBullet].col = { 1.0f, 1.0f, 1.0f, };
		//g_aExplosion[nCntBullet].nCntAnim = -1;
		//g_aExplosion[nCntBullet].nPtnAnim = -1;
		//g_aExplosion[nCntBullet].nType = 0;
		g_aAnimation[nCntBullet].bUse = false;
	}

	//TEXTURE読み込み
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName, &g_pTextureAnimation[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName1, &g_pTextureAnimation[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName2, &g_pTextureAnimation[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName3, &g_pTextureAnimation[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName4, &g_pTextureAnimation[4]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName5, &g_pTextureAnimation[5]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName6, &g_pTextureAnimation[6]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName7, &g_pTextureAnimation[7]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName8, &g_pTextureAnimation[8]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName9, &g_pTextureAnimation[9]);

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * EXPLOSION_VERTEX_NUM * MAX_EXPLOSION,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffAnimation,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//頂点座標の設定
		//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

		pVtx[nCntBullet * 4].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 1].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 2].rhw = 1.0f;
		pVtx[nCntBullet * 4 + 3].rhw = 1.0f;

		////カラー設定
		//pVtx[nCntBullet * 4].col = D3DCOLOR_RGBA(0,0,0, 255);	// A = 透明度
		//pVtx[nCntBullet * 4 + 1].col = D3DCOLOR_RGBA(0,0,0, 255);
		//pVtx[nCntBullet * 4 + 2].col = D3DCOLOR_RGBA(0,0,0, 255);
		//pVtx[nCntBullet * 4 + 3].col = D3DCOLOR_RGBA(0,0,0, 255);

		//テクスチャ座標設定
		//pVtx[nCntBullet * 4].tex = D3DXVECTOR2(0.0f, 0.0f);
		//pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
		//pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
		//pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}

	//頂点BUFFERをアンロックする
	g_pVtxBuffAnimation->Unlock();
}
//=========================================================================================================//
// * 背景の描画処理2	終了処理
//=========================================================================================================//
void UninitAnimation(void)
{//テクスチャの破棄
	int nCntTexture;

	BreakAnimation();
	for (nCntTexture = 0; nCntTexture < EXPLOSION_MAX_TEX; nCntTexture++)
	{
		if (g_pTextureAnimation[nCntTexture] != NULL)
		{
			g_pTextureAnimation[nCntTexture]->Release();
			g_pTextureAnimation[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffAnimation != NULL)
	{
		g_pVtxBuffAnimation->Release();
		g_pVtxBuffAnimation = NULL;
	}
}
//=========================================================================================================//
// * 背景の描画処理3	更新処理
//=========================================================================================================//
void UpdateAnimation(void)
{
	int nCntBullet;
	float fRand = (rand() % 628) * 0.01f;
	int nRand = rand() % 10 + 55;
	static int nVibration = 0;
	PLAYER *pPlayer = GetPlayer();
	nVibration++;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{

		if (g_aAnimation[nCntBullet].bUse == true)
		{//弾を前に飛ばす
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_CHECK0 && g_aAnimation[nCntBullet].pos.x + g_aAnimation[nCntBullet].nLengthX > pPlayer[0].pos.x && g_aAnimation[nCntBullet].pos.x - g_aAnimation[nCntBullet].nLengthX < pPlayer[0].pos.x &&
				g_aAnimation[nCntBullet].pos.y + g_aAnimation[nCntBullet].nLengthY > pPlayer[0].pos.y && g_aAnimation[nCntBullet].pos.y - g_aAnimation[nCntBullet].nLengthY < pPlayer[0].pos.y)
			{
				pPlayer[0].respawn = g_aAnimation[nCntBullet].initpos;
				g_aAnimation[nCntBullet].nType = 3;
				g_aAnimation[nCntBullet].type = ANIMTYPE_CHECK1;
				for (int nCntChack = 0; nCntChack < MAX_EXPLOSION; nCntChack++)
				{
					if (g_aAnimation[nCntChack].bUse == true && g_aAnimation[nCntChack].type == ANIMTYPE_CHECK0 && g_aAnimation[nCntChack].nCntState < g_aAnimation[nCntBullet].nCntState)
					{//前のチェックポイントを使用済みに
						g_aAnimation[nCntChack].type = ANIMTYPE_CHECK1;
						g_aAnimation[nCntChack].nType = 3;
					}
				}
			}
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_CLOCK && pPlayer[0].bClock[g_aAnimation[nCntBullet].nCntState] == true) { g_aAnimation[nCntBullet].bUse = false; }
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_POWERUP && pPlayer[0].bPowerUP[g_aAnimation[nCntBullet].nCntState] == true) { g_aAnimation[nCntBullet].bUse = false; }
		 //MessageBox(0, "本当すか？", "終了", MB_YESNO);
			g_aAnimation[nCntBullet].posold = g_aAnimation[nCntBullet].pos;
			g_aAnimation[nCntBullet].nCntAnim++;

			if(g_aAnimation[nCntBullet].type == ANIMTYPE_NONE)
			{ 
				g_aAnimation[nCntBullet].nPtnAnim = pPlayer[0].nPtnAnim;
				g_aAnimation[nCntBullet].nCntState = pPlayer[0].nVibration;

				if (pPlayer[0].nVibration > 0)
				{//指定された時間入り続ける
					if (nVibration % 2 == 0) { g_aAnimation[nCntBullet].pos += D3DXVECTOR3(sinf(fRand) * 10, cosf(fRand) * 10, 0.0f); }
					else if (nVibration % 2 == 1) { g_aAnimation[nCntBullet].pos = g_aAnimation[nCntBullet].initpos; }
				}//初期位置に戻る
				else if (pPlayer[0].nVibration == 0) { g_aAnimation[nCntBullet].pos = g_aAnimation[nCntBullet].initpos; }
			}
			if (g_aAnimation[nCntBullet].type == ANIMTYPE_NONE &&g_aAnimation[nCntBullet].nPtnAnim > 3) { g_aAnimation[nCntBullet].nPtnAnim -= 2; }

			if (g_aAnimation[nCntBullet].nCntAnim % g_aAnimation[nCntBullet].nPtnSpeed == 0 && g_aAnimation[nCntBullet].type != ANIMTYPE_NONE)
			{
				g_aAnimation[nCntBullet].nPtnAnim++;
				if (g_aAnimation[nCntBullet].nPtnAnim > g_aAnimation[nCntBullet].nPtnHeight * g_aAnimation[nCntBullet].nPtnWide && g_aAnimation[nCntBullet].anim != ANIMATION_LOOP)
				{//全部1回表示したら消える
					g_aAnimation[nCntBullet].bUse = false;
				}
			}
		}
	}

}
//=========================================================================================================//
// * 背景の描画処理4	描画処理
//=========================================================================================================//
void DrawAnimation(ANIMTYPE type)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntItem;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffAnimation, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0 && g_aAnimation[nCntItem].type != ANIMTYPE_NONE && type != ANIMTYPE_NONE)
		{// テクスチャの設定 ポリゴンの描画 置物以外
			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);

			pVtx[nCntItem * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = 透明度
			pVtx[nCntItem * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[nCntItem * 4].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));

			pDevice->SetTexture(0, g_pTextureAnimation[g_aAnimation[nCntItem].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, EXPLOSION_PRIMITIVE_NUM);
		}
		else if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0 && g_aAnimation[nCntItem].type == ANIMTYPE_NONE && type == ANIMTYPE_NONE)
		{//置物しか表示しない
			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);

			pVtx[nCntItem * 4].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// A = 透明度
			pVtx[nCntItem * 4 + 1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntItem * 4 + 3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			pVtx[nCntItem * 4].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 1].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 2].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));
			pVtx[nCntItem * 4 + 3].tex = D3DXVECTOR2((g_aAnimation[nCntItem].nPtnAnim % g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnWide) + (1.0f / g_aAnimation[nCntItem].nPtnWide), (g_aAnimation[nCntItem].nPtnAnim / g_aAnimation[nCntItem].nPtnWide) * (1.0f / g_aAnimation[nCntItem].nPtnHeight) + (1.0f / g_aAnimation[nCntItem].nPtnHeight));

			pDevice->SetTexture(0, g_pTextureAnimation[g_aAnimation[nCntItem].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, EXPLOSION_PRIMITIVE_NUM);

		}
	}

	//頂点BUFFERをアンロックする
	g_pVtxBuffAnimation->Unlock();
}
//============================================================================= 
// 弾の設定処理
//=============================================================================
void SetAnimation(D3DXVECTOR3 pos, int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nCntState, ANIMATION anim, ANIMTYPE type)
{
	int nCntBullet;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aAnimation[nCntBullet].bUse == false)
		{
			g_aAnimation[nCntBullet].pos = pos;
			g_aAnimation[nCntBullet].initpos = pos;
			g_aAnimation[nCntBullet].nCntAnim = -1;
			g_aAnimation[nCntBullet].nPtnAnim = -1;
			g_aAnimation[nCntBullet].nPtnHeight = nPtnHeight;
			g_aAnimation[nCntBullet].nPtnWide = nPtnWide;
			g_aAnimation[nCntBullet].nPtnSpeed = nPtnSpeed;
			g_aAnimation[nCntBullet].nLengthX = nLengthX;
			g_aAnimation[nCntBullet].nLengthY = nLengthY;
			g_aAnimation[nCntBullet].nType = nType;
			g_aAnimation[nCntBullet].anim = anim;
			g_aAnimation[nCntBullet].type = type;
			g_aAnimation[nCntBullet].nCntState = nCntState;
			g_aAnimation[nCntBullet].bUse = true;

			if (g_aAnimation[nCntBullet].type == ANIMTYPE_COIN)
			{
				g_aAnimation[nCntBullet].nLengthX = nLengthX;
				g_aAnimation[nCntBullet].nLengthY = nLengthY;
				g_aAnimation[nCntBullet].nPtnSpeed = 20;
			}

			break;
		}
	}
	//頂点BUFFERをアンロックする
	g_pVtxBuffAnimation->Unlock();
}
//=========================================================================================================//
// * 全Animation破棄処理
//=========================================================================================================//
void BreakAnimation(void)
{
	int nCntAnim;

	for (nCntAnim = 0; nCntAnim < MAX_EXPLOSION; nCntAnim++)
	{
		g_aAnimation[nCntAnim].bUse = false;
	}
}
//=============================================================================
// ブロックとの衝突判定
//=============================================================================
void HitItem(int nCntItem)
{
	PLAYER *pPlayer = GetPlayer();
	int nCntChack;

	switch (g_aAnimation[nCntItem].type)
	{
	case ANIMTYPE_COIN:
		g_aAnimation[nCntItem].bUse = false;
		PlaySound(SOUND_LABEL_COIN);
		pPlayer[0].nScore += 100;
		SetDigital(g_aAnimation[nCntItem].pos, D3DXCOLOR(0.4f, 0.98f, 1.0f, 0.0f), DIGITALSTATE_WAVE, 9, 15, 100);
		break;
	case ANIMTYPE_CHECK0:
		pPlayer[0].respawn = g_aAnimation[nCntItem].initpos;
		g_aAnimation[nCntItem].nType = 3;
		g_aAnimation[nCntItem].type = ANIMTYPE_CHECK1;
		for (nCntChack = 0; nCntChack < MAX_EXPLOSION; nCntChack++)
		{
			if (g_aAnimation[nCntChack].bUse == true && g_aAnimation[nCntChack].type == ANIMTYPE_CHECK0 && g_aAnimation[nCntChack].nCntState < g_aAnimation[nCntItem].nCntState)
			{//前のチェックポイントを使用済みに
				g_aAnimation[nCntChack].type = ANIMTYPE_CHECK1;
				g_aAnimation[nCntChack].nType = 3;
			}
		}
	case ANIMTYPE_CHECK1:
		if (pPlayer[0].nLife > 0)
		{
			SetExplosion(g_aAnimation[nCntItem].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
			PlaySound(SOUND_LABEL_CHECKPOINT);
			pPlayer[0].nEXPold = pPlayer[0].nEXP;
			pPlayer[0].nMAXEXPold = pPlayer[0].nMAXEXP;
			pPlayer[0].nLevelold = pPlayer[0].nLevel;
			pPlayer[0].nLifeold = pPlayer[0].nLife;
			for (int nCount = 0; nCount < 10; nCount++) { pPlayer[0].bPowerUPold[nCount] = pPlayer[0].bPowerUP[nCount]; }
			for (int nCount = 0; nCount < 10; nCount++) { pPlayer[0].bClockold[nCount] = pPlayer[0].bClock[nCount]; }
		}
		break;
	case ANIMTYPE_POWERUP:
		PlaySound(SOUND_LABEL_HEEL);
		SetExplosion(g_aAnimation[nCntItem].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100,100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		SetDigital(D3DXVECTOR3(600, SCREEN_HEIGHT * 1.1f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_HEEL, 30, 45, 1000);
		pPlayer[0].nLife += 1000;
		pPlayer[0].nMaxLife += 1000;
		pPlayer[0].bPowerUP[g_aAnimation[nCntItem].nCntState] = true;
		g_aAnimation[nCntItem].bUse = false;
		break;
	case ANIMTYPE_ALLHEEL:
		PlaySound(SOUND_LABEL_HEEL);
		SetDigital(D3DXVECTOR3(600, SCREEN_HEIGHT * 1.1f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_HEEL, 30, 45, pPlayer[0].nMaxLife);
		g_aAnimation[nCntItem].bUse = false;
		pPlayer[0].nLife = pPlayer[0].nMaxLife;
		break;
	case ANIMTYPE_HEEL:
		PlaySound(SOUND_LABEL_HEEL);
		SetDigital(D3DXVECTOR3(600, SCREEN_HEIGHT * 1.1f, 0.0f), D3DXCOLOR(0.41f, 1.0f, 0.3f, 0.0f), DIGITALSTATE_HEEL, 30, 45, g_aAnimation[nCntItem].nCntState);
		pPlayer[0].nLife += g_aAnimation[nCntItem].nCntState;
		if (pPlayer[0].nLife > pPlayer[0].nMaxLife) { pPlayer[0].nLife = pPlayer[0].nMaxLife; }
		g_aAnimation[nCntItem].bUse = false;
		break;
	case ANIMTYPE_CLOCK:
		PlaySound(SOUND_LABEL_HEEL);
		pPlayer[0].nTime[0] += 1200;
		SetExplosion(g_aAnimation[nCntItem].pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 100, 100, 8, 1, 3, 4, 0, ANIMATION_NORMAL, EXPLOSIONSTATE_EFFECT, USETYPE_IGNORE, 0, D3DX_PI);
		pPlayer[0].bClock[g_aAnimation[nCntItem].nCntState] = true;
		g_aAnimation[nCntItem].bUse = false;
		break;
	}
}
//=============================================================================
// ブロックとの衝突判定
//=============================================================================
void CollisionItem(void)
{
	int nCntItem;
	int nLength;
	PLAYER *pPlayer = GetPlayer();

	if (g_aAnimation[0].nCntAnim > 30)
	{
		for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
		{//上下の判定
			if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0)
			{//使われているブロック && 判定付きのブロックなら
				if (g_aAnimation[nCntItem].posold.y - g_aAnimation[nCntItem].nLengthY >= pPlayer[0].posold.y + PLAYER_CollisionY && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= pPlayer[0].pos.y + PLAYER_CollisionY)
				{//前回が上&&判定上
					nLength = (int)pPlayer[0].pos.x - (int)g_aAnimation[nCntItem].pos.x;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionX;
					if (nLength <= g_aAnimation[nCntItem].nLengthX)
					{
						HitItem(nCntItem);
					}
				}
				else if (g_aAnimation[nCntItem].posold.y + g_aAnimation[nCntItem].nLengthY <= pPlayer[0].posold.y - PLAYER_CollisionY && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= pPlayer[0].pos.y - PLAYER_CollisionY)
				{//前回が下&&判定下 
					nLength = (int)pPlayer[0].pos.x - (int)g_aAnimation[nCntItem].pos.x;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionX;
					if (nLength <= g_aAnimation[nCntItem].nLengthX)
					{
						HitItem(nCntItem);
					}
				}
			}
		}

		for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
		{//右左の判定
			if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= SCREEN_WIDTH && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= 0 && g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY <= SCREEN_HEIGHT && g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY >= 0)
			{//使われているブロック && 判定付きのブロックなら
				if (g_aAnimation[nCntItem].posold.x + g_aAnimation[nCntItem].nLengthX <= pPlayer[0].posold.x - PLAYER_CollisionX && g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX >= pPlayer[0].pos.x - PLAYER_CollisionX)
				{//前回が右&&判定右
					nLength = (int)pPlayer[0].pos.y - (int)g_aAnimation[nCntItem].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionY;
					if (nLength < g_aAnimation[nCntItem].nLengthY)
					{//当たった！
						HitItem(nCntItem);
					}
				}
				if (g_aAnimation[nCntItem].posold.x - g_aAnimation[nCntItem].nLengthX >= pPlayer[0].posold.x + PLAYER_CollisionX && g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX <= pPlayer[0].pos.x + PLAYER_CollisionX)
				{//前回が左&&判定左
					nLength = (int)pPlayer[0].pos.y - (int)g_aAnimation[nCntItem].pos.y;
					if (nLength < 0) { nLength *= -1; }
					nLength -= PLAYER_CollisionY;
					if (nLength < g_aAnimation[nCntItem].nLengthY)
					{//当たった！
						HitItem(nCntItem);
					}
				}
			}
		}
	}
}
//=========================================================================================================//
// * 全Animationスクロール処理
//=========================================================================================================//
void AnimationScroll(D3DXVECTOR3 move)
{
	int nCntItem;
	VERTEX_2D *pVtx;		//頂点情報へのポインタ

	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffAnimation->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntItem = 0; nCntItem < MAX_EXPLOSION; nCntItem++)
	{
		if (g_aAnimation[nCntItem].bUse == true && g_aAnimation[nCntItem].type != ANIMTYPE_NONE)
		{//スクロール
			g_aAnimation[nCntItem].pos += move;
			g_aAnimation[nCntItem].posold += move;

			pVtx[nCntItem * 4].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 1].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y - g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 2].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x - g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);
			pVtx[nCntItem * 4 + 3].pos = D3DXVECTOR3(g_aAnimation[nCntItem].pos.x + g_aAnimation[nCntItem].nLengthX, g_aAnimation[nCntItem].pos.y + g_aAnimation[nCntItem].nLengthY, 0.0f);

		}
	}
	//頂点BUFFERをアンロックする
	g_pVtxBuffAnimation->Unlock();
}

//=========================================================================================================//
// * 全Animation破棄処理
//=========================================================================================================//
Animation *GetAnimation(void)
{
	return &g_aAnimation[0];
}

