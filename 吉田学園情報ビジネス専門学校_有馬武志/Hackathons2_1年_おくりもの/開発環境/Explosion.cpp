//=========================================================================================================//
//
// [弾発射]->弾移動:爆発処理 [bullet.cpp]
// Author : Ryou Sugimoto
//
//=========================================================================================================//
#include "main.h"
#include "game.h"
#include "enemy.h"

//*********************************************************************************************************//
// マクロ定義
//*********************************************************************************************************//
#define EXPLOSION_VERTEX_NUM		(4)					// 頂点の数
#define EXPLOSION_PRIMITIVE_NUM		(2)					// プリミティブの数
#define EXPLOSION_MAX_TEX			(9)
#define EXPLOSION_TextureName		"data/TEXTURE/explosion002.png"
#define EXPLOSION_TextureName1		"data/TEXTURE/bulleteffect000.png"
#define EXPLOSION_TextureName2		"data/TEXTURE/pipo-btleffect003.png"
#define EXPLOSION_TextureName3		"data/TEXTURE/pipo-emotion.png"
#define EXPLOSION_TextureName4		"data/TEXTURE/pipo-btleffect008.png"
#define EXPLOSION_TextureName5		"data/TEXTURE/pipo-btleffect004.png"
#define EXPLOSION_TextureName6		"data/TEXTURE/flame_parts3.png"
#define EXPLOSION_TextureName7		"data/TEXTURE/flame1.png"
#define EXPLOSION_TextureName8		"data/TEXTURE/pipo-btleffect019.png"
#define	MAX_EXPLOSION				(1024)		// 弾の最大数
#define HALFEXPLOSION				(30)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXVECTOR3 Interval;	//間隔
	D3DXVECTOR3 pos;	//位置
	D3DXCOLOR col;	//色
	EXPLOSIONSTATE state;
	USETYPE type;		//使い方
	int nCntEnemy;		//敵の場合の指定のため
	int nLengthX;		//Xの長さ
	int nLengthY;		//Yの長さ
	int nAtk;
	int nCntAnim;		//Animationのカウント
	int nPtnAnim;		//指定された座標で表示
	int nPtnHeight;		//画像の縦の分割数
	int nPtnWide;		//画像の横の分割数
	int nPtnSpeed;		//Animation速度
	int nType;			//画像の指定
	float steep;		//ポリゴンの角度
	ANIMATION anim;		//アニメーションの使い方
	bool bUse;
}Explosin;

//*********************************************************************************************************//
// グローバル変数
//*********************************************************************************************************//
LPDIRECT3DTEXTURE9			g_pTextureExplosion[EXPLOSION_MAX_TEX] = {};	// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9		g_pVtxBuffExplosion = NULL;						// 頂点バッファへのポインタ
Explosin					g_aExplosion[MAX_EXPLOSION];					//最大のAnimation数

//=========================================================================================================//
// * 背景の描画処理1	初期化処理
//=========================================================================================================//
void InitExplosion(void)
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
		g_aExplosion[nCntBullet].bUse = false;
	}

	//TEXTURE読み込み
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName, &g_pTextureExplosion[0]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName1, &g_pTextureExplosion[1]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName2, &g_pTextureExplosion[2]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName3, &g_pTextureExplosion[3]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName4, &g_pTextureExplosion[4]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName5, &g_pTextureExplosion[5]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName6, &g_pTextureExplosion[6]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName7, &g_pTextureExplosion[7]);
	D3DXCreateTextureFromFile(pDevice, EXPLOSION_TextureName8, &g_pTextureExplosion[8]);

	//頂点BUFFERの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * EXPLOSION_VERTEX_NUM * MAX_EXPLOSION,		//確保するBUFFERのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
							//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[nCntBullet * 4].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(0, 0, 0.0f);
		pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(0, 0, 0.0f);

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
	g_pVtxBuffExplosion->Unlock();
}
//=========================================================================================================//
// * 背景の描画処理2	終了処理
//=========================================================================================================//
void UninitExplosion(void)
{//テクスチャの破棄
	int nCntTexture;

	for (nCntTexture = 0; nCntTexture < EXPLOSION_MAX_TEX; nCntTexture++)
	{
		if (g_pTextureExplosion[nCntTexture] != NULL)
		{
			g_pTextureExplosion[nCntTexture]->Release();
			g_pTextureExplosion[nCntTexture] = NULL;
		}
	}
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}
//=========================================================================================================//
// * 背景の描画処理3	更新処理
//=========================================================================================================//
void UpdateExplosion(void)
{
	int nCntBullet;
	int nCntEnemy;
	Enemy *pEnemy = GetEnemy();
	PLAYER *pPlayer = GetPlayer();

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{

		if (g_aExplosion[nCntBullet].bUse == true)
		{//弾を前に飛ばす
		 //MessageBox(0, "本当すか？", "終了", MB_YESNO);
			if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_EHIT)
			{//攻撃判定のある爆発なら
				for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
				{
					if (pEnemy[nCntEnemy].bUse == true)
					{
						if (HitAim(g_aExplosion[nCntBullet].pos, g_aExplosion[nCntBullet].nLengthX, g_aExplosion[nCntBullet].nLengthY, D3DX_PI, pEnemy[nCntEnemy].pos, pEnemy[nCntEnemy].nSize) == true)
						{//弾が当たってる
							HitEnemy(nCntEnemy, g_aExplosion[nCntBullet].nAtk, pPlayer[0].pos.x - pEnemy[nCntEnemy].pos.x, USETYPE_PLAYER);
							g_aExplosion[nCntBullet].state = EXPLOSIONSTATE_EFFECT;
						}//ヒット判定
					}
				}//敵の存在判定
			}
			else if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_PHIT)
			{
				if (HitAim(g_aExplosion[nCntBullet].pos, g_aExplosion[nCntBullet].nLengthX, g_aExplosion[nCntBullet].nLengthY, D3DX_PI, pPlayer[0].pos, pPlayer[0].nCollisionX) == true)
				{//弾が当たってる
					HitPlayer(g_aExplosion[nCntBullet].nAtk, g_aExplosion[nCntBullet].pos.x - pPlayer[0].pos.x, 0);
					//g_aExplosion[nCntBullet].state = EXPLOSIONSTATE_EFFECT;
				}//ヒット判定
			}
			else if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_PHITMINUS)
			{
				if (HitAim(g_aExplosion[nCntBullet].pos, g_aExplosion[nCntBullet].nLengthX / 2, g_aExplosion[nCntBullet].nLengthY / 2, D3DX_PI, pPlayer[0].pos, pPlayer[0].nCollisionX) == true)
				{//弾が当たってる
					HitPlayer(g_aExplosion[nCntBullet].nAtk, g_aExplosion[nCntBullet].pos.x - pPlayer[0].pos.x, 0);
					g_aExplosion[nCntBullet].state = EXPLOSIONSTATE_DELETE;
				}//ヒット判定
				if (g_aExplosion[nCntBullet].nCntAnim > 30) { g_aExplosion[nCntBullet].state = EXPLOSIONSTATE_DELETE; }
			}
			if (g_aExplosion[nCntBullet].state == EXPLOSIONSTATE_DELETE)
			{//消えていく
				g_aExplosion[nCntBullet].col.a -= 0.05f;
				if (g_aExplosion[nCntBullet].col.a <= 0.0f) { g_aExplosion[nCntBullet].bUse = false; }
			}

			if (g_aExplosion[nCntBullet].type == USETYPE_ENEMY && g_aExplosion[nCntBullet].nCntEnemy == nCntEnemy)
			{//指定されたエネミーなら
				g_aExplosion[nCntBullet].pos = pEnemy[nCntEnemy].pos + g_aExplosion[nCntBullet].Interval;
			}
			else if (g_aExplosion[nCntBullet].type == USETYPE_PLAYER)
			{//指定されたエネミーなら
				g_aExplosion[nCntBullet].pos = pPlayer[0].pos + g_aExplosion[nCntBullet].Interval;
			}

			g_aExplosion[nCntBullet].nCntAnim++;

			if (g_aExplosion[nCntBullet].nCntAnim % g_aExplosion[nCntBullet].nPtnSpeed == 0)
			{
				g_aExplosion[nCntBullet].nPtnAnim++;
				if (g_aExplosion[nCntBullet].nPtnAnim + 1 > g_aExplosion[nCntBullet].nPtnHeight * g_aExplosion[nCntBullet].nPtnWide && g_aExplosion[nCntBullet].anim != ANIMATION_LOOP)
				{//全部1回表示したら消える
					g_aExplosion[nCntBullet].bUse = false;
				}
			}
		}
	}
}
//=========================================================================================================//
// * 背景の描画処理4	描画処理
//=========================================================================================================//
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	// デバイスの取得
	pDevice = GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// αブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, 2);

	VERTEX_2D *pVtx;		//頂点情報へのポインタ
	//頂点BUFFERをロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aExplosion[nCntBullet].bUse == true)
		{
			//pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - g_aExplosion[nCntBullet].nLengthX, g_aExplosion[nCntBullet].pos.y - g_aExplosion[nCntBullet].nLengthY, 0.0f);
			//pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + g_aExplosion[nCntBullet].nLengthX, g_aExplosion[nCntBullet].pos.y - g_aExplosion[nCntBullet].nLengthY, 0.0f);
			//pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - g_aExplosion[nCntBullet].nLengthX, g_aExplosion[nCntBullet].pos.y + g_aExplosion[nCntBullet].nLengthY, 0.0f);
			//pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + g_aExplosion[nCntBullet].nLengthX, g_aExplosion[nCntBullet].pos.y + g_aExplosion[nCntBullet].nLengthY, 0.0f);

			pVtx[nCntBullet * 4].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 1].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 2].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) + (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);
			pVtx[nCntBullet * 4 + 3].pos = D3DXVECTOR3(g_aExplosion[nCntBullet].pos.x - (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX), g_aExplosion[nCntBullet].pos.y + (sinf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthX) - (cosf(g_aExplosion[nCntBullet].steep) * g_aExplosion[nCntBullet].nLengthY), 0.0f);

			pVtx[nCntBullet * 4].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
			pVtx[nCntBullet * 4 + 1].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide) + (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
			pVtx[nCntBullet * 4 + 2].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) + (1.0f / g_aExplosion[nCntBullet].nPtnHeight));
			pVtx[nCntBullet * 4 + 3].tex = D3DXVECTOR2((g_aExplosion[nCntBullet].nPtnAnim % g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnWide) + (1.0f / g_aExplosion[nCntBullet].nPtnWide), (g_aExplosion[nCntBullet].nPtnAnim / g_aExplosion[nCntBullet].nPtnWide) * (1.0f / g_aExplosion[nCntBullet].nPtnHeight) + (1.0f / g_aExplosion[nCntBullet].nPtnHeight));

			//カラー設定
			pVtx[nCntBullet * 4].col = g_aExplosion[nCntBullet].col;	// A = 透明度
			pVtx[nCntBullet * 4 + 1].col = g_aExplosion[nCntBullet].col;
			pVtx[nCntBullet * 4 + 2].col = g_aExplosion[nCntBullet].col;
			pVtx[nCntBullet * 4 + 3].col = g_aExplosion[nCntBullet].col;

			// テクスチャの設定 ポリゴンの描画
			pDevice->SetTexture(0, g_pTextureExplosion[g_aExplosion[nCntBullet].nType]);
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, EXPLOSION_PRIMITIVE_NUM);
		}
	}
	//頂点BUFFERをアンロックする
	g_pVtxBuffExplosion->Unlock();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=============================================================================
// 弾の設定処理
//=============================================================================
void SetExplosion(D3DXVECTOR3 pos, D3DXVECTOR3 Interval, D3DXCOLOR col , int nLengthX, int nLengthY, int nPtnWide, int nPtnHeight, int nPtnSpeed, int nType, int nAtk, ANIMATION anim, EXPLOSIONSTATE state, USETYPE type, int nCntEnemy, float steep)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aExplosion[nCntBullet].bUse == false)
		{
			g_aExplosion[nCntBullet].steep = steep;
			g_aExplosion[nCntBullet].pos = pos;
			g_aExplosion[nCntBullet].Interval = Interval;
			g_aExplosion[nCntBullet].col = col;
			g_aExplosion[nCntBullet].state = state;
			g_aExplosion[nCntBullet].nCntAnim = -1;
			g_aExplosion[nCntBullet].nPtnAnim = -1;
			g_aExplosion[nCntBullet].nPtnHeight = nPtnHeight;
			g_aExplosion[nCntBullet].nPtnWide = nPtnWide;
			g_aExplosion[nCntBullet].nPtnSpeed = nPtnSpeed;
			g_aExplosion[nCntBullet].nLengthX = nLengthX;
			g_aExplosion[nCntBullet].nLengthY = nLengthY;
			g_aExplosion[nCntBullet].nType = nType;
			g_aExplosion[nCntBullet].nAtk = nAtk;
			g_aExplosion[nCntBullet].anim = anim;
			g_aExplosion[nCntBullet].type = type;
			g_aExplosion[nCntBullet].nCntEnemy = nCntEnemy;
			g_aExplosion[nCntBullet].bUse = true;
			break;
		}
	}
}
//=========================================================================================================//
// * 全Animationスクロール処理
//=========================================================================================================//
void ExplosionScroll(D3DXVECTOR3 move)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_EXPLOSION; nCntBullet++)
	{
		if (g_aExplosion[nCntBullet].bUse == true)
		{//スクロール
			g_aExplosion[nCntBullet].pos += move;
		}
	}
}
//=========================================================================================================//
// * 全Animation破棄処理
//=========================================================================================================//
void BreakExplosion(void)
{
	int nCntAnim;

	for (nCntAnim = 0; nCntAnim < MAX_EXPLOSION; nCntAnim++)
	{
		g_aExplosion[nCntAnim].bUse = false;
	}
}
